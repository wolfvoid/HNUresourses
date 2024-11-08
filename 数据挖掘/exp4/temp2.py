import torch
import torch.nn as nn
import dgl
import dgl.nn.pytorch.conv as conv
import torch.nn as nn
import torch.nn.functional as F
import dgl.function as fn
import numpy as np
from dgl import save_graphs, load_graphs

src = np.random.randint(0, 100, 500)
dst = np.random.randint(0, 100, 500)
# 同时建立反向边
graph = dgl.graph((np.concatenate([src, dst]), np.concatenate([dst, src])))
print(graph)
# 图中节点的数量是DGL通过给定的图的边列表中最大的点ID推断所得出的

# 建立点和边特征，以及边的标签
graph.ndata['feature'] = torch.randn(100, 10)
graph.edata['feature'] = torch.randn(1000, 10)
graph.edata['label'] = torch.randn(1000) # 当然我们也可以给节点和边赋予一些特征。这里用不上，仅仅做为demo


# 下面是使用点积计算边得分的例子。
class DotProductPredictor(nn.Module):
    def forward(self, graph, h):
        # 这里是根据每条边的两个端点的隐藏向量的点积dot来计算边存在与否的score
        with graph.local_scope():
            graph.ndata['h'] = h
            graph.apply_edges(fn.u_dot_v('h', 'h', 'score'))
            return graph.edata['score']


class Model(nn.Module):
    def __init__(self, in_features, hidden_features, out_features):
        super().__init__()
        self.sage = SAGE(in_features, hidden_features, out_features)
        self.pred = DotProductPredictor()

    # 模型主题函数，调用sage子模型是2层的sageconv算子叠加的，然后得到sage子模块的输出隐藏向量。
    # 这里的隐藏向量已经涵盖有聚合邻居的信息了。然后分别将pos样本和neg样本输入pred模型得到两个打分。
    # 这里的g表示的是原生的逻辑图，我们自己构建起来的，而neg_g是对每个种子节点负采样后得到的子图。而在这里x是输入的所有节点的feature。
    def forward(self, g, neg_g, x):
        h = self.sage(g, x)
        # 注意这里多了一个返回,pos logit 和 neg logit
        return self.pred(g, h), self.pred(neg_g, h)

# 涉及到对不存在的边的采样过程,负采样。因为上述的得分预测模型在图上进行计算，用户需要将负采样的样本表示为另外一个图，其中包含所有负采样的节点对作为边。
# 下面的例子展示了将负采样的样本表示为一个图。每一条边 ( , ) 都有   个对应的负采样样本 ( ,  )，其中    是从均匀分布中采样的。
def construct_negative_graph(graph, k):
    src, dst = graph.edges()
    neg_src = src.repeat_interleave(k)
    neg_dst = torch.randint(0, graph.num_nodes(), (len(src) * k,))
    return dgl.graph((neg_src, neg_dst), num_nodes=graph.num_nodes())

# 间隔损失，训练的循环部分里会重复构建负采样图并计算损失函数值
def compute_loss(pos_score, neg_score):
    n_edges = pos_score.shape[0]
    return (1 - pos_score.unsqueeze(1) + neg_score.view(n_edges, -1)).clamp(min=0).mean()

# 模型训练过程
node_features = graph.ndata['feature']
# 模型特征输入维度
n_features = node_features.shape[1]
# 负采样条数
k = 5
model = Model(n_features, 100, 8)
# 优化器
opt = torch.optim.Adam(model.parameters())

for epoch in range(10):
    # 采样得到neg graph
    negative_graph = construct_negative_graph(graph, k)
    pos_score, neg_score = model(graph, negative_graph, node_features)
    # 计算损失
    loss = compute_loss(pos_score, neg_score)
    # 梯度优化
    opt.zero_grad()
    loss.backward()
    opt.step()
    print(loss.item())

# 输出node embeding
# 训练后，节点表示可以通过以下代码获取。
node_embeddings = model.sage(graph, node_features)
print(node_embeddings[0])





# 假设你已经有一个训练好的模型 model

# 选择两个节点的ID
node1 = 0
node2 = 1

# 获取节点特征
node1_features = node_features[node1].unsqueeze(0)  # 添加 batch 维度
node2_features = node_features[node2].unsqueeze(0)

# 使用训练好的 GraphSAGE 模型获取节点嵌入
with torch.no_grad():
    node1_embedding = model.sage(graph, node1_features)
    node2_embedding = model.sage(graph, node2_features)

# 将节点嵌入连接并传递给链接预测模型
link_prediction_score = model.pred(graph, torch.cat([node1_embedding, node2_embedding]))
print("Link Prediction Score:", link_prediction_score.item())






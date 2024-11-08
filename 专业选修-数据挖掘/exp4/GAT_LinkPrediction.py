import dgl
import torch
import numpy as np

# 读取基因列表
with open('GeneList.txt', 'r') as f:
    gene_list = [line.strip() for line in f]

# 构建基因到索引的映射
gene_dict = {gene: idx for idx, gene in enumerate(gene_list)}

# 读取基因关系和置信分数
with open('Positive_LinkSL.txt', 'r') as f:
    edges = [line.strip().split() for line in f]

# 提取基因关系的源节点、目标节点和置信分数
src_nodes = [gene_dict[edge[0]] for edge in edges]
dst_nodes = [gene_dict[edge[1]] for edge in edges]
confidence_scores = [float(edge[2]) for edge in edges]

# 创建有向图
graph_directed = dgl.graph((src_nodes, dst_nodes))
graph_directed.edata['confidence'] = torch.tensor(confidence_scores).view(-1, 1)

# 交换源节点和目标节点的位置，创建反向边
graph_reverse = dgl.graph((dst_nodes, src_nodes))
graph_reverse.edata['confidence'] = torch.tensor(confidence_scores).view(-1, 1)

# 将两个有向图的边连接起来，得到包含两次边的无向图
graph_undirected = dgl.graph((graph_directed.edges()[0].tolist() + graph_reverse.edges()[0].tolist(),
                              graph_directed.edges()[1].tolist() + graph_reverse.edges()[1].tolist()))
graph_undirected.edata['confidence'] = torch.cat([graph_directed.edata['confidence'], graph_reverse.edata['confidence']])

graph = graph_undirected

# 检测上一步的完成情况：输出边和边特征的信息到同一个txt文件
# output_file = 'graph_info.txt'
# np.savetxt(output_file, np.column_stack((graph_undirected.edges()[0], graph_undirected.edges()[1], graph_undirected.edata['confidence'].numpy())),
#           fmt='%d %d %.6f', header='Source Target Confidence', comments='')
# print("Graph Edges:")
# print(graph_undirected.edges())
# print("Edge Features:")
# print(graph_undirected.edata)
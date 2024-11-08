import numpy as np
DEBUG = 1

class NaiveBayesClassifier(object):
    def __init__(self):
        '''
        self.label_prob表示每种类别在数据中出现的概率
        例如，{0:0.333, 1:0.667}表示数据中类别0出现的概率为0.333，类别1的概率为0.667
        '''
        self.label_prob = {}
        '''
        self.condition_prob表示每种类别确定的条件下各个特征出现的概率
        例如训练数据集中的特征为 [[2, 1, 1],
                              [1, 2, 2],
                              [2, 2, 2],
                              [2, 1, 2],
                              [1, 2, 3]]
        标签为[1, 0, 1, 0, 1]
        那么当标签为0时第0列的值为1的概率为0.5，值为2的概率为0.5;
        当标签为0时第1列的值为1的概率为0.5，值为2的概率为0.5;
        当标签为0时第2列的值为1的概率为0，值为2的概率为1，值为3的概率为0;
        当标签为1时第0列的值为1的概率为0.333，值为2的概率为0.666;
        当标签为1时第1列的值为1的概率为0.333，值为2的概率为0.666;
        当标签为1时第2列的值为1的概率为0.333，值为2的概率为0.333,值为3的概率为0.333;
        因此self.condition_prob的值如下：     
        {
            0:{
                0:{
                    1:0.5
                    2:0.5
                }
                1:{
                    1:0.5
                    2:0.5
                }
                2:{
                    1:0
                    2:1
                    3:0
                }
            }
            1:
            {
                0:{
                    1:0.333
                    2:0.666
                }
                1:{
                    1:0.333
                    2:0.666
                }
                2:{
                    1:0.333
                    2:0.333
                    3:0.333
                }
            }
        }
        '''
        self.condition_prob = {}

    def fit(self, feature, label):
        '''
        对模型进行训练，需要将各种概率分别保存在self.label_prob和self.condition_prob中
        :param feature: 训练数据集所有特征组成的ndarray
        :param label:训练数据集中所有标签组成的ndarray
        :return: 无返回
        '''

        # ********* Begin *********#
        # label_prob
        label_0 = np.count_nonzero(label == 0)
        label_1 = np.count_nonzero(label == 1)
        self.label_prob = {0: (label_0+1)/(label.size+2), 1: (label_1+1)/(label.size+2)}

        # condition_prob
        self.condition_prob[0] = {}
        self.condition_prob[1] = {}
        # 初始化每个特征取值的字典
        for item in self.condition_prob:
            for feature_index in range(len(feature[0])):  # len(feature[0])为特征数量
                self.condition_prob[item][feature_index] = {}
        # 读取数据
        i = 0  # 样本编号
        for data in feature:
            j = 0  # 特征序号
            for feat in data:
                if (self.condition_prob[label[i]][j].get(feat) == None):
                    self.condition_prob[label[i]][j][feat] = 0
                self.condition_prob[label[i]][j][feat] += 1
                j += 1
            i += 1

        # 归一化得到概率(加入拉普拉斯平滑)
        for j in range(feature.shape[1]):
            for i in range(2):
                for key,value in self.condition_prob[i][j].items():
                    if (self.condition_prob[(i+1)%2][j].get(key) == None):
                        self.condition_prob[(i+1)%2][j][key] = 0
            Ni = 0
            for key, value in self.condition_prob[i][j].items():
                Ni += 1
            for i in range(2):
                total_sum = Ni
                for key, value in self.condition_prob[i][j].items():
                    total_sum += value
                for key,value in self.condition_prob[i][j].items():
                    self.condition_prob[i][j][key] = (self.condition_prob[i][j][key] + 1) / total_sum

        if (DEBUG):
            print("label_prob:\n{}".format(self.label_prob))
            print("condition_prob:\n{}".format(self.condition_prob))

# ********* End *********#

    def predict(self, feature):
        '''
        对数据进行预测，返回预测结果
        :param feature:测试数据集所有特征组成的ndarray
        :return:
        '''
        # ********* Begin *********#

        # P(A1) P(B|A1)  P(C|A1)  P(D|A1)
        ans = []
        i = 0 # 处理的组号
        for group in feature:
            if (DEBUG):
                print("now process {}".format(i))
            # 处理多组数据
            prob_list = {}
            prob_list[0] = self.label_prob[0]
            prob_list[1] = self.label_prob[1]
            for label_index in range(2):
                j = 0 # 处理的特征序号，即feat的index
                for feat in group:
                    pa = self.condition_prob[label_index][j].get(feat)
                    if (pa == None):
                        prob_list[label_index] *= 0
                    else:
                        prob_list[label_index] *= pa
                    j += 1
            if (DEBUG):
                print(prob_list[0])
                print(prob_list[1])
            if (prob_list[0]>prob_list[1]):
                ans.append(0)
            else:
                ans.append(1)
            i += 1
        return ans


        # ********* End *********#


if __name__ == "__main__":
    nb_classifier = NaiveBayesClassifier()
    feature = np.array([[2, 1, 1],[1, 2, 2],[2, 2, 2],[2, 1, 2],[1, 2, 3]])
    label = np.array([1, 0, 1, 0, 1])
    nb_classifier.fit(feature,label)
    print(nb_classifier.predict(feature))
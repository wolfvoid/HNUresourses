from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.naive_bayes import MultinomialNB


def news_predict(train_sample, train_label, test_sample):
    '''
    训练模型并进行预测，返回预测结果
    :param train_sample: 原始训练集中的新闻文本，类型为ndarray
    :param train_label: 训练集中新闻文本对应的主题标签，类型为ndarray
    :param test_sample: 原始测试集中的新闻文本，类型为ndarray
    :return: 预测结果，类型为ndarray
    '''

    # 实例化tf-idf对象，同时完成向量化和TF-IDF转换
    tfidf_vectorizer = TfidfVectorizer()

    # 将训练集和测试集的文本进行向量化和TF-IDF转换
    X_train = tfidf_vectorizer.fit_transform(train_sample)
    X_test = tfidf_vectorizer.transform(test_sample)

    # 使用多项式朴素贝叶斯进行训练和预测
    clf = MultinomialNB(alpha=0.001)
    clf.fit(X_train, train_label)
    result = clf.predict(X_test)

    return result

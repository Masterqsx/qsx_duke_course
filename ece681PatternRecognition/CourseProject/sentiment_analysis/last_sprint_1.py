#-*- coding: utf-8 -*-


import re,os,glob,copy
from sklearn import datasets,svm,cross_validation,tree,decomposition
from sklearn.metrics import roc_curve, auc
from sklearn.naive_bayes import MultinomialNB,GaussianNB,BernoulliNB
import numpy as np
import matplotlib.pyplot as plt


data = np.loadtxt("data.txt",dtype=type(1),delimiter=' ');
target = np.loadtxt("target.txt",dtype=type(1),delimiter=' ');
data_pre = np.loadtxt("data_pre.txt",dtype=type(1),delimiter=' ');

sentiment = svm.SVC(kernel="linear",probability=True)
sentiment_bay_m = MultinomialNB()
sentiment_bay_g = GaussianNB()
sentiment_bay_b = BernoulliNB()

sentiment_dec = tree.DecisionTreeClassifier()


accuracy = np.mean(cross_validation.cross_val_score(sentiment,data,target))
accuracy_pre = np.mean(cross_validation.cross_val_score(sentiment,data_pre,target))
accuracy_bay_m = np.mean(cross_validation.cross_val_score(sentiment_bay_m,data,target))
accuracy_bay_pre_m = np.mean(cross_validation.cross_val_score(sentiment_bay_m,data_pre,target))
accuracy_bay_g = np.mean(cross_validation.cross_val_score(sentiment_bay_g,data,target))
accuracy_bay_pre_g = np.mean(cross_validation.cross_val_score(sentiment_bay_g,data_pre,target))
accuracy_bay_b = np.mean(cross_validation.cross_val_score(sentiment_bay_b,data,target))
accuracy_bay_pre_b = np.mean(cross_validation.cross_val_score(sentiment_bay_b,data_pre,target))

print accuracy,accuracy_pre,accuracy_bay_m,accuracy_bay_pre_m,accuracy_bay_g,accuracy_bay_pre_g,accuracy_bay_b,accuracy_bay_pre_b


cv = cross_validation.StratifiedKFold(target)

mean_tpr = np.array(0.0)
mean_fpr = np.array(0.0)
for (train,test) in cv:
  probas = sentiment.fit(data[train], target[train]).predict_proba(data[test])
  fpr, tpr, thresholds = roc_curve(target[test], probas[:, 1])
  mean_fpr = np.append(fpr,mean_fpr)
  mean_tpr = np.append(tpr,mean_tpr)

mean_fpr=np.sort(mean_fpr)
mean_tpr=np.sort(mean_tpr)
mean_auc = auc(mean_fpr, mean_tpr)
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of SVM with frequency data \n(AUC = %0.2f) (accuracy = %0.2f) 3 folder' % (mean_auc,accuracy))

mean_tpr = np.array(0.0)
mean_fpr = np.array(0.0)
for (train,test) in cv:
  probas = sentiment.fit(data_pre[train], target[train]).predict_proba(data_pre[test])
  fpr, tpr, thresholds = roc_curve(target[test], probas[:, 1])
  mean_fpr = np.append(fpr,mean_fpr)
  mean_tpr = np.append(tpr,mean_tpr)

mean_fpr=np.sort(mean_fpr)
mean_tpr=np.sort(mean_tpr)
mean_auc = auc(mean_fpr, mean_tpr)
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of SVM with presence data \n(AUC = %0.2f) (accuracy = %0.2f) 3 folder' % (mean_auc,accuracy_pre))


mean_tpr = np.array(0.0)
mean_fpr = np.array(0.0)
for (train,test) in cv:
  probas = sentiment_bay_m.fit(data[train], target[train]).predict_proba(data[test])
  fpr, tpr, thresholds = roc_curve(target[test], probas[:, 1])
  mean_fpr = np.append(fpr,mean_fpr)
  mean_tpr = np.append(tpr,mean_tpr)

mean_fpr=np.sort(mean_fpr)
mean_tpr=np.sort(mean_tpr)
mean_auc = auc(mean_fpr, mean_tpr)
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Multinomial Naive Bayes with frequency data \n(AUC = %0.2f) (accuracy = %0.2f) 3 folder' % (mean_auc,accuracy_bay_m))

mean_tpr = np.array(0.0)
mean_fpr = np.array(0.0)
for (train,test) in cv:
  probas = sentiment_bay_m.fit(data_pre[train], target[train]).predict_proba(data_pre[test])
  fpr, tpr, thresholds = roc_curve(target[test], probas[:, 1])
  mean_fpr = np.append(fpr,mean_fpr)
  mean_tpr = np.append(tpr,mean_tpr)

mean_fpr=np.sort(mean_fpr)
mean_tpr=np.sort(mean_tpr)
mean_auc = auc(mean_fpr, mean_tpr)
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Multinomial Naive Bayes with presence data \n(AUC = %0.2f) (accuracy = %0.2f) 3 folder' % (mean_auc,accuracy_bay_pre_m))
'''
mean_tpr = np.array(0.0)
mean_fpr = np.array(0.0)
for (train,test) in cv:
  probas = sentiment_bay_g.fit(data[train], target[train]).predict_proba(data[test])
  fpr, tpr, thresholds = roc_curve(target[test], probas[:, 1])
  mean_fpr = np.append(fpr,mean_fpr)
  mean_tpr = np.append(tpr,mean_tpr)

mean_fpr=np.sort(mean_fpr)
mean_tpr=np.sort(mean_tpr)
mean_auc = auc(mean_fpr, mean_tpr)
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Gaussian Naive Bayes with frequency data \n(AUC = %0.2f) (accuracy = %0.2f) 3 folder' % (mean_auc,accuracy_bay_g))

mean_tpr = np.array(0.0)
mean_fpr = np.array(0.0)
for (train,test) in cv:
  probas = sentiment_bay_b.fit(data[train], target[train]).predict_proba(data[test])
  fpr, tpr, thresholds = roc_curve(target[test], probas[:, 1])
  mean_fpr = np.append(fpr,mean_fpr)
  mean_tpr = np.append(tpr,mean_tpr)

mean_fpr=np.sort(mean_fpr)
mean_tpr=np.sort(mean_tpr)
mean_auc = auc(mean_fpr, mean_tpr)
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Bernoulli Naive Bayes with frequency data \n(AUC = %0.2f) (accuracy = %0.2f) 3 folder' % (mean_auc,accuracy_bay_b))
'''

x = np.array([0,0.6,1])
y = np.array([0,0.65,1])
x_b = np.arange(0,1.01,0.01)
y_b = np.arange(0,1.01,0.01)
'''
plt.plot(x,y,label='ROC of using statistics of the data \n(AUC = %0.2f) (accuracy = %0.2f) (tie = %0.2f)' %(auc(x,y),0.63,0.14))
'''
plt.plot(x_b,y_b,'k--')


plt.xlim([0, 1])
plt.ylim([0, 1])
plt.title('Comparison between frequency and presence value')
plt.xlabel('$P_F$')
plt.ylabel('$P_D$')
plt.legend(loc="lower right",fontsize = 'x-small')
plt.grid()
plt.show()




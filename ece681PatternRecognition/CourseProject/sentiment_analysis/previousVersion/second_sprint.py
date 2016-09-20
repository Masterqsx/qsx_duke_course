#-*- coding: utf-8 -*-


import re,os,glob,copy
from sklearn import datasets,svm,cross_validation,tree,decomposition
from sklearn.metrics import roc_curve, auc
from sklearn.naive_bayes import MultinomialNB,GaussianNB,BernoulliNB
import numpy as np
import matplotlib.pyplot as plt
import nltk,string




wordcount={}

with open(os.path.join(os.getcwd(),"test.txt")) as f:
  for word in f.read().split():
    if (len(re.findall("[^a-zA-Z]",word))!=0):
      continue
    if word not in wordcount:
      wordcount[word] = 1
    else:
      wordcount[word] += 1

wordcount=sorted(wordcount.iteritems(), key=lambda (k,v): (v,k))


feature=[]
pos=[]
neg=[]
with open(os.path.join(os.getcwd(),"positive-words.txt")) as p,open(os.path.join(os.getcwd(),"negative-words.txt")) as n:
  for w in p.read().split():
    pos.append(w)
  for w in n.read().split():
    neg.append(w)


for wo in wordcount:
    if (wo[0] in pos) | (wo[0] in neg):
      feature.append(wo[0])

feature.append('\?')
feature.append('\!')
print len(feature)
#feature=['love','wonderful','best','great','superb','stil','beautiful','bad','worst','stupid','waste','boring','\?','\!']
def analyzer(f1):
    global feature
    f_words=copy.deepcopy(feature)
    index=range(len(f_words))
    f_words=zip(f_words,index)
    f_count=[0]*len(f_words)
    for line in f1:
     for f_word in f_words :
       ma = re.findall(f_word[0],line)
       if len(ma)!=0 :
         f_count[f_word[1]] = f_count[f_word[1]] + len(ma)

    return f_count

nu = 0;
co = 0.0;
data = []
target = []
for root, dirs, files in os.walk("./review0"):
  it = glob.glob(os.path.join(root,"*.txt"))
  flag = 0
  if re.search("neg",root) :
    flag = 1
  if len(it)==0:
    continue
  for path in it :
    with open(path) as f_input:
      data.append(analyzer(f_input))
      target.append(flag)






data_pre = copy.deepcopy(data)
for i in range(len(data_pre)):
  for j in range(len(data_pre[i])):
    if data_pre[i][j]>0:
      data_pre[i][j]=1

data = np.array(data)
data_pre = np.array(data_pre) 
target = np.array(target)

#pca = decomposition.PCA(n_components=2000)
#pca.fit(data)
#data=pca.transform(data)


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
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of SVM with 3 folds \n(AUC = %0.2f) (accuracy = %0.2f)' % (mean_auc,accuracy))

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
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Multinomial Naive Bayes with 3 folds \n(AUC = %0.2f) (accuracy = %0.2f)' % (mean_auc,accuracy_bay_m))

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
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Gaussian Naive Bayes with 3 folds \n(AUC = %0.2f) (accuracy = %0.2f)' % (mean_auc,accuracy_bay_g))

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
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of Bernoulli Naive Bayes with 3 folds \n(AUC = %0.2f) (accuracy = %0.2f)' % (mean_auc,accuracy_bay_b))
"""
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
plt.plot(mean_fpr, mean_tpr,label='Mean ROC of M pre with 3 folds \n(AUC = %0.2f) (accuracy = %0.2f)' % (mean_auc,accuracy_bay_pre_m))
"""
x = np.array([0,0.6,1])
y = np.array([0,0.65,1])
x_b = np.arange(0,1.01,0.01)
y_b = np.arange(0,1.01,0.01)
plt.plot(x,y,label='ROC of using statistics of the data \n(AUC = %0.2f) (accuracy = %0.2f) (tie = %0.2f)' %(auc(x,y),0.63,0.14))
plt.plot(x_b,y_b,'k--')


plt.xlim([0, 1])
plt.ylim([0, 1])
plt.title('Sentiment classification with mutiple approaches')
plt.xlabel('$P_F$')
plt.ylabel('$P_D$')
plt.legend(loc="lower right",fontsize = 'x-small')
plt.grid()
plt.show()



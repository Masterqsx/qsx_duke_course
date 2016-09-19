#-*- coding: utf-8 -*-


import re,os,glob,copy
from sklearn import datasets,svm,cross_validation
from sklearn.metrics import roc_curve, auc
import numpy as np
import matplotlib.pyplot as plt

def analyzer(f1):
  pos_words=['love','wonderful','best','great','superb','stil','beautiful']
  neg_words=['bad','worst','stupid','waste','boring','\?','\!']
  index=range(7)
  pos_words=zip(pos_words,index)
  neg_words=zip(neg_words,index)
  p_count=[0]*7
  n_count=[0]*7
  for line in f1:
    for p_word in pos_words :
      ma = re.findall(p_word[0],line)  
      if len(ma)!=0 :
        p_count[p_word[1]] = p_count[p_word[1]] + len(ma)

    for n_word in neg_words :
      ma = re.findall(n_word[0],line) 
      if len(ma)!=0 :
        n_count[n_word[1]] = n_count[n_word[1]] + len(ma)

  return p_count+n_count

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

sentiment = svm.SVC(kernel="linear",probability=True)

'''
sentiment.fit(data,target)
for root, dirs, files in os.walk("./review1"):
  it = glob.glob(os.path.join(root,"*.txt"))
  flag = 1
  if re.search("neg",root) :
    flag = 0
  if len(it)==0:
    continue
  for path in it :
    with open(path) as f_input:
      co = co + 1
      test = np.array(analyzer(f_input))
      anay_re = sentiment.predict(test.reshape(1,-1))+flag;
      if anay_re == 1 :
        nu = nu + 1
#print nu/co
'''

accuracy = np.mean(cross_validation.cross_val_score(sentiment,data,target))
accuracy_pre = np.mean(cross_validation.cross_val_score(sentiment,data_pre,target))

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
plt.plot(mean_fpr, mean_tpr,'red',label='Mean ROC of SVM with 3 folds \n(AUC = %0.2f) (accuracy = %0.2f)' % (mean_auc,accuracy))
x = np.array([0,0.6,1])
y = np.array([0,0.65,1])
x_b = np.arange(0,1.01,0.01)
y_b = np.arange(0,1.01,0.01)
plt.plot(x,y,label='ROC of statistics of the data\n(AUC = %0.2f) (accuracy = %0.2f) (tie = %0.2f)' %(auc(x,y),0.63,0.14))
plt.plot(x_b,y_b,'k--')

plt.xlim([0, 1])
plt.ylim([0, 1])
plt.title('Sentiment classification with SVM and 14-word feature')
plt.xlabel('$P_F$')
plt.ylabel('$P_D$')
plt.legend(loc="lower right",fontsize = 'x-small')
plt.grid()
plt.show()

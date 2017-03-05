#-*- coding: utf-8 -*-


import re,os,glob,copy
from sklearn import datasets,svm,cross_validation,tree,decomposition
from sklearn.metrics import roc_curve, auc
from sklearn.naive_bayes import MultinomialNB,GaussianNB,BernoulliNB
import numpy as np
import matplotlib.pyplot as plt
import nltk,string
from nltk.corpus import sentiwordnet as swn



wordcount={}

with open(os.path.join(os.getcwd(),"../Dataset/test.txt")) as f:
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
with open(os.path.join(os.getcwd(),"../Dataset/positive-words.txt")) as p,open(os.path.join(os.getcwd(),"../Dataset/negative-words.txt")) as n:
  for w in p.read().split():
    wu = unicode(w, errors='ignore')
    senti = swn.senti_synsets(wu, 'a')
    if len(senti) > 0:
      pos.append(w)
  for w in n.read().split():
    wu = unicode(w, errors='ignore')
    senti = swn.senti_synsets(wu, 'a')
    if len(senti) > 0:
      neg.append(w)


for wo in wordcount:
    if (wo[0] in pos) | (wo[0] in neg):
      feature.append(wo[0])

feature.append('\?')
feature.append('\!')
#feature=['love','wonderful','best','great','superb','stil','beautiful','bad','worst','stupid','waste','boring','\?','\!']
def analyzer(f1):
    global feature
    f_words=copy.deepcopy(feature)
    index=range(len(f_words))
    f_words=zip(f_words,index)
    f_count=[0]*len(f_words)
    for line in f1:
     for f_word in f_words :
       senti = swn.senti_synsets(f_word[0], 'a')
       ori = 0
       if len(senti) > 0:
        ori = float(senti[0].pos_score() - senti[0].neg_score())
       ma = re.findall(f_word[0],line)
       if len(ma)!=0 :
         f_count[f_word[1]] = f_count[f_word[1]] + len(ma)*ori

    return f_count

nu = 0;
co = 0.0;
data = []
target = []
for root, dirs, files in os.walk("../Dataset/review0"):
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
print data.shape

np.savetxt('../Dataset/data.txt',data,fmt="%10.2f",delimiter=';');
np.savetxt('../Dataset/data_pre.txt',data_pre,fmt="%10.2f",delimiter=';');
np.savetxt('../Dataset/target.txt',target,fmt="%10.2f",delimiter=';');

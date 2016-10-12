from nltk.corpus import wordnet as wn
import nltk
import unicodedata, sys

def cleanInput(word):
    word = word.strip().lower()
    return word
 
def cleanPun(text):
    tbl = dict.fromkeys(i for i in xrange(sys.maxunicode) if unicodedata.category(unichr(i)).startswith('P'))
    text = text.translate(tbl)
    text = cleanInput(text)
    return text

class score:
    gloss1 = []
    gloss2 = []
    dp = []
    def __init__(self, i_gloss1, i_gloss2):
        self.gloss1 = i_gloss1.split(' ')
        self.gloss2 = i_gloss2.split(' ')
        self.dp = [[0 for i in range((len(self.gloss2)+1))] for j in range((len(self.gloss1)+1))] 

    def lcs(self):
        for i in range(len(self.gloss1)+1):
            for j in range(len(self.gloss2)+1):
                try:
                    if (i == 0 or j == 0):
                        self.dp[i][j] = 0;
                    elif (self.gloss1[i-1] == self.gloss2[j-1]):
                        text1 = nltk.word_tokenize(self.gloss1[i-1])
                        text2 = nltk.word_tokenize(self.gloss2[i-1])
                        if (nltk.pos_tag(text1)[0][1] == 'IN' or nltk.pos_tag(text1)[0][1] == 'PRP' or nltk.pos_tag(text1)[0][1] == 'DT'):
                            continue
                        if (nltk.pos_tag(text2)[0][1] == 'IN' or nltk.pos_tag(text2)[0][1] == 'PRP' or nltk.pos_tag(text2)[0][1] == 'DT'):
                            continue
                        self.dp[i][j] = 1 + self.dp[i-1][j-1];
                    else:
                        self.dp[i][j] = max(self.dp[i-1][j], max(self.dp[i][j-1], self.dp[i-1][j-1]))
                except:
                    pass

    def getScore(self):
        self.lcs();
        return pow(self.dp[-1][-1], 2)

f = open("RG_word.txt", "r");
out = open("res.txt", "w");
for line in f:
    words = line.split(',', 2)
    words[0] = cleanInput(words[0])
    words[1] = cleanInput(words[1])
    sc = 0.0
    syns1 = wn.synsets(words[0])
    syns2 = wn.synsets(words[1])
    for i in range(len(syns1)):
        for j in range(len(syns2)):
            scorer = score(cleanPun(syns1[i].definition()), cleanPun(syns2[j].definition()))
            sc = sc + float(scorer.getScore())/float(len(syns1))/float(len(syns2))
            syns1_hyper = syns1[i].hypernyms()
            syns2_hyper = syns2[j].hypernyms()
            for m in range(len(syns1_hyper)):
                for n in range(len(syns2_hyper)):
                    scorer = score(cleanPun(syns1_hyper[m].definition()), cleanPun(syns2_hyper[n].definition()))
                    sc = sc + float(scorer.getScore())/float(len(syns1_hyper))/float(len(syns2_hyper))
            syns1_hypo = syns1[i].hyponyms()
            syns2_hypo = syns2[j].hyponyms()
            for m in range(len(syns1_hypo)):
                for n in range(len(syns2_hypo)):
                    scorer = score(cleanPun(syns1_hypo[m].definition()), cleanPun(syns2_hypo[n].definition()))
                    sc = sc + float(scorer.getScore())/float(len(syns1_hypo))/float(len(syns2_hypo))
    out.write(words[0]+" "+words[1]+" "+str(sc)+"\n");

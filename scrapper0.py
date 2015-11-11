from bs4 import BeautifulSoup
import urllib2
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

a_prob1 = "https://www.wordnik.com/words/"+str(sys.argv[1])
page = urllib2.urlopen(a_prob1)

soup = BeautifulSoup(page.read())

prob = soup.findAll("div", {"class": "guts active"})
selec = str(prob[0])

soup = BeautifulSoup(selec)
dicts = soup.findAll("h3", {"class":"source"})
prob = soup.findAll("ul")

f = open(sys.argv[1], 'w')
sys.stdout = f

print(soup.get_text())

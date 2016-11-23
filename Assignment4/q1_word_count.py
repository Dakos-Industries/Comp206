#!/usr/bin/python
import sys
def main(path):
	file = open(path,"r")
	wordcount = {}
	for word in file.read().split():
		compare = word.lower()
		if "-" in compare:
			compare = compare.split("-")
			for i in compare:
				if i not in wordcount:
					wordcount[i] = 1
				else:
					wordcount[i] +=1
		elif compare not in wordcount:
			wordcount[compare] = 1
		else:
			wordcount[compare] += 1

	for k,v in wordcount.items():
		print (k,v)
main(sys.argv[1])

#!/usr/bin/python
# Author: Spiros Mavroidakos
# Version: 2.0
''' This Python3 program takes in a text file via the command line
and counts the frequency of the word pairs and prints the results 
to the screen
'''
import sys
from operator import itemgetter
def main(path):
	file = open(path,"r")
	wordcount = {}
	wholetext = file.read().split()
	file.close();
	prevword = wholetext[0].lower()
	del wholetext[0]
	for word in wholetext:
		compare = word.lower()
		newpair = prevword + " " + compare
		if "-" in compare:
			compare = compare.split("-")
			for i in compare:
				temp = prevword + " " + i
				if temp not in wordcount:
					wordcount[temp] = 1
					prevword = i
				else:
					wordcount[temp] +=1
					prevword = i
		elif newpair not in wordcount:
			wordcount[newpair] = 1
			prevword = compare
		else:
			wordcount[newpair] += 1
			prevword = compare

	for key, val in sorted(wordcount.items(), key = itemgetter(1), reverse = True):
		print (key,val)
main(sys.argv[1])

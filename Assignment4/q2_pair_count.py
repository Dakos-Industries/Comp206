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
	wordFreq = {}
	wholetext = file.read().split()
	file.close();
	prevword = wholetext[0].lower()
	del wholetext[0]
	for word in wholetext:
		currentWord = word.lower()
		newpair = prevword + " " + currentWord
		if "-" in currentWord:
			currentWord = currentWord.split("-")
			for i in currentWord:
				temp = prevword + " " + i
				if temp not in wordFreq:
					wordFreq[temp] = 1
					prevword = i
				else:
					wordFreq[temp] +=1
					prevword = i
		elif newpair not in wordFreq:
			wordFreq[newpair] = 1
			prevword = currentWord
		else:
			wordFreq[newpair] += 1
			prevword = currentWord

	for key, val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
		print (key,val)
main(sys.argv[1])

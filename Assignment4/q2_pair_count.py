#!/usr/bin/python
# Author: Spiros Mavroidakos
# Version: 3.0
''' This Python3 program takes in a text file via the command line
and counts the frequency of the word pairs and prints the results 
to the screen
'''
import sys
import os
from operator import itemgetter
def main(path):
	if os.path.exists(path) == False:
		print("File does not exist. Try Again with existing file.")
		return None
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
if len(sys.argv) == 1:
	print("Please enter at least one file as an argument")
	sys.exit(0)
main(sys.argv[1])

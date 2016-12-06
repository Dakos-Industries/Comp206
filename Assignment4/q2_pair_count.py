#!/usr/bin/python
# Author: Spiros Mavroidakos
# Version: 3.0
''' This Python3 program takes in a text file via the command line
and counts the frequency of the word pairs and prints the results 
to the screen
'''
import sys
import os
import re, string
from operator import itemgetter
def main(path):
	if os.path.exists(path) == False:
		print("File does not exist. Try Again with existing file.")
		return None
	file = open(path,"r")
	regex = re.compile('[^a-zA-Z0-9]')
	wordFreq = {}
	wholetext = file.read().split()
	file.close();
	prevword = regex.sub("",wholetext[0].lower())
	del wholetext[0]
	for word in wholetext:
		currentWord = word.lower()
		newpair = prevword + " " + regex.sub("", word.lower())
		if "-" in currentWord:
			currentWord = currentWord.split("-")
			for i in currentWord:
				temp = prevword + " " + regex.sub("", i)
				if temp not in wordFreq and regex.sub("",i) != "":
					wordFreq[temp] = 1
					prevword = regex.sub("", i)
				elif regex.sub("",i) != "":
					wordFreq[temp] +=1
					prevword = regex.sub("", i)
		elif newpair not in wordFreq:
			wordFreq[newpair] = 1
			prevword = regex.sub("", currentWord)
		else:
			wordFreq[newpair] += 1
			prevword = regex.sub("", currentWord)
	for key, val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
		print key,val
if len(sys.argv) == 1:
	print("Please enter at least one file as an argument")
	sys.exit(0)
main(sys.argv[1])

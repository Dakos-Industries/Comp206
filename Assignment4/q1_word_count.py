#!/usr/bin/python
# Author : Spiros Mavroidakos
# Version 2.0
'''This Python3 program takes in a file path through the command line
and reads the file specified in the path. The program then finds the frequency 
of every word and prints the results to the screen
'''
import sys
from operator import itemgetter
def main(path):
	file = open(path,"r")
	wordFreq = {}
	for word in file.read().split():
		compare = word.lower()
		if "-" in compare:
			compare = compare.split("-")
			for i in compare:
				if i not in wordFreqt:
					wordFreq[i] = 1
				else:
					wordFreq[i] +=1
		elif compare not in wordcount:
			wordFreq[compare] = 1
		else:
			wordFreq[compare] += 1
	for key, val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
		print (key,val)
main(sys.argv[1])

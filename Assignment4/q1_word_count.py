#!/usr/bin/python
# Author : Spiros Mavroidakos
# Version 3.0
'''This Python3 program takes in a file path through the command line
and reads the file specified in the path. The program then finds the frequency 
of every word and prints the results to the screen
'''
import os
import sys
import re, string
from operator import itemgetter
def main(path):
	count = 0
	if os.path.exists(path) == False:
		print("File does not exist. Please enter an existing file")
		return None
	file = open(path,"r")
	regex = re.compile('[^a-zA-z0-9]')
	wordFreq = {}
	for word in file.read().split():
		compare = word.lower()
		if "-" in compare:
			compare = compare.split("-")
			for i in compare:
				if regex.sub("",i) not in wordFreq:
					wordFreq[regex.sub("",i)] = 1
				else:
					wordFreq[regex.sub("",i)] +=1
		elif regex.sub("",compare) not in wordFreq:
			wordFreq[regex.sub("",compare)] = 1
		else:
			wordFreq[regex.sub("",compare)] += 1
	
	for key, val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
		print key,val
if len(sys.argv) == 1:
	print("Please enter at least one file as an argument")
	sys.exit(0)
main(sys.argv[1])

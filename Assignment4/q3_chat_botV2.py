#!/usr/bin/python
#Author Spiros Mavroidakos
#Version 3.0
''' Solution to Assignment 4 question 3 chat bot'''
import os
import re, string
import sys
import random
from operator import itemgetter

wordFreq = {}
endWord = []
regex = re.compile('[^a-zA-Z0-9]')
#This function will save each word pair to the wordFreq dictionary
def database(path):
	if os.path.exists(path) == False:
		print("File does not exist. Try Again with existing file.")
		return None
	file = open(path,"r")
	regex = re.compile('[^a-zA-Z0-9]')
	wholetext = file.read().split()
	file.close();
	prevword = regex.sub("",wholetext[0].lower())
	del wholetext[0]
	for word in wholetext:
		currentWord = word.lower()
		if word[len(word)-1] == ".":
			newpair = prevword + " " + word.lower()
		else:
			newpair = prevword + " " + regex.sub("", word.lower())
		if "-" in currentWord:
			currentWord = currentWord.split("-")
			for i in currentWord:
				if len(i) > 0:
					if i[len(i)-1] == "":
						temp = prevword + " " + i
					else:
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
def findPair(word):
	count = 0
	string = word.lower()
	comparison = [] 
	while True:
		for key in wordFreq:
			comparison = key.split(" ")
			if count == 20:
				break
			if comparison[0].lower() == string:
				if (count == 0):
					print comparison[1].capitalize(), 
					string = comparison[1].lower()
				else:
					print comparison[1].lower(),
					string = comparison[1].lower()
				count += 1
				if comparison[1][len(comparison[1])-1] == ".":
					return None
				if count == 20:
					print ".",
					return None
		if count == 0 :
			break
			
	if count == 0:
		
		if (word + ".") in endWord:
			print(word.capitalize(),)
			return None  
		tmp = random.choice(list(wordFreq.keys())).split(" ")
		string = tmp[1]
		while count != 20:
			for ite in wordFreq:
				comparison = ite.split(" ")
				if comparison[0].lower() == string:
					if (count == 0):
						print comparison[1].capitalize(), 
						string = comparison[1].lower()
					else:
						print comparison[1].lower(),
						string = comparison[1].lower() 
					count += 1
					if comparison[1][len(comparison[1])-1] == ".":
						return None
					if count == 20:
						print ".",
						return None 
		
#Checks to see if at least one text source has been entered
if len(sys.argv)<= 1:
	print("Please enter at least one file to use as a basis")
	sys.exit()
del sys.argv[0] 
#runs the database function for each text
for word in sys.argv:
	database(word)
while True:
	userInput = raw_input("Send: \t")
	userInput = regex.sub("", userInput)
	wordToCompare = userInput.split(" ")
	word = wordToCompare[len(wordToCompare) - 1]
	print "Received: \t", 
	findPair(word)
	print("")
#for key,val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
#	print(key, val)

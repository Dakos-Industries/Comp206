#!/usr/bin/python
#Author Spiros Mavroidakos
#Version 1.0
''' Solution to Assignment 4 question 3 chat bot'''
import sys
import random
from operator import itemgetter

wordFreq = {}
#This function will save each word pair to the wordFreq dictionary
def database(path):
	
	file = open(path,"r")
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
def findPair(word):
	count = 0
	string = word
	comparison = ""
	for key in wordFreq:
		comparison = ""
		for char in key:
			comparison += char 
			if string == comparison:
				if (count == 0):
					print(key.capitalize(), end = " ")
				else:
					print(key, end = " ")
				count += 1
				if key[len(key)-1] == ".":
					print("")
					return None
			elif (char == " "):
				comparison = ""
			if count == 10 :
				print(".", end = "")
				return None
	if count == 0:
		print (random.choice(list(wordFreq.keys())).capitalize(), end = " ")
	count = 0
	print(".")
			
#Checks to see if at least one text source has been entered
if len(sys.argv)<= 1:
	print("Please enter at least one file to use as a basis")
	sys.exit()
del sys.argv[0] 
#runs the database function for each text
for word in sys.argv:
	database(word)
while True:
	userInput = input("Send: \t")
	wordToCompare = userInput.split(" ")
	word = wordToCompare[len(wordToCompare) - 1]
	print("Received: \t", end = "")
	findPair(word)
#for key,val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
#	print(key, val)

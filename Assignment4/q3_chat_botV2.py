#!/usr/bin/python3
#Author Spiros Mavroidakos
#Version 3.0
''' Solution to Assignment 4 question 3 chat bot'''
import os
import sys
import random
from operator import itemgetter

wordFreq = {}
endWord = []
#This function will save each word pair to the wordFreq dictionary
def database(path):
	if os.path.exists(path) == False:
		print("File does not exist. Please enter existing file.")
		return None
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
	endWord.append(prevword)
def findPair(word):
	count = 0
	string = word
	comparison = ""
	for key in wordFreq:
		comparison = ""
		if count == 10 :
			break
		for char in key:
			comparison += char 
			if (string == comparison) and ((key[len(comparison)] == " ") or (key[len(comparison)] == ".")) :
				if (count == 0):
					print(key.capitalize(), end = " ")
				else:
					print(key.lower(), end = " ")
				count += 1
				if key[len(key)-1] == ".":
					return None
			elif (char == " "):
				comparison = ""
				break
	if count == 0:
		
		if (word + ".") in endWord:
			print(word.capitalize(), end = ".")
			return None 
		tmp = random.choice(list(wordFreq.keys())).capitalize()
		if tmp[len(tmp)-1] == ".":
			print(tmp, end = "")
		else:
			print(tmp, end = ".")
		count = 0
		return None
	else: 
		while(count < 10):
			string = random.choice(list(wordFreq.keys())).capitalize()
			print(string.lower(), end = " ")
			count += 1
			if string[len(string)-1] == ".":
				return None
	if count == 10 :
		print(".", end = "")
		
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
	print("")
#for key,val in sorted(wordFreq.items(), key = itemgetter(1), reverse = True):
#	print(key, val)

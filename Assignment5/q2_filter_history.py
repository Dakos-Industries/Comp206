#/usr/bin/python

''' 
	Author: Spiros Mavroidakos
	Version: V2.0
	Description: Solution to Assignment 5 question 2
'''
import ctypes
import sys
import pickle
import os
# List to save the image states
historia = []
# Same filtering method as done in Q1
def filt():
	# check if the result image exists
	if os.path.isfile("result.bmp") == False:
		print "No file loaded! Please load a file."
		return None
	f = open('history.pickle','rb')
	historia = pickle.load(f)
	pos = pickle.load(f)
	f.close()
	if pos != 0 and len(historia) != 0:
		pos += 1	
		del historia [pos:len(historia)]
	else:
		pos = 0
		del historia [pos:len(historia)]
	# Import the shared library to perform the filter
	fastFilt = ctypes.cdll.LoadLibrary("./libfast_filter.so")
	#Open the image, get the data and send the data to the undo pickle dump file
	in_img = open('result.bmp', 'rb')
	in_img_data = in_img.read()
	if pos  >= len(historia):
		historia.append(in_img_data)
	else:
		historia[pos] = in_img_data
	in_img.close()

	width = (int)(sys.argv[2])

	#Read the input filter information as done in convolve_slow.py
	weights = []
	i = 0
	while (i < (width*width)):
		weights.append(float(sys.argv[3+i]))
		i +=1

	#convert to ctypes
	weights = (ctypes.c_float *len(weights))(*weights)

	out_img_data = " " *len(in_img_data)

	#Perform Filter and write image to result.bmp
	fastFilt.doFiltering(in_img_data, weights, width, out_img_data)
	out_img = open("result.bmp", "wb")
	out_img.write(out_img_data)
	out_img.close()
	if pos == 0:
		pos += 1
	f = open('history.pickle','wb')
	pickle.dump(historia,f)
	pickle.dump(pos,f)
	f.close()
def load():
	#Load in the data from the given bmp file
	in_img = open(sys.argv[2], 'rb')
	in_img_data = in_img.read()
	in_img.close()
 	out_img = open("result.bmp", "wb")
	out_img.write(in_img_data)
	out_img.close()
	pos = 0
	# Delete the old pickle dump files if any exist
	if os.path.isfile("history.pickle") == True:
		os.remove("history.pickle")
	f = open('history.pickle','wb')
	pickle.dump(historia,f)
	pickle.dump(pos,f)
	f.close()

def undo():
	#cheching if undo was done before
	if os.path.isfile("history.pickle") == False:
		print "Nothing to undo!"
		return None
	f = open('history.pickle','rb')
	historia = pickle.load(f)
	pos = pickle.load(f)
	f.close()
	# checks to see if undo is possible
	if pos == 0:
		print "Can't undo at earliest change"
		return None
	else:
		
		# load the previous data and undo the previous steps
		redo = open('result.bmp', 'rb')
		redo_data = redo.read()
		if pos == len(historia):
			historia.append(redo_data)
		else:
			historia[pos] = redo_data
		pos -= 1
		out_img = open("result.bmp", "wb")
		out_img.write(historia[pos])
		out_img.close()
		f = open('history.pickle','wb')
		pickle.dump(historia,f)
		pickle.dump(pos,f)
		f.close()
def redo():
	#cheching if file exists
	if os.path.isfile("history.pickle") == False:
		print "Nothing to undo!"
		return None
	f = open('history.pickle','rb')
	historia = pickle.load(f)
	pos = pickle.load(f)
	f.close()
	# checking to see if we can redo
	if pos+1 >= (len(historia)):
		print "At latest change"
		return None
	else:
		
		# load the  data and redo the previous steps
		pos += 1
		out_img = open("result.bmp", "wb")
		out_img.write(historia[pos])
		out_img.close()
		f = open('history.pickle','wb')
		pickle.dump(historia,f)
		pickle.dump(pos,f)
		f.close()


# checking user input	
if sys.argv[1] == "load" :
	load()
if sys.argv[1] == "filter":
	filt()
if sys.argv[1] == "undo":
	undo()
if sys.argv[1] == "redo":
	redo()

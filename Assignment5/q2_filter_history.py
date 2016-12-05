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
# Same filtering method as done in Q1
def filt():
	# check if the result image exists
	if os.path.isfile("result.bmp") == False:
		print "No file loaded! Please load a file."
		return None
	# Import the shared library to perform the filter
	fastFilt = ctypes.cdll.LoadLibrary("./libfast_filter.so")
	#Open the image, get the data and send the data to the undo pickle dump file
	in_img = open('result.bmp', 'rb')
	in_img_data = in_img.read()
	pickle.dump(in_img_data, open("undo.p","wb"))
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
def load():
	#Load in the data from the given bmp file
	in_img = open(sys.argv[2], 'rb')
	in_img_data = in_img.read()
	in_img.close()
 	out_img = open("result.bmp", "wb")
	out_img.write(in_img_data)
	out_img.close()
	# Delete the old pickle dump files if any exist
	if os.path.isfile("undo.p") == True:
		os.remove("undo.p")
	if os.path.isfile("redo.p") == True:
		os.remove("redo.p")
def undo():
	#cheching if undo was done before
	if os.path.isfile("undo.p") == False:
		print "Nothing to undo!"
		return None
	# load the previous data and undo the previous steps
	undo_data = pickle.load(open("undo.p","rb"))

	redo = open('result.bmp', 'rb')
	redo_data = redo.read()
	pickle.dump(redo_data, open("redo.p","wb"))
	redo.close()

	out_img = open("result.bmp", "wb")
	out_img.write(undo_data)
	out_img.close()
def redo():
	# checking to see if redo is possible
	if os.path.isfile("redo.p") == False:
		print "Nothing to redo!"
		return None
	# load the data and perform the redo
	redo_data = pickle.load(open("redo.p","rb"))

	undo = open('result.bmp', 'rb')
	undo_data = undo.read()
	pickle.dump(undo_data, open("undo.p","wb"))
	undo.close()

	out_img = open("result.bmp", "wb")
	out_img.write(redo_data)
	out_img.close()


# checking user input	
if sys.argv[1] == "load" :
	load()
if sys.argv[1] == "filter":
	filt()
if sys.argv[1] == "undo":
	undo()
if sys.argv[1] == "redo":
	redo()

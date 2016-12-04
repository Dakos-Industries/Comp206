#/usr/bin/python

''' 
	Author: Spiros Mavroidakos
	Version: V2.0
	Description: Solution to Assignment 5 question 2
'''
import ctypes
import sys
import pickle
def filt():
	fastFilt = ctypes.cdll.LoadLibrary("./libfast_filter.so")

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

	#Perform FIlter
	fastFilt.doFiltering(in_img_data, weights, width, out_img_data)
	out_img = open("result.bmp", "wb")
	out_img.write(out_img_data)
	out_img.close()
def load():
	in_img = open(sys.argv[2], 'rb')
	in_img_data = in_img.read()
	in_img.close()
 	out_img = open("result.bmp", "wb")
	out_img.write(in_img_data)
	out_img.close()
def undo():
	undo_data = pickle.load(open("undo.p","rb"))

	redo = open('result.bmp', 'rb')
	redo_data = redo.read()
	pickle.dump(redo_data, open("redo.p","wb"))
	redo.close()

	out_img = open("result.bmp", "wb")
	out_img.write(undo_data)
	out_img.close()
def redo():
	redo_data = pickle.load(open("redo.p","rb"))

	undo = open('result.bmp', 'rb')
	undo_data = undo.read()
	pickle.dump(undo_data, open("undo.p","wb"))
	undo.close()

	out_img = open("result.bmp", "wb")
	out_img.write(redo_data)
	out_img.close()


	
if sys.argv[1] == "load" :
	load()
if sys.argv[1] == "filter":
	filt()
if sys.argv[1] == "undo":
	undo()
if sys.argv[1] == "redo":
	redo()

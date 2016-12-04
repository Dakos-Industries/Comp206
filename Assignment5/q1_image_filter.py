#/usr/bin/python

''' 
	Author: Spiros Mavroidakos
	Version: V2.0
	Description: Solution to Assignment 5 question 1
'''
import ctypes
import sys

fastFilt = ctypes.cdll.LoadLibrary("./libfast_filter.so")
in_img = open(sys.argv[1], 'rb')
in_img_data = in_img.read()
in_img.close()
width = (int)(sys.argv[3])

#Read the input filter information as done in convolve_slow.py
weights = []
i = 0
while (i < (width*width)):
	weights.append(float(sys.argv[4+i]))
	i +=1

#convert to ctypes
weights = (ctypes.c_float *len(weights))(*weights)

out_img_data = " " *len(in_img_data)

#Perform FIlter
fastFilt.doFiltering(in_img_data, weights, width, out_img_data)
out_img = open(sys.argv[2], "wb")
out_img.write(out_img_data)
out_img.close()

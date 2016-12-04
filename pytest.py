#!/usr/bin/python
''' Test Python program'''

def main():
	thing = {" word count": 1, " daisy dog" : 2, " the cat":3}
	string = input("Hello world")
	comparison = ""
	for key in thing:
		for char in key:
			comparison += char
		#	print("comparison: " + comparison)
			if string == comparison:
				print(key)
			elif (char == " "):
				comparison = ""
main()

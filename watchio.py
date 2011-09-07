#!/usr/bin/env python


import sys

def warning(msg):
	sys.stdout.write("Warning:\n%s\n" % msg)
	
	
def error(msg):
	sys.stdout.write("Error:\n%s\n" % msg)
	

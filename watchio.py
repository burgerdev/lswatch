#!/usr/bin/env python

import vcheck


import sys

levels = {'debug': 5, 'info': 3, 'warning': 2, 'error': 1, 'quiet': 0}

debuglevel = 'info'



def debug(msg):
	if levels[debuglevel]>=levels['debug']:
		sys.stdout.write("Debug:\n%s\n" % msg)

def info(msg):
	if levels[debuglevel]>=levels['info']:
		sys.stdout.write("Info:\n%s\n" % msg)

def warning(msg):
	if levels[debuglevel]>=levels['warning']:
		sys.stdout.write("Warning:\n%s\n" % msg)
	
	
def error(msg):
	if levels[debuglevel]>=levels['error']:
		sys.stdout.write("Error:\n%s\n" % msg)
	

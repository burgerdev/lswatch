#!/usr/bin/env python

import vcheck

import socket
import sys
import time
import signal
import configparser

import socketmsg as sm

num_devices = 4
sQuit = "q"


def sigint_handle(num,frame):
    print("Exit on interrupt.")
    sys.exit(0)


if __name__=="__main__":

	# set signal handling
	signal.signal(signal.SIGINT,sigint_handle)

	sock = socket.socket()

	conf = configparser.ConfigParser()
	conf.read('config.txt')
	port = int(conf.get('communication', 'port'))
	host = conf.get('communication','host')

	sock.connect((host,port))

	sock.send(sm.hellomsg(num_devices))
    
	cont = True
	while cont:
		data = sys.stdin.readline().strip()
		if data.isdigit():
			num = int(data)
			
			if not num < num_devices:
				print("Device %d out of range (max: %d)" % (num,num_devices))
			else:
				t = int(round(time.time()*1000))
				msg = sm.encode([(num,t)])
				sock.send(msg)
		else:
			if data.lower() == sQuit:
				cont = False
			else:
				print("Unknown command: %s. Try %s to quit." % (repr(data),repr(sQuit)))
		


	sock.close()
	

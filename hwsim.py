#!/usr/bin/env python

import socket
import sys
import time

import configparser

import socketmsg as sm


if __name__=="__main__":
	sock = socket.socket()

	conf = configparser.ConfigParser()
	conf.read('config.txt')
	port = int(conf.get('communication', 'port'))
	host = conf.get('communication','host')

	sock.connect((host,port))

    
	cont = True
	while cont:
		data = sys.stdin.readline().strip()
		if data.isdigit():
			num = int(data)
			t = int(round(time.time()*1000))
			msg = sm.encode([(num,t)])
			sock.send(msg)
		else:
			if data.lower() is "q":
				cont = False
			else:
				print("Unknown command: '%s' " % data)
		


	sock.close()

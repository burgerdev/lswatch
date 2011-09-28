#!/usr/bin/env python

import vcheck

import socket
import sys

import watchio


import socketmsg as sm

import threading

class listener:
	
	datalock = threading.Lock()
	
	_data = []
	
	_t = None
	
	def __init__(self, host, port):
		self._host = host
		self._port = port
	
	def getdata(self):
		self.datalock.acquire()
		temp = self._data 
		self.datalock.release()
		return temp
		
	def popdata(self):
		self.datalock.acquire()
		temp = self._data 
		self._data = []
		self.datalock.release()
		return temp
		
	
	def setdata(self,data):
		self.datalock.acquire()
		self._data = data
		self.datalock.release()
		
	def appenddata(self,data):
		self.datalock.acquire()
		self._data += data
		self.datalock.release()
		
	def start(self):
		if self.is_alive():
			watchio.warning("Declined attempt to start already active listener.")
		else:
			self._t = threading.Thread(target = self.run)
			self._t.daemon = True
			self._t.start()
		
	def is_alive(self):
		if self._t and self._t.is_alive():
			return True
		else:
			return False
		
	def run(self):
		
			
		sock = socket.socket()
		sock.bind((self._host,self._port))

		sock.listen(1)

		
		conn, addr = sock.accept()

		print("Connection established to %s" % str(addr))
		
		data = conn.recv(1024)
			
		num_dev = sm.gethello(data)
		if not num_dev:
			carry_on = False
		else:
			carry_on = True
		
    
		while carry_on:
			newdata = conn.recv(1024)
			if len(newdata)<1:
				carry_on = False
			else:
				# TODO repair adding
				data = b''.join([data,newdata])
				numtime, data = sm.decode(data)
				self.appenddata(numtime)
				
				
			
				
		print("Info: Connection closed.")		
		conn.close()
	
	




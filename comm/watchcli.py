#!/usr/bin/env python

import vcheck


import sys
import threading
import time

import watchio




def handleTournament(T,L):
	watchio.debug("invoked handleTournament")
	
	if T.getcurrentperson() is None:
		T.setcurrentperson(1)
	if T.getcurrentround() is None:
		T.setcurrentround(1)
		
	cli = clihandler(T)
	cli.start()
	
	watchio.debug("going in main loop")
	
	while L.is_alive() and cli.is_alive():
		
		time.sleep(0.5)
		data = L.popdata()
		if len(data)>0:
			watchio.debug("acquired data")
			T.lock()
			T.persons[T.getcurrentperson()-1].updatetimes(data)
			P=T.persons[T.getcurrentperson()-1]
			print(str(P))
			T.unlock()
			#print(str(data))
			#L.setdata([])
			
			
			


class clihandler:

	def __init__(self, T):
		self._T = T
		self._thread = None
		
	def getcommand(self):
		watchio.debug("awaiting command")
		cmd = sys.stdin.readline().strip().split()
		watchio.debug("received command")
		return cmd
		
	def parsecommand(self,cmd):
		self._T.lock()
		ret = True
		
		pmapping = {'t': self._T, 'p': self._T.persons[self._T.getcurrentperson()-1]}
		smapping= {'tr': self._T.setcurrentround, 'pr': self._T.persons[self._T.getcurrentperson()-1].setcurrentround,
					'tp': self._T.setcurrentperson}
		
		watchio.debug("parsing command")
		
		if cmd[0] == 'print':
			exparg = 1
			if len(cmd)<exparg+1:
				watchio.error("Insufficient arguments for command '%s' (Expected %d)." % (cmd[0],exparg))
			elif cmd[1] in pmapping.keys():
				print(str(pmapping[cmd[1]]))
			else:
				watchio.error("Unknown argument '%s'." % (cmd[1],exparg))
			
		elif cmd[0] == 'set':
			exparg = 2
			if len(cmd)<exparg+1:
				watchio.error("Insufficient arguments for command '%s' (Expected %d)." % (cmd[0],exparg))
			elif cmd[1] in smapping.keys():
				# TODO the call to int() shall be replaced as soon as the checking works in watchdefs.py
				smapping[cmd[1]](int(cmd[2]))
			else:
				watchio.error("Unknown argument '%s'." % (cmd[1],exparg))
				
		elif cmd[0] == 'quit':
			ret = False
				
		elif cmd[0] == 'help':
			print("Available commands:")
			print("\tprint p|t")
			print("\tset pr|tr|tp <int>")
			print("\thelp")
			print("\tquit")
			
		else:
			watchio.error("Unknown command '%s'." % cmd[0])
	
		
		self._T.unlock()
		
		return ret
		
		
	def start(self):
		if self.is_alive():
			watchio.warning("Declined attempt to start already active cli.")
		else:
			
			self._thread = threading.Thread(target = self.run)
			self._thread.daemon = True
			self._thread.start()
			watchio.debug("command line parser started")
		
	def is_alive(self):
		if self._thread and self._thread.is_alive():
			return True
		else:
			return False
		
	def run(self):
		watchio.debug("cli run method invoked")
		while self.parsecommand(self.getcommand()):
			watchio.debug("finished one cl parsing")
			pass
			
		
	
	
	
	

#!/usr/bin/env python

import vcheck

import socket
import sys
import time
import signal

import configparser


import listener
from watchdefs import *
import watchio
import watchcli

def sigint_handle(num,frame):
    print("Exit on interrupt.")
    sys.exit(0)


def getDefaultTournament():
	T = Tournament()
	
	P=Person()
	P.details.update(name='Anna')
	T.persons.append(P)
	
	'''
	P=Person()
	P.details.update(name='Bert')
	T.persons.append(P)
	'''
	
	T.setcurrentround(1)
	T.setcurrentperson(1)
	return T
	


if __name__=="__main__":

	# set signal handling
	signal.signal(signal.SIGINT,sigint_handle)

	watchio.info("Main watch application started.")
	

	# set communication parameters
	conf = configparser.ConfigParser()
	conf.read('config.txt')
	port = int(conf.get('communication', 'port'))
	host = conf.get('communication','host')
	
	L = listener.listener(host, port)
	
	L.start()
	
	T = getDefaultTournament()
	
	
	watchcli.handleTournament(T,L)
	
	
	watchio.info("Main watch application stopped.")
	

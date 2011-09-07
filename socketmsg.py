#!/usr/bin/python

import re

def encode(num_time_list):
	msg = ["B:%d:%d:E" % item for item in num_time_list]
	byte_msg = bytes(''.join(msg),'ASCII')
	return byte_msg

def decode(byte_msg):
	msg = str(byte_msg, 'ASCII')
	exp=re.compile("B:([0-9]*):([0-9]*):E")
	num_time_list = exp.findall(msg)
	
	num_time_list = [(int(item[0]),int(item[1])) for item in num_time_list]
	
	#device_numbers = [int(ans[0]) for ans in num_time_list]
	#times = [int(ans[1]) for ans in num_time_list]
	
	msg_remainder = exp.sub('', msg)
	byte_msg_remainder = bytes(msg_remainder,'ASCII')
	
	return num_time_list, byte_msg_remainder
	
def lstrip(byte_msg):
	msg = str(byte_msg, 'ASCII')
	k = msg.find('E')
	if msg.startswith('B') or k<0:
		byte_msg_remainder = bytes(msg,'ASCII')
	else:
		byte_msg_remainder = bytes(msg[k+1:],'ASCII')
	
	return byte_msg_remainder
	
def rstrip(byte_msg):
	msg = str(byte_msg, 'ASCII')
	k = msg.rfind('B')
	if msg.endswith('E') or k<0:
		byte_msg_remainder = bytes(msg,'ASCII')
	else:
		byte_msg_remainder = bytes(msg[:k],'ASCII')
	
	return byte_msg_remainder
	
	

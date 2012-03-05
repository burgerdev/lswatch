#!/usr/bin/env python

import vcheck

import unittest

import socketmsg as sm

class TestSockFun(unittest.TestCase):
	
	def testEncode(self):
		expected_msg = bytes('B:15:23:E','ASCII')
		have_msg = sm.encode([(15,23)])
		self.assertEqual(have_msg,expected_msg)
		
	def testEncodeMulti(self):
		expected_msg = bytes('B:15:23:EB:16:24:E','ASCII')
		have_msg = sm.encode([(15,23),(16,24)])
		self.assertEqual(have_msg,expected_msg)

	def testDecode(self):
		expected = [(15,23)]
		have,rem = sm.decode(bytes('B:15:23:E','ASCII'))
		self.assertEqual(have,expected)
		self.assertEqual(rem,b'')
		
	def testDecodeMulti(self):
		expected = [(15,23),(16,24)]
		have,rem = sm.decode(bytes('12:EB:15:23:EB:16:24:EB17:','ASCII'))
		self.assertEqual(have,expected)
		self.assertEqual(rem,b'12:EB17:')
		
	def testStrip(self):
		expected = bytes('B:15:23:EB:16:24:E','ASCII')
		have = sm.lstrip(sm.rstrip(bytes('12:EB:15:23:EB:16:24:EB17:','ASCII')))
		self.assertEqual(have,expected)
		
	def testHelloDecode(self):
		expected = 42
		have = sm.gethello(b'HALLO 42')
		
		self.assertEqual(have,expected)
		
		
if __name__=="__main__":
	unittest.main()

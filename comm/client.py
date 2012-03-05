#!/usr/bin/env python

import socket
import sys

import configparser


if __name__=="__main__":
    sock = socket.socket()

    conf = configparser.ConfigParser()
    conf.read('config.txt')
    port = int(conf.get('communication', 'port'))
    host = conf.get('communication','host')

    sock.connect((host,port))

    data = sys.stdin.readline().rstrip()

    while len(data) > 0:
        
        sock.send(bytes(data, 'UTF-8'))
        data = sys.stdin.readline().rstrip()
        
        #print(repr(data))

    sock.close()

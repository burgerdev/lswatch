#!/usr/bin/python


import socket
import sys
import signal


import configparser


def sigint_handle(num,frame):
    print("Exit on interrupt.")
    sys.exit(0)

if __name__=="__main__":
    # set signal handling
    signal.signal(signal.SIGINT,sigint_handle)
    
    # set communication parameters
    conf = configparser.ConfigParser()
    conf.read('config.txt')
    port = int(conf.get('communication', 'port'))
    host = conf.get('communication','host')

    sock = socket.socket()



    sock.bind((host,port))

    sock.listen(1)

    while True:
        conn, addr = sock.accept()

        print("Connection established to %s" % str(addr))

        carry_on = True
        
        while carry_on:
            data = conn.recv(1024)
            if len(data) > 0:
                print(str(data,'ASCII'))
            else:
                print("Info: Connection closed.")
                carry_on = False
                

        conn.close()
    



    

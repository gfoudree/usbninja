#!/usr/bin/python

from UsbSerial import *

if __name__ == '__main__':
    print("UsbFW 0.1")
    ser = UsbSerial()
    ser.readKey('test.pem')

    signature = ser.signData("Test")
    if ser.verifyData('Test', signature):
        print('Test')

    print(ser.generateSerial())

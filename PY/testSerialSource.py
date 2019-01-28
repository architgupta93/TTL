#!/usr/bin/python3
from time import sleep
import serial

# TODO: Put the baudrate and other constants in a separate configuration file
# which can be loaded in.
DELAY      = 0.05
BAUDRATE   = 9600
DEF_PORT   = '/dev/ttyS0'
WRITE_DATA = b'\xff\xff\xff\xff\xff\xff\xff\xff'

def initializeSerial(port=DEF_PORT):
    ser = serial.Serial(port, BAUDRATE,
            timeout=0,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE
            )
    return ser

if __name__ == "__main__":
    serial_port = initializeSerial()

    # Until interrupted
    while True:
        # There is a little difference in how PC-serial and RPi-serial work. In
        # the absence of any input, PC doesn't read anything, RPi on the other
        # hand keeps putting out a stream of 0, i.e., 0x00.
        serial_port.write(WRITE_DATA)
        sleep(DELAY)

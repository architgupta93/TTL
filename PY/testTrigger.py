#!/usr/bin/python
import serial
from time import sleep

# Constant declarations
BAUDRATE     = 9600
DEFAULT_PORT = '/dev/ttyS1'
WRITE_DATA   = b'\xfd'
WRITE_PERIOD = 0.05 # Perform a write every 50ms

def initializeSerialDevice(port=DEFAULT_PORT):
    ser = serial.Serial(port, BAUDRATE,
            timeout=0,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_NONE
            )
    return ser

if (__name__ == "__main__"):
    serial_port = initializeSerialDevice()
    while (True):
        serial_port.write(WRITE_DATA)
        sleep(WRITE_PERIOD)

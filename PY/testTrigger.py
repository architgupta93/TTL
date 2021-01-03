#!/usr/bin/python3
import serial
import time

# Constant declarations
MODULE_ID    = "[PC-SERIAL] "
BAUDRATE     = 9600
DEFAULT_PORT = '/dev/ttyS0'
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

if __name__ == "__main__":
    try:
        serial_port = initializeSerialDevice()
        start_time = time.time()
        try:
            while (True):
                serial_port.write(WRITE_DATA)
                current_time = time.time() - start_time
                print(MODULE_ID + "Wrote to Serial port at %.2f"%current_time)
                time.sleep(WRITE_PERIOD)
        except KeyboardInterrupt as err:
            print()
            print(MODULE_ID + "Received keyboard interrupt. Exiting!")
        finally:
            serial_port.close()
            del serial_port
    except IOError as err:
        print(MODULE_ID + "Unable to open serial port.")
        print(err)

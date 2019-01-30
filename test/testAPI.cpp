#include "SerialPort.h"

int main() {
    /* Test the initialization and writing of data onto a communication port */
    SerialPort serial_port = SerialPort();
    serial_port.test();
}

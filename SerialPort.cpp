/* Implementation for the functions for Serial communication described in
 * SerialPort.h
 *
 * Author: Archit Gupta
 * Date: January 29, 2019
 */

#include "SerialPort.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

/*** Class constructor with PORT NAME specified ***/
SerialPort::SerialPort(const std::string port_name){
    m_port_name = port_name;
    initializePort();
}

/*** Default class constructor ***/
SerialPort::SerialPort(){
#ifdef __DEBUG__
    std::cout << "Port not supplied, using default: " << D_SERIAL_PORT << std::endl;
#endif
    m_port_name = D_SERIAL_PORT;
    initializePort();
}

void SerialPort::initializePort(){
    m_port = open(m_port_name.c_str(), O_RDWR | O_NONBLOCK | O_NDELAY);
#ifdef __DEBUG__
    std::cout << "Initializing Port: " << m_port_name << std::endl;
#endif

    if (m_port < 0) {
        // Port not found or could not be assigned
        std::cout << "Error " << errno << ": opening port " << m_port_name << std::endl;
    }

#ifdef __DEBUG__
    std::cout << "Port initialized. Allocating memory and setting attributes." << std::endl;
#endif
    /*** Configure Port ***/
    memset(&m_tty, 0, sizeof(m_tty));

    /*** Get terminal attributes, handle errors if any ***/
    if ( tcgetattr(m_port, &m_tty) != 0 ) {
        std::cout << "Error " << errno << " getting attributes: " << strerror(errno) << std::endl;
    }

    /*** Set the baud rate ***/
    cfsetospeed(&m_tty, in_baudrate);
    cfsetispeed(&m_tty, op_baudrate);

    /*** Setting up parity, stopbits and other stuff ***/
    // TODO: So far, I have no idea why some entries are ANDed and others are ORed!
    m_tty.c_cflag     &= ~PARENB;       // Make 8N1
    m_tty.c_cflag     &= ~CSTOPB;       // Add a stop bit
    m_tty.c_cflag     &= ~CSIZE;
    m_tty.c_cflag     |= CS8;
    m_tty.c_cflag     &= ~CRTSCTS;      // No flow control, pretty unidirectional communication here
    m_tty.c_cc[VMIN]   = 1;             // Read does not block
    m_tty.c_cc[VTIME]  = 1;             // Read timeout (multiple of 100 ms)
    m_tty.c_cflag     |= CREAD | CLOCAL;
    cfmakeraw(&m_tty);                  // Make Rae

#ifdef __DEBUG__
    std::cout << "Attributes set. Flushing port." << std::endl;
#endif

    /* Flush port and then apply the attributes set above */
    tcflush(m_port, TCIFLUSH);
    if (tcsetattr( m_port, TCSANOW, &m_tty ) != 0 ) {
        std::cout << " Error " << errno << " in setting attributes"  << std::endl;
    }
#ifdef __DEBUG__
    std::cout << "Port flushed. Ready for communication." << std::endl;
#endif
}

SerialPort::~SerialPort(){
    return;
}

/*** Read/Write/Test functions ***/
void SerialPort::test(){
#ifdef __DEBUG__
    std::cout << "Testing pulses... " << std::endl;
#endif
    while (true) {
        signal(); 
        usleep(D_DELAY_uS);
    }
    return;
}

bool SerialPort::signal(){
    /* Writes the default character specified in the field D_WRITE_DATA to the
     * serial port
     */
    int char_written = write(m_port, &D_WRITE_DATA, sizeof(D_WRITE_DATA));
    if (char_written == sizeof(D_WRITE_DATA))
        return true;
    return false;
}

bool SerialPort::message(const std::string &data){
    int chars_written = write(m_port, &data, sizeof(data));
    if (chars_written == data.length())
        return true;
    return false;
}

std::string SerialPort::read(){
    std::cout << "Function not implemented!" << std::endl;
    return "";
}

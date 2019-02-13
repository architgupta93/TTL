/* Implementation for the functions for Serial communication described in
 * SerialPort.h
 *
 * Author: Archit Gupta
 * Date: January 29, 2019
 * UPDATE: Feb 13, 2019: Switching to ioctl library for controlling DTR and RTS pins
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
    // m_port = open(m_port_name.c_str(), O_RDWR | O_NONBLOCK | O_NDELAY);
    m_port = open(m_port_name.c_str(), O_RDWR | O_NOCTTY);
#ifdef __DEBUG__
    std::cout << "Initializing Port: " << m_port_name << std::endl;
#endif

    // Having switched to ioctl.h, this may or may not work!
    if (m_port < 0) {
        // Port not found or could not be assigned
        std::cout << "Error " << errno << ": opening port " << m_port_name << std::endl;
    }

#ifdef __DEBUG__
    std::cout << "Port initialized. Ready for pulsing." << std::endl;
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
        sendBiphasicPulse();
        usleep(D_TEST_DELAY_uS);
    #ifdef __DEBUG__
        std::cout << "Send [Q] to quit, anything else to continue. ";
        std::cin >> user_input;
        if (user_input.compare("Q") == 0){
            return;
        }
    #endif
    }
    return;
}

/*** Functions for pulsing the control pins  ***/
// TODO: The pulse widths and inter-pulse delays can be added as arguments to
// these functions.
void SerialPort::pulseRTS(){
#ifdef __DEBUG__
    std::cout << "Press ENTER to SET RTS.";
    std::cin.get();
#endif
    ioctl(m_port, SIGNAL_ON, &RTS_FLAG);
    usleep(D_PULSE_WIDTH);
#ifdef __DEBUG__
    std::cout << "Press ENTER to CLEAR RTS.";
    std::cin.get();
#endif
    ioctl(m_port, SIGNAL_OFF, &RTS_FLAG);
}

void SerialPort::pulseDTR(){
#ifdef __DEBUG__
    std::cout << "Press ENTER to SET DTR.";
    std::cin.get();
#endif
    ioctl(m_port, SIGNAL_ON, &DTR_FLAG);
    usleep(D_PULSE_WIDTH);
#ifdef __DEBUG__
    std::cout << "Press ENTER to CLEAR RTS.";
    std::cin.get();
#endif
    ioctl(m_port, SIGNAL_OFF, &DTR_FLAG);
}

void SerialPort::sendBiphasicPulse(){
    pulseRTS();
    pulseDTR();
}

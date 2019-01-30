/* Implementation for the functions for Serial communication described in
 * SerialPort.h
 *
 * Author: Archit Gupta
 * Date: January 29, 2019
 */

#include "SerialPort.h"
#include <iostream>
#include <string.h>

// Class constructor with PORT NAME specified
SerialPort::SerialPort(std::string port_name){
    m_port_name = port_name;
    m_port = open(m_port_name, O_RDWR | O_NONBLOCK | O_NDELAY);

    /*** Configure Port ***/
    memset(&tty, sizeof(tty));

    /*** Get terminal attributes, handle errors if any ***/
}

// Default class constructor
SerialPort::SerialPort(){

}

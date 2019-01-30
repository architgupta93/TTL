#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

int main(){
    // Delcare PORT Names
    const char SERIAL_PORT[] = "/dev/ttyS1";
    const unsigned char WRITE_DATA = 0xef;
    const unsigned int DELAY_uS = 50000;

    // Open port to write to
    int port = open(SERIAL_PORT, O_RDWR | O_NONBLOCK | O_NDELAY);

    // Error handling
    if (port < 0) {
        std::cout << "Error " << errno << " opening port " << SERIAL_PORT << std::endl;
    }

    /*** Configure port ***/
    struct termios tty;
    memset(&tty, 0, sizeof(tty));

    // Get terminal attributes and handle any errors
    // TODO: I don't understand why the attributes should be 0 at this point?
    // Is it because we just initialized it?
    if ( tcgetattr(port, &tty) != 0 ) {
        std::cout << "Error " << errno << " getting attributes: " << strerror(errno) << std::endl;
    }

    /*** Set the baud rate ***/
    cfsetospeed(&tty, (speed_t)B9600);
    cfsetispeed(&tty, (speed_t)B9600);

    /*** Setting up parity, stopbits and other stuff ***/
    // TODO: So far, I have no idea why some entries are ANDed and others are ORed!
    tty.c_cflag     &= ~PARENB;     // Make 8N1
    tty.c_cflag     &= ~CSTOPB;      // Add a stop bit
    tty.c_cflag     &= ~CSIZE;
    tty.c_cflag     |= CS8;
    tty.c_cflag     &= ~CRTSCTS;    // No flow control, pretty unidirectional communication here
    tty.c_cc[VMIN]   = 1;           // Read does not block
    tty.c_cc[VTIME]  = 1;           // Read timeout (multiple of 100 ms)
    tty.c_cflag     |= CREAD | CLOCAL;
    // tty.c_iflag     &= ~(IXON | IXOFF | IXANY);         // Turn off software control

    /* Make Raw */
    cfmakeraw(&tty);

    /* Flush port and then apply the attributes set above */
    tcflush(port, TCIFLUSH);
    if (tcsetattr( port, TCSANOW, &tty ) != 0 ) {
        std::cout << " Error " << errno << " in setting attributes"  << std::endl;
    }

    /* Write data */
    int char_written = -1;
    while (true) {
        char_written = write( port, &WRITE_DATA, sizeof(WRITE_DATA));
        usleep(DELAY_uS);
    }
}

#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#include <string>
#include <termios.h>
#include <sys/ioctl.h>

// Definitions for ON and OFF signals on pins, these correspond to setting and
// clearing the pins.
#define SIGNAL_ON TIOCMBIS
#define SIGNAL_OFF TIOCMBIC

class SerialPort {
    /* Class definition for a Serial Port
     * Used for establishing a TTL pulse based connection with a device
     *
     * Author: Archit Gupta
     * Date: January 29, 2019
     */

    private:
        /*** DEFAULT SETTINGS FOR COMMUNICATION ***/
        const std::string D_SERIAL_PORT = "/dev/ttyS0";
        const unsigned int D_TEST_DELAY_uS = 50000;
        const unsigned int D_PULSE_WIDTH = 5000;

        // Internal pin numbers for the two ports
        const int RTS_FLAG = TIOCM_RTS;
        const int DTR_FLAG = TIOCM_DTR;
#ifdef __DEBUG__
        std::string user_input;
#endif

    protected:
        std::string m_port_name;
        int m_port;
        void initializePort();

    public:
        /*** Class Constructors ***/
        SerialPort(std::string port_name);
        SerialPort();

        /*** Class Destructor ***/
        ~SerialPort();

        /*** Read/Write Functions ***/
        void test();
        bool signal();
        void pulseRTS();
        void pulseDTR();
        void sendBiphasicPulse();

        /*** Functions for updating communication port parameters ***/
        // TODO
};
#endif

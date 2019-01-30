#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#include <string>
#include <termios.h>

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
        const unsigned char D_WRITE_DATA = 0xef;
        const unsigned int D_DELAY_uS = 50000;

    protected:
        struct termios m_tty;
        std::string m_port_name;
        int m_port;
        speed_t in_baudrate = B9600;
        speed_t op_baudrate = B9600;
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
        bool message(const std::string &data);
        std::string read();

        /*** Functions for updating communication port parameters ***/
        // TODO
};
#endif

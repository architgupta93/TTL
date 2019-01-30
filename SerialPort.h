#include <string.h>
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
        const char D_SERIAL_PORT[] = "/dev/ttyS0";
        const unsigned char D_WRITE_DATA = 0xef;
        const unsigned int D_DELAY_uS = 50000;

    protected:
        struct termios tty;
        std::string m_port_name;
        int m_port;

    public:
        SerialPort(std::string port_name);
        SerialPort();
        bool write();
        bool write(const std::string &message);
        std::string read();
};

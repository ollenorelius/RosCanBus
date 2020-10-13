#include <linux/can.h>
#include <sys/socket.h>
#include <iostream>


/*
    This program should send some CAN frames over local
    CAN bus loopback to test the main program.

    TODO: That.
*/

int main()
{
    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    can_frame c;
    
    c.data[0] = 0xFF;
    c.data[1] = 0xAA;
    
    std::cout << c.data[0] << c.data[1] << "asdf\n";
    return 0;
}
#include "CAN.hpp"
#include <sys/ioctl.h>
#include <cstring>
#include <linux/can.h>
#include <sys/socket.h>
#include <net/if.h>
#include <unistd.h>
#include <iostream>




Interfaces::CAN::CAN()
{
    rxCanEvent_ = std::make_unique<EventSignal>();

    init();
}

void Interfaces::CAN::init()
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    socketFd_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    std::strcpy(ifr.ifr_name, "vcan0" );
    ioctl(socketFd_, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(socketFd_, (struct sockaddr *)&addr, sizeof(addr));
}


void Interfaces::CAN::deinit() 
{
    close(socketFd_);
}
void Interfaces::CAN::readCanFrame() 
{
    struct can_frame frame;

    int nbytes = read(socketFd_, &frame, sizeof(struct can_frame));

    if (nbytes < 0) {
            perror("can raw socket read");
            return;
    }

    /* paranoid check ... */
    if (nbytes < sizeof(struct can_frame)) {
            fprintf(stderr, "read: incomplete CAN frame\n");
            return;
    }
    lastCanFrame_.id = frame.can_id;
    lastCanFrame_.dlc = frame.can_dlc;
    memcpy(lastCanFrame_.data, frame.data, frame.can_dlc);
    rxCanEvent_->emit();
}

EventSignal* Interfaces::CAN::getRxCanEvent() const
{
    return rxCanEvent_.get();
}

FrameData Interfaces::CAN::getLatestCanFrame() const
{
    return lastCanFrame_;
}
namespace Interfaces
{
    CAN::~CAN() 
    {
        deinit();
    }
}
#pragma once

#include <memory>
#include "FrameData.hpp"

class EventSignal;

namespace Interfaces
{
    class CAN
    {
    public:
        CAN(std::string interface = "can0");
        ~CAN();

        FrameData getLatestCanFrame() const;
        void readCanFrame();
        void writeCanFrame(const FrameData& fd);
        EventSignal* getRxCanEvent() const;

    private:
        void init();
        void deinit();

        std::unique_ptr<EventSignal> rxCanEvent_;
        int socketFd_;
        FrameData lastCanFrame_;
        std::string interface_;
    };
};
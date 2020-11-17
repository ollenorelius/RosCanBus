#pragma once

#include "../EventSignal.hpp"
#include <memory>
#include "FrameData.hpp"

namespace Interfaces
{
    class CAN
    {
    public:
        CAN();
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
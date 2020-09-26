
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

        FrameData getLatestCanFrame();


    private:
        void init();
        void deinit();

        void readCanFrame();
        std::unique_ptr<EventSignal> rxCanEvent_;
        int socketFd_;
        FrameData lastCanFrame_;
    };
};
#pragma once
#include <linux/can.h>
#include <vector>
#include <string>

class Frame
{
public:
    Frame(std::string name,
               int frameId,
               std::vector<int> signals,
               double period,
               std::string description);

    Frame(const Frame& other); 


    std::string getName();
    int getFrameId();
    double getPeriod();
    int getDlc();
    void setDlc(int dlc);
    std::vector<int>* getSignals();
    std::string getDescription();
//    void decodeCanFrame(can_frame* canFrame);

private:
//    std::vector<CANSignal> decodedSignals;
    std::string name_;
    int frameId_;
    double period_;
    std::vector<int> signals_;
    std::string description_;
    int dlc_;



};
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

    Frame(); 


    std::string getName() const;
    int getFrameId() const;
    double getPeriod() const;
    int getDlc() const;
    void setDlc(int dlc);
    const std::vector<int>* getSignals() const;
    std::string getDescription() const;
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
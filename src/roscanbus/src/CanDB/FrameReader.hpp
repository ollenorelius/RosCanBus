#pragma once

#include "xlnt/xlnt.hpp"
#include <string>
#include <map>
#include <memory>
#include "Frame.hpp"

class SignalDefinition;
class FrameReader
{
public:
    FrameReader(std::string path, std::map<int, SignalDefinition>* signalDefinitionCollectionModel);
    
    std::unique_ptr<std::map<int, Frame>> getTxFrames(std::string selfID);
    std::unique_ptr<std::map<int, Frame>> getRxFrames(std::string selfID);

private:
    xlnt::workbook document_;
    Frame createDBCanFrame(xlnt::cell_vector row);
    void updateDLC(Frame& frame);

    const int NAME = 0;
    const int ID = 1;
    const int SIGNALS = 2;
    const int PERIOD = 3;
    const int SOURCE = 4;
    const int BUS = 5;
    const int DESC = 6;
    std::map<int, SignalDefinition>* signalDefinitionCollectionModel_;
};
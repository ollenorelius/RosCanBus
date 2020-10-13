#pragma once

#include "xlnt/xlnt.hpp"
#include <string>
#include <map>
#include <memory>
#include "Frame.hpp"

class FrameReader
{
public:
    FrameReader(std::string path);
    
    std::unique_ptr<std::map<int, Frame>> getTxFrames(std::string selfID);
    std::unique_ptr<std::map<int, Frame>> getRxFrames(std::string selfID);

private:
    xlnt::workbook document_;
    Frame createDBCanFrame(xlnt::cell_vector row);

    const int NAME = 0;
    const int ID = 1;
    const int SIGNALS = 2;
    const int PERIOD = 3;
    const int SOURCE = 4;
    const int BUS = 5;
    const int DESC = 6;
};
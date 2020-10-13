#pragma once

#include <string>
#include <memory>
#include <map>
#include "xlnt/xlnt.hpp"
#include "SignalDefinition.hpp"
#include "../Models/CanSignalCollectionModel.hpp"

class SignalReader
{
    public:
    SignalReader(std::string path);
    
    std::unique_ptr<std::map<int, SignalDefinition>> getSignalDefinitions();
    std::unique_ptr<CanSignalCollectionModel> createCanSignalCollectionModel();

private:
    SignalDefinition createSignalDefinition(xlnt::cell_vector row);
    SIGNAL_TYPE convertToSignalType(std::string signalType);

    xlnt::workbook document_;
    enum class COLUMNS
    {
        ID = 0,
        NAME = 1,
        TYPE = 2,
        LENGTH = 3,
        SCALER = 4,
        OFFSET = 5,
        UNIT = 6,
        DESCRIPTION = 7,
        SOURCE = 8
    };

};

#include "SignalReader.hpp"

SignalReader::SignalReader(std::string path) 
{
    document_.load(path);
}

std::unique_ptr<std::map<int, SignalDefinition>> SignalReader::getSignalDefinitions() 
{
    std::map<int, SignalDefinition> signalDefinitions;

    xlnt::worksheet worksheet = document_.sheet_by_title("Signals");
    auto rows = worksheet.rows();
    for (auto row : rows)
    {
        signalDefinitions.insert(std::pair<int, SignalDefinition>(row[static_cast<int>(COLUMNS::ID)].value<int>(), createSignalDefinition(row)));
    }

    return std::make_unique<std::map<int, SignalDefinition>>(signalDefinitions);
}

std::unique_ptr<CanSignalCollectionModel> SignalReader::createCanSignalCollectionModel()
{
    CanSignalCollectionModel* canSignalCollectionModel = new CanSignalCollectionModel();

    xlnt::worksheet worksheet = document_.sheet_by_title("Signals");
    auto rows = worksheet.rows();
    for (auto row : rows)
    {
        CanSignalDirection direction = row[static_cast<int>(COLUMNS::SOURCE)].value<std::string>() == "ADAS" ? CanSignalDirection::TX : CanSignalDirection::RX;
        canSignalCollectionModel->addCanSignal(row[static_cast<int>(COLUMNS::ID)].value<int>(), direction);

        //signalDefinitions.insert(std::pair<int, SignalDefinition>(row[static_cast<int>(COLUMNS::ID)].value<int>(), createSignalDefinition(row)));
    }

    return std::unique_ptr<CanSignalCollectionModel>(canSignalCollectionModel);
}

SignalDefinition SignalReader::createSignalDefinition(xlnt::cell_vector row) 
{
    double scaler;
    if (row[static_cast<int>(COLUMNS::SCALER)].to_string() == "-" || 
        row[static_cast<int>(COLUMNS::SCALER)].to_string() == "")
    {
        scaler = 0;
    }
    else
    {
        scaler = row[static_cast<int>(COLUMNS::SCALER)].value<double>();
    }
    
    return SignalDefinition(convertToSignalType(row[static_cast<int>(COLUMNS::TYPE)].value<std::string>()),
                                      row[static_cast<int>(COLUMNS::LENGTH)].value<int>(),
                                      scaler,
                                      row[static_cast<int>(COLUMNS::OFFSET)].value<double>(),
                                      row[static_cast<int>(COLUMNS::UNIT)].value<std::string>(),
                                      row[static_cast<int>(COLUMNS::NAME)].value<std::string>(),
                                      row[static_cast<int>(COLUMNS::DESCRIPTION)].value<std::string>()
                                      );
}

SIGNAL_TYPE SignalReader::convertToSignalType(std::string signalType) 
{
    if (signalType == "signed"        || signalType == "Signed") return SIGNAL_TYPE::SIGNED;
    else if (signalType == "unsigned" || signalType == "Unsigned") return SIGNAL_TYPE::UNSIGNED;
    else if (signalType == "float"    || signalType == "Float") return SIGNAL_TYPE::FLOAT;
    else if (signalType == "bool"     || signalType == "Bool") return SIGNAL_TYPE::BOOL;
    
}


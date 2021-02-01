#include "FrameReader.hpp"
#include "SignalDefinition.hpp"
 
FrameReader::FrameReader(std::string path,
                         std::map<int, SignalDefinition>* signalDefinitionCollectionModel) :
    signalDefinitionCollectionModel_(signalDefinitionCollectionModel)
{
    document_.load(path);
}

std::unique_ptr<std::map<int, Frame>> FrameReader::getRxFrames(std::string selfID) 
{
    std::map<int, Frame> rxFrames;
    for (std::string sheetname : document_.sheet_titles())
    {
        if (sheetname.find("Frames",0) == -1) continue;

        xlnt::worksheet worksheet = document_.sheet_by_title(sheetname);
        auto rows = worksheet.rows();
        for (xlnt::range_iterator::reference row : rows)
        {
            if (row[SOURCE].value<std::string>() != selfID)
            {
                try 
                {
                    std::string id = row[ID].value<std::string>();
                    int fid = std::stoi(id, nullptr, 0);
                    rxFrames.insert( std::pair<int, Frame>(fid, createDBCanFrame(row)));
                }
                catch (std::invalid_argument e)
                {
                    continue;
                }
            }
        }
    }
    return std::make_unique<std::map<int, Frame>>(rxFrames);
}

std::unique_ptr<std::map<int, Frame>> FrameReader::getTxFrames(std::string selfID) 
{
    std::map<int, Frame> txFrames;
    for (std::string sheetname : document_.sheet_titles())
    {
        if (sheetname.find("Frames",0) == -1) continue;

        xlnt::worksheet worksheet = document_.sheet_by_title(sheetname);
        auto rows = worksheet.rows();
        for (xlnt::range_iterator::reference row : rows)
        {
            if (row[SOURCE].value<std::string>() == selfID)
            {
                try 
                {
                    std::string id = row[ID].value<std::string>();
                    int fid = std::stoi(id, nullptr, 0);
                    txFrames.insert( std::pair<int, Frame>(fid, createDBCanFrame(row)));
                }
                catch (std::invalid_argument e)
                {
                    continue;
                }
            }
        }
    }
    return std::make_unique<std::map<int, Frame>>(txFrames);
}

Frame FrameReader::createDBCanFrame(xlnt::cell_vector row) 
{
    std::vector<int> signals;
    std::string tmp; 
    std::stringstream ss(row[SIGNALS].value<std::string>());
    std::vector<std::string> words;

    while(getline(ss, tmp, ',')){
        signals.push_back(std::stoi(tmp));
    }
    Frame frame = Frame(row[NAME].value<std::string>(),
                      std::stoi(row[ID].value<std::string>(), nullptr, 0),
                      signals,
                      row[PERIOD].value<double>(),
                      row[DESC].value<std::string>());

    updateDLC(frame);
    return frame;
}

void FrameReader::updateDLC(Frame& frame) 
{
        int dlc = 0;   
        auto signals = frame.getSignals();
        
        for (int signalIndex : *signals)
        {
            dlc += signalDefinitionCollectionModel_->at(signalIndex).getLength();
        }
        dlc = dlc / 8 + (dlc % 8 != 0); // divide by 8 and round up.
        frame.setDlc(dlc);
}

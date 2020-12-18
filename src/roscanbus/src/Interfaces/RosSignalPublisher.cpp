#include "RosSignalPublisher.hpp"
#include "../Models/CanSignalModel.hpp"
#include "../Models/RosNodeModel.hpp"
#include "std_msgs/Float32.h"
#include <string>
#include <algorithm>

RosSignalPublisher::RosSignalPublisher(CanSignalModel* canSignalModel,
                                       RosNodeModel* rosNodeModel,
                                       std::map<int, SignalDefinition>* canSignalDefinitions):
    canSignalModel_(canSignalModel),
    rosNodeModel_(rosNodeModel)
{
    std::string name = canSignalDefinitions->at(canSignalModel_->getIndex()).getName().data();
    std::replace(name.begin(), name.end(), ' ', '_');

    signal_pub_ = rosNodeModel_->getNodeHandle()->advertise<std_msgs::Float32>(name, 100);
    
    auto callback = [this]()
    {
        publishRosMessage();
    };
    canSignalModel_->getValueChanged()->connect(callback);
}

void RosSignalPublisher::publishRosMessage() 
{   
    std_msgs::Float32 msg;
    msg.data = canSignalModel_->getValue();
    signal_pub_.publish(msg);
}

#include "RosSignalSubscriber.hpp"
#include "../Models/CanSignalModel.hpp"
#include "../Models/RosNodeModel.hpp"

RosSignalSubscriber::RosSignalSubscriber(CanSignalModel* canSignalModel,
                        RosNodeModel* rosNodeModel,
                        std::map<int, SignalDefinition>* canSignalDefinitions) :
    canSignalModel_(canSignalModel),
    rosNodeModel_(rosNodeModel)
{
    std::string name = canSignalDefinitions->at(canSignalModel_->getIndex()).getName().data();
    std::replace(name.begin(), name.end(), ' ', '_');

    auto callback = [this](const std_msgs::Float32::ConstPtr& msg){subCallback(msg);};

    signalSub_ = rosNodeModel_->getNodeHandle()->subscribe(name, 1000, &RosSignalSubscriber::subCallback, this);
}

void RosSignalSubscriber::subCallback(const std_msgs::Float32::ConstPtr& msg)
{
    canSignalModel_->setValue(msg->data);
//    ROS_INFO("I heard: [%s]", msg->data.c_str());
}
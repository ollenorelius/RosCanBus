#include "RosNodeModel.hpp"


RosNodeModel::RosNodeModel(int argc, char** argv) 
{
    ros::init(argc, argv,  "CanPublisher");

}

ros::NodeHandle* RosNodeModel::getNodeHandle() 
{
    return &nodeHandle_;
}

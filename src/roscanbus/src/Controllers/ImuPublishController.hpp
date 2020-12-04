#pragma once

#include <map>
#include "ros/ros.h"

class CanSignalCollectionModel;
class RosNodeModel;
class CanSignalModel;


enum class ImuData
{
    ACC_X,
    ACC_Y,
    ACC_Z,
    
    GYRO_X,
    GYRO_Y,
    GYRO_Z,

    MAG_X,
    MAG_Y,
    MAG_Z
};

class ImuPublishController
{
public:
    ImuPublishController(std::map<ImuData, CanSignalModel*> signals, 
                 RosNodeModel* rosNodeModel);

    void start();

private:
    std::map<ImuData, CanSignalModel*> signals_;
    RosNodeModel* rosNodeModel_;
    ros::Publisher signal_pub_;

    void publish();

};
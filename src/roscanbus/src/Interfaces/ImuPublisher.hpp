#pragma once

#include <map>

class CanSignalCollectionModel;
class RosNodeModel;

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

class ImuPublisher
{
public:
    ImuPublisher(std::map<ImuData, CanSignalModel*> signals, 
                 CanSignalCollectionModel* canSignalCollectionModel,
                 RosNodeModel* rosNodeModel);

    void start();

private:
    std::map<ImuData, CanSignalModel*> signals_;
    CanSignalCollectionModel* canSignalCollectionModel_;
    RosNodeModel* rosNodeModel_;
    ros::Publisher signal_pub_;

    void publish();

};
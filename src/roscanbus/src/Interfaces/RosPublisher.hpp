#pragma once 

class RosNodeModel;

namespace Interfaces
{
    class RosPublisher
    {
    public:
        RosPublisher(RosNodeModel* rosNodeModel);
    };

}
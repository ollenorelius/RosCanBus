# RosCanBus
## WIP WIP WIP WIP 

A CAN bus ROS node that will transcode CAN signals to ROS topics according to a predefined CAN database.


## Building 
Building the project is a bit awkward atm, since I'm bad at CMake.
First you need to build the lib:
- cd lib/xlnt
- mkdir build
- cd build
- cmake ..
- make -j4

Then you can build the actual source. Go to the project root and run:

- mkdir build
- cd build 
- cmake ..
- make -j4

ISSUES:
If signal IDs are not formatted as strings, they will not be read. This is a problem for single signal frames like blinker request.

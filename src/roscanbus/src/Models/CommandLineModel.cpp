#include "CommandLineModel.hpp"


CommandLineModel::CommandLineModel(int argc, char** argv) :
argc_(argc),
argv_(argv)
{
    
}

int CommandLineModel::getArgc() 
{
    return argc_;
}

char** CommandLineModel::getArgv() 
{
    return argv_;
}

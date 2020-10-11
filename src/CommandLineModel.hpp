#pragma once

class CommandLineModel
{
public:
    CommandLineModel(int argc, char** argv);

    int getArgc();
    char** getArgv();

private:
    int argc_;
    char** argv_;
};
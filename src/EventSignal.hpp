#pragma once

#include <functional>
#include <vector>

class EventSignal
{
public:
    EventSignal();
    void connect(std::function<void()> callback);
    void emit();

private:
    std::vector<std::function<void()>> receivers_;
};
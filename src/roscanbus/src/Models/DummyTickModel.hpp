#pragma once 

#include <memory>

#include "../EventSignal.hpp"

class DummyTickModel
{
public : 
    DummyTickModel();

    void emit();    
    EventSignal* getSignal() const;

private:
    std::unique_ptr<EventSignal> signal_;

};
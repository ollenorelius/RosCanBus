#include "DummyTickModel.hpp"

DummyTickModel::DummyTickModel() : 
    signal_(std::make_unique<EventSignal> ()) 
{

}

void DummyTickModel::emit()
{   
    signal_->emit();
}

EventSignal* DummyTickModel::getSignal() const 
{
    return signal_.get();
}
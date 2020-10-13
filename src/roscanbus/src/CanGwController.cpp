#include "CanGwController.hpp"
#include "CanGwModel.hpp"
#include "CanGwInterfaces.hpp"

    

CanGwController::CanGwController(CanGwModel* canGwModel, CanGwInterfaces* canGwInterfaces) 
{
    signalPublishingController_ = std::make_unique<SignalPublishingController>(canGwModel->getCanSignalCollectionModel(),
                                                                               canGwModel->getRosNodeModel(),
                                                                               canGwModel->getCanSignalDefinitionCollectionModel());   

    frameToSignalsController_ = std::make_unique<FrameToSignalsController>(canGwInterfaces->getCanInterface(),
                                                                           canGwModel->getCanSignalCollectionModel(),
                                                                           canGwModel->getRxCanFramesCollectionModel(),
                                                                           canGwModel->getCanSignalDefinitionCollectionModel());
}

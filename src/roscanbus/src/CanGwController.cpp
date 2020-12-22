#include "CanGwController.hpp"
#include "CanGwModel.hpp"
#include "CanGwInterfaces.hpp"
#include <map>

CanGwController::CanGwController(CanGwModel* canGwModel, CanGwInterfaces* canGwInterfaces) 
{
    signalPublishingController_ = std::make_unique<SignalPublishingController>(canGwModel->getCanSignalCollectionModel(),
                                                                               canGwModel->getRosNodeModel(),
                                                                               canGwModel->getCanSignalDefinitionCollectionModel());   

    frameToSignalsController_ = std::make_unique<FrameToSignalsController>(canGwInterfaces->getCanInterface(),
                                                                           canGwModel->getCanSignalCollectionModel(),
                                                                           canGwModel->getRxCanFramesCollectionModel(),
                                                                           canGwModel->getCanSignalDefinitionCollectionModel());
<<<<<<< HEAD
<<<<<<< HEAD
                                                                           
    
    
    canTransmitterController_ = std::make_unique<CanTransmitterController>( canGwInterfaces->getCanInterface(),
                                                                            canGwModel->getCanSignalCollectionModel(),                                                                            
                                                                            canGwModel->getTxCanFramesCollectionModel(),
                                                                            canGwModel->getCanFrameEmitTimerModel(),
                                                                            canGwModel->getCanSignalDefinitionCollectionModel(),
                                                                            canGwModel->getDummyTickModel());                                                                        
=======
=======
>>>>>>> a89900bf798d814511c65caa685d1613c3c8bf6b


    std::map<ImuData, CanSignalModel*> imuSignals;

    imuSignals[ImuData::ACC_X] = canGwModel->getCanSignalCollectionModel()->getCanSignal(62);
    imuSignals[ImuData::ACC_Y] = canGwModel->getCanSignalCollectionModel()->getCanSignal(63);
    imuSignals[ImuData::ACC_Z] = canGwModel->getCanSignalCollectionModel()->getCanSignal(64);

    imuSignals[ImuData::GYRO_X] = canGwModel->getCanSignalCollectionModel()->getCanSignal(59);
    imuSignals[ImuData::GYRO_Y] = canGwModel->getCanSignalCollectionModel()->getCanSignal(60);
    imuSignals[ImuData::GYRO_Z] = canGwModel->getCanSignalCollectionModel()->getCanSignal(61);

    imuPublishController_ = std::make_unique<ImuPublishController>(imuSignals, canGwModel->getRosNodeModel());
    
<<<<<<< HEAD
>>>>>>> datatypes
=======
                                                                           
    
    
    canTransmitterController_ = std::make_unique<CanTransmitterController>( canGwInterfaces->getCanInterface(),
                                                                            canGwModel->getCanSignalCollectionModel(),                                                                            
                                                                            canGwModel->getTxCanFramesCollectionModel(),
                                                                            canGwModel->getCanFrameEmitTimerModel(),
                                                                            canGwModel->getCanSignalDefinitionCollectionModel(),
                                                                            canGwModel->getDummyTickModel());                                                                        
>>>>>>> a89900bf798d814511c65caa685d1613c3c8bf6b
}



                            
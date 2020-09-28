cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(IGNORE_ME ${CMAKE_C_COMPILER})


project("ProjectX")
set(SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/CanGwModel.cpp
${CMAKE_CURRENT_LIST_DIR}/src/CanGwController.cpp
${CMAKE_CURRENT_LIST_DIR}/src/CanGwInterfaces.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/src/CanSignalCollectionModel.cpp
${CMAKE_CURRENT_LIST_DIR}/src/CanDB/Frame.cpp
${CMAKE_CURRENT_LIST_DIR}/src/CanDB/SignalDefinition.cpp
${CMAKE_CURRENT_LIST_DIR}/src/CanDB/FrameReader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/CanDB/SignalReader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Interfaces/CAN.cpp
${CMAKE_CURRENT_LIST_DIR}/src/EventSignal.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Controllers/FrameToSignalsController.cpp

)

add_executable(${PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${SOURCES}
                ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
                )


target_include_directories( ${PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib/xlnt/include>
)

target_link_libraries( ${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/lib/xlnt/build/source/libxlnt.so
)


set(CANSENDER CanSender)
add_executable(${CANSENDER})
target_sources(${CANSENDER} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/cansender.cpp)

add_executable(test)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src)
target_sources(test PRIVATE
               ${CMAKE_CURRENT_LIST_DIR}/test/test.cpp
               ${SOURCES})

target_link_libraries( test PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/lib/xlnt/build/source/libxlnt.so
)
target_include_directories( test PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/lib/xlnt/include>
)
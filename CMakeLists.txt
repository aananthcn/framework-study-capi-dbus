cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -pthread -std=c++0x")
 
include_directories(
    src-gen
    ../capicxx-core-runtime/include
    ../capicxx-dbus-runtime/include
    ../dbus-1.8.20
)
 
link_directories(
    /home/aananth/projects/framework-study/capicxx-core-runtime/build
    /home/aananth/projects/framework-study/capicxx-dbus-runtime/build
    /home/aananth/projects/framework-study/dbus-1.8.20/dbus/.libs
)
 
add_executable(HelloWorldClient
    src/HelloWorldClient.cpp
    src-gen/v1/commonapi/HelloWorldDBusProxy.cpp
    src-gen/v1/commonapi/HelloWorldDBusDeployment.cpp
)
target_link_libraries(HelloWorldClient CommonAPI CommonAPI-DBus dbus-1)
 
add_executable(HelloWorldService
    src/HelloWorldService.cpp
    src/HelloWorldStubImpl.cpp
    src-gen/v1/commonapi/HelloWorldDBusStubAdapter.cpp
    src-gen/v1/commonapi/HelloWorldStubDefault.cpp
    src-gen/v1/commonapi/HelloWorldDBusDeployment.cpp
)
target_link_libraries(HelloWorldService CommonAPI CommonAPI-DBus dbus-1)

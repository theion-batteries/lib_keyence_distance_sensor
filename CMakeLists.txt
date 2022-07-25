# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.22.0)

# project name
project(keyence_interface)

# creates the variable EXEC and sets it to main
set(EXEC main)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)

# I../includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SerialPort/include/)

# puts all .cpp files inside src to the SOURCES variable
#file(GLOB SOURCES src/*.cpp)
# Local header files here ONLY
# target is windows
add_library(keyenceLib)
target_sources(keyenceLib
    PUBLIC
   src/keyence_api.cpp
   src/distance_sensor_interface.cpp
   src/keyence_win_api.cpp
   src/keyence_rs232_api.cpp
   includes/distance_sensor_interface.h
   includes/keyence_api.h
   includes/keyence_rs232_api.h
   includes/settings.h
   includes/keyence_win_api.h 
  )

  add_executable(keyenceExe src/main.cpp)


# compiles the files defined by SOURCES to generante the executable defined by EXEC
#add_executable(${PROJECT_NAME} ${SOURCES})
#add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
#INCLUDE_DIRECTORIES(
#  c:/src/vcpkg/installed/x64-windows/include/
#)
#  
#LINK_DIRECTORIES(
#  c:/src/vcpkg/installed/x64-windows/lib/
#) 
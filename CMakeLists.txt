# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.22.0)

# project name
project(keyence_interface)

# creates the variable EXEC and sets it to main
set(EXEC main)

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Unix Makefiles")

# set output dir
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY C:/Users/SamiDhiab/Theion_Repos/lib_keyence_distance_sensor/build/arch/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY C:/Users/SamiDhiab/Theion_Repos/lib_keyence_distance_sensor/build/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY C:/Users/SamiDhiab/Theion_Repos/lib_keyence_distance_sensor/build/)

# I../includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SerialPort/include/)

# puts all .cpp files inside src to the SOURCES variable
file(GLOB SOURCES src/*.cpp)

# compiles the files defined by SOURCES to generante the executable defined by EXEC
add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

INCLUDE_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/lib/
)
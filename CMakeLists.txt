# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.5.0)

# project name
project(keyence_lib VERSION "1.0")

# set the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
## library name
set(KEYENCE keyence_lib)
set(KEYENCE_STATIC ${KeyenceLib}-static)

# --- Build Options ---

if(WIN32)
	option(KEYENCE_BUILD_STATIC "Build static library" ON)
	option(KEYENCE_BUILD_SHARED "Build shared library (DLL)" OFF)
else()
	option(KEYENCE_BUILD_STATIC "Build static library" OFF)
	option(KEYENCE_BUILD_SHARED "Build shared library" ON)
endif()

option(KEYENCE_BUILD_EXAMPLES "Build example applications" OFF)
option(KEYENCE_BUILD_TESTS "Build unit tests" OFF)
option(KEYENCE_BUILD_DOCUMENTATION "Create Doxygen reference documentation" OFF)

# --- System libraries ---

include(GNUInstallDirs)

if(WIN32)
	set(LIBS_SYSTEM ws2_32)
elseif(UNIX)
	set(LIBS_SYSTEM c stdc++)
endif()


# include libs
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/sockpp/include/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/SerialPort/include/)
# source *.cpp
file(GLOB all_SRCS
        "${PROJECT_SOURCE_DIR}/dependencies/sockpp/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/dependencies/SerialPort/src/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
)
# add .exe
add_executable(keyence_bin ${all_SRCS})
# link againt static lib
#target_link_libraries(keyence_bin ${PROJECT_SOURCE_DIR}/dependencies/sockpp/build/libsockpp-static.a)

## include preinstalled lib with vcpkg
INCLUDE_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
  c:/src/vcpkg/installed/x64-windows/lib/
) 


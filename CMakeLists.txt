cmake_minimum_required(VERSION 3.10)
project(openrdv_agent)

set(CMAKE_CXX_STANDARD 17)

# ----- FINDING BOOST LIBRARIES -----
cmake_policy(SET CMP0074 NEW)
find_package(Boost REQUIRED COMPONENTS filesystem)
if (Boost_FOUND)
    message(STATUS "Found Boost ${Boost_VERSION_STRING}")
    message(STATUS "Boost include dir ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# ----- AGENT EXECUTABLE -----
add_executable(openrdv_agent main.cpp src/AttestPluginLoader.cpp src/AttestManager.cpp src/ServerConnection.cpp include/ServerConnection.h)
target_link_libraries(openrdv_agent ${Boost_LIBRARIES} ${CMAKE_DL_LIBS} Threads::Threads)

# ----- SAMPLE PLUGIN SHARED LIBRARY -----
add_library(sample_plugin SHARED plugins/SamplePlugin.cpp)
target_link_libraries(sample_plugin ${Boost_LIBRARIES})

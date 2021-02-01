cmake_minimum_required(VERSION 3.10)
project(openrdv_agent)

set(CMAKE_CXX_STANDARD 17)

# ----- FINDING BOOST LIBRARIES -----
cmake_policy(SET CMP0074 NEW)
find_package(Boost CONFIG)
if (Boost_FOUND)
    message(STATUS "Found Boost ${Boost_VERSION_STRING}")
    message(STATUS "Boost include dir ${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(include)

add_executable(openrdv_agent main.cpp src/AttestProviderLoader.cpp)
target_link_libraries(openrdv_agent pthread)
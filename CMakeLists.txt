project(mini)
cmake_minimum_required(VERSION 2.8)

#SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall -g -D_GNU_SOURCE -fPIC -pthread")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall -g -D_GNU_SOURCE -pthread")
SET(CMAKE_BUILD_TYPE DEBUG)
#TARGET_LINK_LIBRARIES(pthread)

LINK_DIRECTORIES(/usr/lib)
LINK_DIRECTORIES(/usr/local/lib)
LINK_DIRECTORIES(/home/gl/workspace/havefun/lib)

include_directories(include/hiredis)
#include_directories(redis_mysql)
ADD_SUBDIRECTORY(redis_mysql)
ADD_SUBDIRECTORY(test)

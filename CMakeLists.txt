project(mini)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall -g -D_GNU_SOURCE -fPIC -pthread")
SET(CMAKE_BUILD_TYPE DEBUG)
#TARGET_LINK_LIBRARIES(pthread)

AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(mini_run ${SRC_LIST})
TARGET_LINK_LIBRARIES(mini_run pthread)

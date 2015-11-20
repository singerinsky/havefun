project(mini)

#TARGET_LINK_LIBRARIES(pthread)

SET(EXECUTABLE_OUTPUT_PATH ../)
LINK_DIRECTORIES(/usr/lib)
LINK_DIRECTORIES(/usr/local/lib)
LINK_DIRECTORIES(/home/gl/workspace/havefun/lib)

include_directories(../include/hiredis)
AUX_SOURCE_DIRECTORY(. SRC_LIST)
ADD_EXECUTABLE(mini_run ${SRC_LIST})
#TARGET_LINK_LIBRARIES(mini_run pthread gflag glog)
TARGET_LINK_LIBRARIES(mini_run pthread gflags glog hiredis protobuf mysql2redis mysqlclient)

# cmake version to be used
cmake_minimum_required( VERSION 3.0 )

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

# project name
project(BRS_task)

# target
#add_executable( ceres_tut1 sandbox/ceres_tut1.cpp )

# external libs
find_package(Ceres REQUIRED)
find_package(Glog REQUIRED)
# Or find_package(Ceres REQUIRED PATHS "/path/to/install/dir") if the install directory is not in your PATH

include_directories(${CERES_INCLUDE_DIRS} ${GLOG_INCLUDE_DIRS})
#add_library(BRS_task ${CERES_LIBRARIES} ${GLOG_LIBRARIES})

#target_include_directories(BRS_task
    #${CERES_INCLUDE_DIRS}
    #${GLOG_INCLUDE_DIRS}
#)

#target_link_libraries(BRS_task
#    ${CERES_LIBRARIES}
#    ${GLOG_LIBRARIES}
#)

add_executable(ceres_tut1 sandbox/ceres_tut1.cpp)
#target_include_directories(task_main .)
add_executable(task_main "task_main.cpp" "PointSearcher.cpp" "Geometry.cpp")
#add_executable(task_main "task_main.cpp")
#add_executable(test_reader "Geometry.cpp" "sandbox/test_reader.cpp")

#target_link_libraries(ceres_tut1 ${CERES_LIBRARIES} ${GLOG_LIBRARIES})
target_link_libraries(task_main ${CERES_LIBRARIES})
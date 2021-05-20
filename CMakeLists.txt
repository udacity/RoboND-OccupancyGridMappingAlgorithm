cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(robotND)

message("GridApp")

#find Matplot package
find_package(Matplot++ REQUIRED)

#for windows its required to prvode the include folder
if(WIN32)
set(MATPLOT_INCLUDE_DIR ${Matplot++_DIR}/../../../include)
list(APPEND HEADER_FILES "${MATPLOT_INCLUDE_DIR}/matplot/matplot.h")
list(APPEND HEADER_FILES_INCLUDE_DIRS  "${MATPLOT_INCLUDE_DIR}")
endif()

#compile the source code and link it with external libraries
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC Matplot++::matplot)
     

cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_STANDARD 14)
project( ProgramaSecuencial )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ProgramaSecuencial main.cpp )
target_link_libraries( ProgramaSecuencial ${OpenCV_LIBS} )
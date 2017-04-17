cmake_minimum_required(VERSION 2.8)
project( make_picture )
find_package( OpenCV REQUIRED )
add_executable( make_picture make_picture.cpp )
target_link_libraries( make_picture  ${OpenCV_LIBS} )


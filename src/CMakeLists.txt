cmake_minimum_required(VERSION 2.8)

project( tarantula )

SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH "Single directory for all executables." )
MARK_AS_ADVANCED( EXECUTABLE_OUTPUT_PATH )

find_package( OpenCV REQUIRED )

SET( tarantula_SRCS tarantula) # for multiple: SET( tarantula_SRCS tarantula control gui vision) 

add_executable( tarantula ${tarantula_SRCS} )
target_link_libraries( tarantula ${OpenCV_LIBS} )
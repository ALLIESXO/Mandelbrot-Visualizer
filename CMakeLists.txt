cmake_minimum_required(VERSION 3.0.0)

project(MandelBrot)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )

FILE(GLOB_RECURSE MY_HEADERS "include/*.hpp")
FILE(GLOB_RECURSE MY_SOURCES "src/*.cpp")

add_executable (${PROJECT_NAME} ${MY_SOURCES} ${MY_HEADERS} )
add_library (${PROJECT_NAME}_lib ${MY_SOURCES} ${MY_HEADERS} )

target_include_directories(${PROJECT_NAME} PUBLIC include )
target_include_directories(${PROJECT_NAME}_lib PUBLIC include )

target_include_directories(${PROJECT_NAME} PRIVATE ${OPENCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME}_lib PRIVATE ${OPENCV_INCLUDE_DIRS} )
target_link_libraries(${PROJECT_NAME}_lib ${OpenCV_LIBS})

add_subdirectory(extern/googletest)
add_subdirectory(test)

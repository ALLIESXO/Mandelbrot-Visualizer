
enable_testing()

add_executable(${CMAKE_PROJECT_NAME}_test test_mandelbrot.cpp test_Fractal.cpp test_HSV.cpp test_RGB.cpp test_Settings.cpp)
add_test(NAME ${CMAKE_PROJECT_NAME}_test COMMAND ${CMAKE_PROJECT_NAME}_test)
target_link_libraries(${CMAKE_PROJECT_NAME}_test PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)

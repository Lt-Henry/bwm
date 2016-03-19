
add_executable(bwm main.cpp WindowManager.cpp)

target_link_libraries(bwm X11)
add_definitions(-std=c++11)

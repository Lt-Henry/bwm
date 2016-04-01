
add_executable(bwm main.cpp WindowManager.cpp Decorator.cpp Utils.cpp Rect.cpp)

#require pkg-config support
find_package(PkgConfig REQUIRED)

#required pkg-config libs
pkg_check_modules(CAIRO REQUIRED cairo)

#add include dirs
include_directories(${CAIRO_INCLUDE_DIRS})

target_link_libraries(bwm X11 ${CAIRO_LIBRARIES})
add_definitions(-std=c++11)

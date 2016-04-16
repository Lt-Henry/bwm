
add_executable(bwm main.cpp WindowManager.cpp Decorator.cpp Utils.cpp Rect.cpp Pointer.cpp Frame.cpp)

#require pkg-config support
find_package(PkgConfig REQUIRED)

#required pkg-config libs
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

#add include dirs
include_directories(${CAIRO_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})

target_link_libraries(bwm X11 Xcursor ${CAIRO_LIBRARIES} ${GTKMM_LIBRARIES})
add_definitions(-std=c++11)

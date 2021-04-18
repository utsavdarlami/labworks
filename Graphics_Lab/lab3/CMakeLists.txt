cmake_minimum_required (VERSION 2.6)
project (view)
add_executable(view main.cpp)

target_link_libraries(view glfw GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi dl)

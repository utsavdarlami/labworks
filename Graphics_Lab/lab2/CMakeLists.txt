# comment use for OPENGL ..mkdir build && cd build , cmake ..

cmake_minimum_required (VERSION 2.6)
project (tra)
add_executable(tra main.cpp)

target_link_libraries(tra glfw GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi dl)
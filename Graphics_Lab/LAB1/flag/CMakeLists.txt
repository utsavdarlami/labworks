# comment use for OPENGL ..mkdir build && cd build , cmake ..

cmake_minimum_required (VERSION 2.6)
project (flag)
add_executable(flag main.cpp)

target_link_libraries(flag glfw GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi dl)

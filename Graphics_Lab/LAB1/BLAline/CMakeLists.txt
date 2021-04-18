# comment use for OPENGL ..mkdir build && cd build , cmake ..

cmake_minimum_required (VERSION 2.6)
project (bla)
add_executable(bla main.cpp)

target_link_libraries(bla glfw GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi dl)

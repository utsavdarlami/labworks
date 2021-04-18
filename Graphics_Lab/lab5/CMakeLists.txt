# comment use for OPENGL ..mkdir build && cd build , cmake ..

cmake_minimum_required (VERSION 2.6)
project (tra3)
add_executable(tra3 main.cpp)

target_link_libraries(tra3 glfw GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi dl)

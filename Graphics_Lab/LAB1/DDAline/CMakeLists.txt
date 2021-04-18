# comment use for OPENGL ..mkdir build && cd build , cmake ..

cmake_minimum_required (VERSION 2.6)
project (sonar)
add_executable(sonar main.cpp)

target_link_libraries(sonar glfw GL GLU GLEW X11 Xxf86vm Xrandr pthread Xi dl)

project(SFMLSandbox)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SFML_DIR "D:/devtools/mingw-w64/Libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(SFMLSandbox main.cpp Animated.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_widgets.cpp imgui/imgui-SFML.cpp imgui/imgui.cpp)

target_include_directories(SFMLSandbox PRIVATE imgui)


target_link_libraries(SFMLSandbox sfml-graphics sfml-audio opengl32)

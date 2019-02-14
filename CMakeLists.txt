# cmake_minimum_required(VERSION <specify CMake version here>)
project(SFMLSandbox)

cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SFML_DIR "D:/devtools/mingw-w64/Libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(SFMLSandbox main.cpp Animated.cpp)
target_link_libraries(SFMLSandbox sfml-graphics sfml-audio)
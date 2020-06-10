cmake_minimum_required(VERSION 3.10)

# Checkeo de la versión de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Compressor VERSION 1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Compressor_SOURCE_DIR})

# Directorio con el código fuente
add_subdirectory(src)
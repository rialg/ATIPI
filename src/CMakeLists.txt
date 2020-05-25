# Build src code
include_directories(${Compressor_SOURCE_DIR}/include)
add_library(GrayImage gray_image.cc)
add_executable(Compressor main.cc)
target_link_libraries(Compressor PUBLIC GrayImage)
target_include_directories(Compressor PUBLIC
                            ${Compressor_BINARY_DIR}
                            ${Compressor_SOURCE_DIR}/src)

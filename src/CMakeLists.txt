# Build src code
include_directories(${Compressor_SOURCE_DIR}/include)

add_library(GreyImage grey_image.cc)
add_library(MedPredictor med_predictor.cc)
add_library(ErrorCalculator error_calculator.cc)
add_library(ContextSignMatrix context_sign_matrix.cc)

add_executable(Compressor main.cc)

target_link_libraries(MedPredictor PUBLIC GreyImage)
target_link_libraries(ErrorCalculator PUBLIC GreyImage)
target_link_libraries(ContextSignMatrix PUBLIC GreyImage)
target_link_libraries(Compressor PUBLIC GreyImage)
target_link_libraries(Compressor PUBLIC MedPredictor)
target_link_libraries(Compressor PUBLIC ErrorCalculator)
target_link_libraries(Compressor PUBLIC ContextSignMatrix)
target_include_directories(Compressor PUBLIC
                            ${Compressor_BINARY_DIR}
                            ${Compressor_SOURCE_DIR}/src)

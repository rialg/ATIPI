# Build src code
include_directories(${Compressor_SOURCE_DIR}/include)

add_library(GreyImage grey_image.cc)
add_library(MedPredictor med_predictor.cc)
add_library(ErrorCalculator error_calculator.cc)
add_library(ContextSignMatrix context_sign_matrix.cc)
add_library(LocalContext local_context.cc)
add_library(GolombEncoder golomb_encoder.cc)
add_library(Decompressor decompressor.cc)
add_library(FileHandler file_handler.cc)

add_executable(Compressor main.cc)

target_link_libraries(MedPredictor PUBLIC GreyImage)
target_link_libraries(MedPredictor PUBLIC LocalContext)
target_link_libraries(ErrorCalculator PUBLIC GreyImage)
target_link_libraries(ContextSignMatrix PUBLIC GreyImage)
target_link_libraries(FileHandler PUBLIC GreyImage)

target_link_libraries(GolombEncoder PUBLIC GreyImage)
target_link_libraries(GolombEncoder PUBLIC LocalContext)

target_link_libraries(Decompressor PUBLIC GreyImage)
target_link_libraries(Decompressor PUBLIC MedPredictor)
target_link_libraries(Decompressor PUBLIC LocalContext)
target_link_libraries(Decompressor PUBLIC GolombEncoder)

target_link_libraries(Compressor PUBLIC GreyImage)
target_link_libraries(Compressor PUBLIC MedPredictor)
target_link_libraries(Compressor PUBLIC ErrorCalculator)
target_link_libraries(Compressor PUBLIC ContextSignMatrix)
target_link_libraries(Compressor PUBLIC LocalContext)
target_link_libraries(Compressor PUBLIC GolombEncoder)
target_link_libraries(Compressor PUBLIC Decompressor)
target_link_libraries(Compressor PUBLIC FileHandler)
target_include_directories(Compressor PUBLIC
                            ${Compressor_BINARY_DIR}
                            ${Compressor_SOURCE_DIR}/src)

# Build src code
include_directories(${MED_Predictor_SOURCE_DIR}/include)
add_library(GrayImage gray_image.cc)
add_executable(MED_Predictor med_predictor.cc)
target_link_libraries(MED_Predictor PUBLIC GrayImage)
target_include_directories(MED_Predictor PUBLIC
                            ${MED_Predictor_BINARY_DIR}
                            ${MED_Predictor_SOURCE_DIR}/src)

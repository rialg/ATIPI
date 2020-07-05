/** @file decompressor.h
 * API de descompresión de imágenes
*/
#ifndef ATIPI_INCLUDE_DECOMPRESSOR_H_
#define ATIPI_INCLUDE_DECOMPRESSOR_H_

#include <string>
#include <cstdint>
#include <cstdlib>
#include "grey_image.h"
#include "local_context.h"
#include "med_predictor.h"
#include "golomb_encoder.h"

using namespace std;

/**
 * @brief Función que descomprime la imagen (code)
 * @param code [in] - Código de Golomb del mapeo de los errores
 * @param height [in] - Cantidad de filas
 * @param width [in] - Cantidad de columnas
 * @param N [in] - Tamaño de los contextos
 * @returns Imagen descomprimida
*/
GreyImage& decompress(const string& code, int height, int width, size_t N);

#endif /// < ATIPI_INCLUDE_DECOMPRESSOR_H_
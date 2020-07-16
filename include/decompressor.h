/** @file decompressor.h
 * API de descompresión de imágenes
*/
#ifndef ATIPI_INCLUDE_DECOMPRESSOR_H_
#define ATIPI_INCLUDE_DECOMPRESSOR_H_

#include <string>
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include "grey_image.h"
#include "local_context.h"
#include "med_predictor.h"
#include "golomb_encoder.h"

using namespace std;

/// @brief Estado de las variables de decompresión
using state = tuple<bool, bool, int, int, int, int, int, int>;

/**
 * @brief Función que descomprime la imagen (code)
 * @param code [in] - Código de Golomb del mapeo de los errores
 * @param height [in] - Cantidad de filas
 * @param width [in] - Cantidad de columnas
 * @param N [in] - Tamaño de los contextos
 * @returns Imagen descomprimida
*/
GreyImage& decompress(const string& code, int height, int width, size_t N);

/**
 * @brief Función que descomprime code en oDecompressed
 * @param code [in] - Parte del código de la imagen comprimida
 * @param oTable [in] - Contextos locales
 * @param height [in] - Cantidad de filas
 * @param width [in] - Cantidad de columnas
 * @param N [in] - Tamaño de los contextos
 * @param oErrorTemp [out] - Errores de predicción de la imagen
 * @param oPred [out] - Predicción med de los valores de la imagen
 * @param oState [out] - Actualización del estado de decompresión
 * @param buffer [out] - Bits remanentes de la última ejecución
 * @param oDecompressed [out] - Imagen de salida (actualizada en cada invocación del procedimiento)
 * @returns Actualización de la decompresión
*/
void stateless_decompress(const string& code, ContextTable& oTable, const int height, const int width, const size_t N, GreyImage& oErrorTemp, GreyImage& oPred, state& oState, string& buffer, GreyImage& oDecompressed);

#endif /// < ATIPI_INCLUDE_DECOMPRESSOR_H_
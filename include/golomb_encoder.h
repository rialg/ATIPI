/** @file golomb_encoder.h
 * Funciones empleadas para la codificación de
 * Golomb del mapeo de los errores de predicción
 */
#ifndef ATIPI_INCLUDE_GOLOMB_ENCODER_H_
#define ATIPI_INCLUDE_GOLOMB_ENCODER_H_

#include <bitset>
#include <vector>
#include <cmath>
#include <regex>
#include "local_context.h"
#include "grey_image.h"
#include "med_predictor.h"
#include "iostream"

using namespace std;

/**
 * @brief Encode a GreyImage using the golomb encoding
 * @returns code
*/
char* golombEncoding(const GreyImage& oImage, size_t N);

/**
 * @brief Orden m=2^k del código de Golomb
 * @param [in] oPixel - Posición del pixel
 * @param [in] oTable - Tabla de contextos locales
 * @param [in] oErrorMatrix - Matrix con errores de predicción
 * @returns m - Orden del código de Golomb para el pixel
*/
int getCodeOrder(const PixelPos& oPixel, ContextTable& oTable, const GreyImage& errorMatrix );

/**
 * @brief Orden m=2^k del código de Golomb
 * @param [in] oPixel - Posición del pixel
 * @param [in] oTable - Tabla de contextos locales
 * @param [in] errorMatrix - Matrix con errores de predicción
 * @returns m - Orden del código de Golomb para el pixel
*/
int getCodeOrder(const PixelPos& oPixel, ContextTable& oTable, int** errorMatrix );

/**
 * @brief Mapeo de Rice
 * @param [in] oErrorMatrix - Matrix con errores de predicción
 * @returns oMappings - Mapeo
*/
GreyImage& RiceMapping( const GreyImage& oErrorMatrix );

/**
 * @brief Mapeo de Rice
 * @param [in] height - Cantidad de filas
 * @param [in] width - Cantidad de columnas
 * @param [in] errorMatrix - Matrix con errores de predicción
 * @returns mappings - Mapeo
*/
GreyImage& RiceMapping( int height, int width, int** errorMatrix );

/**
 * @brief Codificacion de Golomb
 * @param [in] K - K value
 * @param [in] error - error value (mapped by rice)
 * @returns bits codification vector
*/
vector<bool> GolombCodification( int k, int error );

#endif /// < ATIPI_INCLUDE_GOLOMB_ENCODER_H_
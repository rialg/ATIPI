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
const string& golombEncoding(const GreyImage& oImage, size_t N);

/**
 * @brief Orden m=2^k del código de Golomb
 * @param oPixel [in] - Posición del pixel
 * @param oTable [in] - Tabla de contextos locales
 * @param oErrorMatrix [in] - Matrix con errores de predicción
 * @returns m - Orden del código de Golomb para el pixel
*/
int getCodeOrder(const PixelPos& oPixel, ContextTable& oTable, const GreyImage& errorMatrix );

/**
 * @brief Orden m=2^k del código de Golomb
 * @param oPixel [in] - Posición del pixel
 * @param oTable [in] - Tabla de contextos locales
 * @param errorMatrix [in] - Matrix con errores de predicción
 * @returns m - Orden del código de Golomb para el pixel
*/
int getCodeOrder(const PixelPos& oPixel, ContextTable& oTable, int** errorMatrix );

/**
 * @brief Mapeo de Rice
 * @param oErrorMatrix [in] - Matrix con errores de predicción
 * @returns oMappings - Mapeo
*/
GreyImage& RiceMapping( const GreyImage& oErrorMatrix );

/**
 * @brief Mapeo de Rice
 * @param height [in] - Cantidad de filas
 * @param width [in] - Cantidad de columnas
 * @param errorMatrix [in] - Matrix con errores de predicción
 * @returns mappings - Mapeo
*/
GreyImage& RiceMapping( int height, int width, int** errorMatrix );

/**
 * @brief Codificacion de Golomb
 * @param K [in] - K value
 * @param error [in] - error value (mapped by rice)
 * @returns bits codification vector
*/
vector<bool> GolombCodification( int k, int error );

#endif /// < ATIPI_INCLUDE_GOLOMB_ENCODER_H_
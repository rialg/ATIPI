/** @file med_predictor.h
 * Interfaz del predictor MED
 * Median Edge Detector (MED) es un predictor fijo
 * utilizado en LOCO-I para detectar en que puntos de la imagen
 * el brillo cambia abruptamente (es decir, presenta discontinuidades)
 */
#ifndef ATIPI_INCLUDE_MED_PREDICTOR_H_
#define ATIPI_INCLUDE_MED_PREDICTOR_H_

#include <algorithm>
#include "gray_image.h"

using namespace std;

/**
 * @brief funcion que retorna un imagen con las prediciones MED
 * @param [in] oImage - Imagen en escala de gris de entrada
 * @returns predicción
*/
GrayImage& fixed_prediction(GrayImage oImage);

#endif /// < ATIPI_INCLUDE_MED_PREDICTOR_H_
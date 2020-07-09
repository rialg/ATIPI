/** @file med_predictor.h
 * Interfaz del predictor MED
 * Median Edge Detector (MED) es un predictor fijo
 * utilizado en LOCO-I para detectar en que puntos de la imagen
 * el brillo cambia abruptamente (es decir, presenta discontinuidades)
 */
#ifndef ATIPI_INCLUDE_MED_PREDICTOR_H_
#define ATIPI_INCLUDE_MED_PREDICTOR_H_

#include <algorithm>
#include "grey_image.h"
#include "local_context.h"

using namespace std;

/**
 * @brief funcion que retorna un imagen con las prediciones MED
 * @param oImage [in] - Imagen en escala de gris de entrada
 * @returns predicción
*/
GreyImage& fixed_prediction(const GreyImage& oImage);

/**
 * @brief funcion que actualiza las prediciones MED pixel a pixel
 * @param oImage [in] - Imagen en escala de gris de entrada
 * @param oPos [in] - Posición del pixel a actualizar
 * @param oPrediccion [out] - prediccion actualizada
 * @returns predicción actualizada
*/
void update_fixed_prediction(const GreyImage& oImage, const PixelPos& oPos, GreyImage* oPrediccion);

#endif /// < ATIPI_INCLUDE_MED_PREDICTOR_H_
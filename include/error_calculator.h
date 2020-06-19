/** @file error_calculator.h
 * Calcula diferencia entre bit predicho por el MED
 * con bit original de la imagen.
 */
#ifndef ATIPI_INCLUDE_ERROR_CALCULATOR_H_
#define ATIPI_INCLUDE_ERROR_CALCULATOR_H_

#include <algorithm>
#include "grey_image.h"

using namespace std;

/**
 * @brief funcion que retorna una "imagen" con los errores de prediccion
 * @param [in] oImage - Imagen en escala de gris de entrada
 * @returns errores
*/
void calculate_errors(const GreyImage &oImage, const GreyImage &oPrediction, int** errorMatrix);

#endif /// < ATIPI_INCLUDE_ERROR_CALCULATOR_H_
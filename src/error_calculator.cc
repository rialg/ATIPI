/** @file error_calculator.h
 * Calcula diferencia entre bit predicho por el MED
 * con bit original de la imagen. 
 */
#include <string>
#include <iostream>
#include "error_calculator.h"

/**
 * @brief funcion que retorna una "imagen" con los errores de prediccion
 * @param [in] oImage - Imagen en escala de gris de entrada
 * @param [in] oPrediction - Resultado de aplicar MED
 * @param [out] errorMatrix - Matriz de errores de predicción
 * @returns Matriz con errores de predicción usado para hallar el valor de k, necesario para codificar
 *          el error (luego de aplicar el mapeo de Rice).
*/
void calculate_errors(const GreyImage &oImage, const GreyImage &oPrediction, int** errorMatrix){
    for(int row = 1; row < oImage.getHeight() ; ++row){
        errorMatrix[row] = new int[oImage.getHeight()];
        for(int col = 1; col < oImage.getWidth() ; ++col){
            /// Valor del error
            int8_t x_original = oImage(row,col), x_predicted = oPrediction(row,col);
            errorMatrix[row][col] = x_original - x_predicted;
        }
    }
    return ;
}
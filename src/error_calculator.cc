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
 * @returns errores
*/
void calculate_errors(GrayImage &oImage, GrayImage &oPrediction, int** errorMatrix){
    for(int row = 1; row < oImage.getHeight() ; ++row){
        errorMatrix[row] = new int[oImage.getHeight()];
        for(int col = 1; col < oImage.getHeight() ; ++col){
            /// Valor del error
            int8_t x_original = oImage(row,col), x_predicted = oPrediction(row,col);
            errorMatrix[row][col] = x_original - x_predicted;
        }
    }
    return ;
}
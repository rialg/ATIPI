/** @file med_predictor.cc
 * Implementación del predictor MED
 * Median Edge Detector (MED) es un predictor fijo
 * utilizado en LOCO-I para detectar en que puntos de la imagen
 * el brillo cambia abruptamente (es decir, presenta discontinuidades)
 */

#include "med_predictor.h"

/**
 * @brief funcion que retorna un imagen con las prediciones MED
 * @param [in] oImage - Imagen en escala de gris de entrada
 * @returns predicción
*/
GreyImage& fixed_prediction(const GreyImage& oImage)
{
    
    GreyImage* oPrediccion = new GreyImage(oImage.getWidth(), oImage.getHeight());
    /// Saltear primera fila
    for(int row = 1; row < oPrediccion->getWidth() ; ++row)
    {
        /// Saltear primera columna
        for(int col = 1; col < oPrediccion->getHeight() ; ++col)
        {
            /// Asignar predicción
            uint8_t a = oImage(row, col-1), b = oImage(row-1, col), c = oImage(row-1, col-1);
            if( c >= max(a,b) )
                (*oPrediccion)(row, col) = min(a, b);
            else if( c <= min(a,b) )
                (*oPrediccion)(row, col) = max(a, b);
            else
                (*oPrediccion)(row, col) = a + b - c;

        }

    }

    return *oPrediccion;
    
}
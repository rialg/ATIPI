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
    
    GreyImage* oPrediccion = new GreyImage(oImage.getHeight(), oImage.getWidth());
    /// Saltear primera fila
    for(int row = 0; row < oPrediccion->getHeight() ; ++row)
    {
        /// Saltear primera columna
        for(int col = 0; col < oPrediccion->getWidth() ; ++col)
        {
            /// Inicializar el contexto
            uint8_t b = row == 0 ? 0 : oImage(row-1, col),\
                    a = col == 0 ? b : oImage(row, col-1),\
                    c = row == 0 ? 0 : col == 0 ? row-2 > 0 ? oImage(row-2, col) : 0 : oImage(row-1, col-1);

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
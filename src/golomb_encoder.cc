/** @file golomb_encoder.h
 * Funciones empleadas para la codificación de
 * Golomb del mapeo de los errores de predicción
 */

#include "golomb_encoder.h"

/**
 * @brief Orden m=2^k del código de Golomb
 * @param [in] oPixel - Posición del pixel
 * @param [in] oTable - Tabla de contextos locales
 * @param [in] errorMatrix - Matrix con errores de predicción
 * @returns m - Orden del código de Golomb para el pixel
*/
int getCodeOrder(const PixelPos& oPixel, ContextTable& oTable, int** errorMatrix )
{

    /// Si se intenta acceder a una posición invalida, elevar excepción
    /// TODO: Hacer overload de operator[] y agregar la excepción allí
    if( oTable.find(oPixel) == oTable.end() )
        throw new InvalidPixelPositionException();

    if( oTable[ oPixel ].empty() )
        return 2 << (3 - 1); /// < m = 2^3
    else
    {

        /// < Cantidad de errores de predicción
        int n = oTable[oPixel].size();
        /// < Suma de valores absolutos de errores de predicción
        double A = 0;

        for (const auto& oNeighbour : oTable[oPixel] )
        {

            A += abs( errorMatrix[oNeighbour.first][oNeighbour.second] );

        }
        
        return 2 << (static_cast<int>( ceil( log2(A/n) )) - 1); /// m = 2^k
        
    }

}
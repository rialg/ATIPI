/** @file decompressor.c
 * API de descompresión de imágenes
*/
#include "decompressor.h"

/**
 * @brief Función de mapeo de Rice inverso
 * @param mappedError [in] - Error transformado
 * @returns error
*/
inline static int16_t inverseRiceMapping(int mappedError)
{

    if ( mappedError % 2 == 0)
        return (int16_t) (mappedError/2);
    else
        return (int16_t)( -(mappedError+1)/2 );

}

/**
 * @brief Función que descomprime la imagen (code)
 * @param code [in] - Código de Golomb del mapeo de los errores
 * @param height [in] - Cantidad de filas
 * @param width [in] - Cantidad de columnas
 * @param N [in] - Tamaño de los contextos
 * @returns Imagen descomprimida
*/
GreyImage& decompress(const string& code, int height, int width, size_t N)
{

    /// Imagen a descomprimir
    GreyImage* oRet = new GreyImage(height, width);

    /// Obtener los contextos locales
    ContextTable oTable{getLocalContext(N, width, height)};

    /// Empezar el proceso de descompresión
    string sCode{code}, buffer = "";
    bool newPixel = true, startUna = true;
    int row = 0, col = 0, m = 0, k = 0, rem = 0, quot = 0;

    GreyImage oErrorTemp{height, width}, oPred{height, width};

    for(const auto& bit : sCode )
    {
        /// Calcular m
        if(newPixel)
        {

            try
            {

                m = getCodeOrder( PixelPos{row, col}, oTable, oErrorTemp);
                k = ceil(log2((double) m));
                buffer.clear();
                buffer = "";

            } catch (const InvalidPixelPositionException& e) {

                /// Nos encontramos con el padding
                break;

            }
            newPixel = false;

        }

        if( m > 1 && k > 0)
        {

            /// Procesar cod binario
            buffer += string{bit};
            k--;

        } else {

            if(startUna)
            {
                if( m > 1 )
                {
                    rem = (int) strtol( buffer.c_str(), NULL, 2);
                } else
                    rem = 0;
                buffer.clear();
                buffer = "";
                startUna = false;
            }

            if ( bit  == '1' )
            {
                quot = (int) count( buffer.begin(), buffer.end(), '0');

                /// Recuperar pixel
                int16_t error = inverseRiceMapping(quot*m+rem);
                update_fixed_prediction( *oRet, PixelPos{row, col}, &oPred);
                oErrorTemp(row,col) = error;
                (*oRet)(row, col) = error + oPred(row, col);

                if( (col+1) % width == 0 )
                {
                    row++;
                    col = 0;
                }
                else
                    col++;

                startUna = true;
                newPixel = true;
            } else {

                buffer += string{bit};

            }

        }

    }

    return *oRet;
}
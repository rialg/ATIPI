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
    ContextTable oTable{getLocalContext(N, height, width)};

    /// Empezar el proceso de descompresión
    string sCode{code}, buffer = "";
    bool newPixel = true, startUna = true;
    int row = 0, col = 0, m = 0, k = 0, rem = 0, quot = 0, count = 0;

    for(const auto& bit : sCode )
    {
        if(newPixel)
        {

            /// Calcular m
            GreyImage oErrorTemp = (*oRet) - fixed_prediction(*oRet);
            m = getCodeOrder( PixelPos{row, col}, oTable, oErrorTemp);
            k = ceil(log2((double) m));

            buffer = string{bit};
            newPixel = false;
            k--;
        
        } else {

            /// Procesar cod binario
            if( k > 0 )
            {

                buffer += string{bit};
                k--;

            } else { /// Procesar cod unario

                if(startUna)
                {

                    rem = (int) strtol( buffer.c_str(), NULL, 2);
                    buffer.clear();
                    buffer = string{bit};
                    startUna = false;

                }

                if ( bit  == '1' )
                {

                    quot = count;
                    /// Recuperar pixel
                    int16_t error = inverseRiceMapping(quot*m+rem);
                    GreyImage oPred = fixed_prediction(*oRet);
                    (*oRet)(row, col) = error + oPred(row, col);
                    if( (col+1) % width == 0 )
                    {
                        row++;
                        col = 0;
                    }
                    else
                        col++;

                    count = 0;
                    startUna = true;
                    newPixel = true;

                } else {

                    count++;

                }

            }

        }

    }

    return *oRet;

}
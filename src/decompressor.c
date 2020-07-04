/** @file decompressor.c
 * API de descompresión de imágenes
*/
#include "decompressor.h"

/**
 * @brief Función de mapeo de Rice inverso
 * @param mappedError [in] - Error transformado
 * @returns error
*/
inline static int16_t& inverseRiceMapping(int mappedError)
{

    return mappedError % 2 == 0 ? mappedError/2 : -(mappedError+1)/2 ;

}

/**
 * @brief Función que descomprime la imagen (code)
 * @param code [in] - Código de Golomb del mapeo de los errores
 * @param height [in] - Cantidad de filas
 * @param width [in] - Cantidad de columnas
 * @param N [in] - Tamaño de los contextos
 * @returns Imagen descomprimida
*/
GreyImage& decompress(const char* code, int height, int width, size_t N)
{
    /// Imagen a descomprimir
    GreyImage* oRet = new GreyImage(height, width);

    /// Obtener los contextos locales
    ContextTable oTable{getLocalContext(N, height, width)};

    /// Empezar el proceso de descompresión
    string sCode{code}, buffer = "";
    bool newPixel = true;
    int row = 0, col = 0, m = 0;

    for(const auto& bit :sCode )
    {

        
        if(newPixel)
        {

            GreyImage oErrorTemp = oRet - fixed_prediction(oRet);
            m = getCodeOrder( PixelPos{row, col}, oTable, oErrorTemp);

            buffer += to_string(bit);

        }

    }

    return oRet;

}
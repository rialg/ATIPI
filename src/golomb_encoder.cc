/** @file golomb_encoder.h
 * Funciones empleadas para la codificación de
 * Golomb del mapeo de los errores de predicción
 */

#include "golomb_encoder.h"
//#include <iostream>

//using namespace std;

/**
 * @brief Orden m=2^k del código de Golomb
 * @param [in] oPixel - Posición del pixel
 * @param [in] oTable - Tabla de contextos locales
 * @param [in] oErrorMatrix - Matrix con errores de predicción
 * @returns m - Orden del código de Golomb para el pixel
*/
int getCodeOrder(const PixelPos& oPixel, ContextTable& oTable, const GreyImage& oErrorMatrix )
{

    /// Si se intenta acceder a una posición invalida, elevar excepción
    try {

        if( oTable[ oPixel ].empty() )
            return 1 << 3; /// < m = 2^3
        else
        {

            /// < Cantidad de errores de predicción
            int n = oTable[oPixel].size();
            /// < Suma de valores absolutos de errores de predicción
            double A = 0;

            for (const auto& oNeighbour : oTable[oPixel] )
            {

                A += abs( oErrorMatrix(oNeighbour.first, oNeighbour.second) );

            }

            return 1 << static_cast<int>( ceil( log2(A/n) )); /// m = 2^k

        }

    } catch ( InvalidPixelPositionException& e)
    {

        throw e;

    }
}

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
    try {

        if( oTable[ oPixel ].empty() )
            return 1 << 3; /// < m = 2^3
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

            return 1 << static_cast<int>( ceil( log2(A/n) )); /// m = 2^k

        }

    } catch ( InvalidPixelPositionException& e)
    {

        throw e;

    }
}

/**
 * @brief Mapeo de Rice
 * @param [in] height - Cantidad de filas
 * @param [in] width - Cantidad de columnas
 * @param [in] errorMatrix - Matrix con errores de predicción
 * @returns mappings - Mapeo
*/
GreyImage& RiceMapping( int height, int width, int** errorMatrix )
{

    GreyImage* mappings = new GreyImage(height, width);
    for( int row = 0; row < height ; ++row )
        for ( int col = 0; col < width ; ++col )
        {

            int error = errorMatrix[row][width];

            if( error < 0 )
                (*mappings)(row, col) = -2 * error - 1;
            else
                (*mappings)(row, col) = 2 * error;

        }
    return *mappings;

}

/**
 * @brief Mapeo de Rice
 * @param [in] oErrorMatrix - Matrix con errores de predicción
 * @returns oMappings - Mapeo
*/
GreyImage& RiceMapping( const GreyImage& oErrorMatrix )
{

    GreyImage* oMappings = new GreyImage( oErrorMatrix.getHeight(), oErrorMatrix.getWidth());
    for( int row = 0; row < oMappings->getHeight() ; ++row )
        for ( int col = 0; col <  oMappings->getWidth(); ++col )
            (*oMappings)(row, col) = oErrorMatrix(row, col) > 0 ? 2 * oErrorMatrix(row, col) : -2 * oErrorMatrix(row, col) - 1;

    return *oMappings;
}

/**
 * @brief Encoding function
 * @returns code
*/
char* golombEncoding(const GreyImage& oImage, size_t N)
{

    /// 1. Apply MED
    GreyImage oPrediction = fixed_prediction(oImage);

    /// 2. Find prediction error
    GreyImage oError = oImage - oPrediction;

    /// 3. Find Rice mapping
    GreyImage oRiceMap = RiceMapping(oError);

    /// 4. Calculate context table for a given N size
    ContextTable oTable{ getLocalContext( N, oImage.getWidth(), oImage.getHeight()) };

    /// 5. Calculate the compressed image code
    string sCode = "";
    for(int row = 0; row < oImage.getHeight() ; ++row)
        for(int col = 0; col < oImage.getWidth() ; ++col)
        {
            int m = getCodeOrder(PixelPos{row, col} , oTable, oError);
            div_t result = div(oRiceMap(row, col), m);
            //cout << "RiceMapping " << oRiceMap(row, col) << " m " << m << endl;
            string codification{""};

            /// bin(rice mod m)
            if( m > 1 )
            {
                //cout << "rem " << result.rem << endl;
                int exp = result.rem > 0 ? floor(log2((double) result.rem)) : 0;
                int rem = result.rem > 0 ? result.rem - (1 << exp) : 0;
                codification = result.rem > 0 ? "1" : "0";

                for(int i = 0; i < exp; ++i )
                    codification += "0";

                while(rem > 0)
                {

                    exp = floor(log2((double) rem));
                    rem -= 1 << exp;
                    codification[codification.length() - 1 - exp] = '1';

                }
                int k = ceil(log2((double) m));
                for(int j=0; j < k - codification.length(); ++j)
                    codification = "0"+codification;
            //cout << "bin " << codification << endl;
            }

            /// uni(rice div m)
            for(int i=0; i<result.quot; i++){
                codification += "0";
            }
            codification += "1";
            //cout << "cod " << codification << endl;
            sCode += codification;
        }

    return const_cast<char*>(sCode.c_str());
}

/**
 * @brief Codificacion de Golomb
 * @param [in] K - K value
 * @param [in] error - error value (mapped by rice)
 * @returns codification bitset
*/
vector<bool> GolombCodification( int m, int error )
{
    vector<bool> codification;
    int bits = log2(m);

    div_t result = div(error, m);
    string binary = bitset<8>(result.rem).to_string();


    // Pusheamos unary
    for(int i=0; i<result.quot; i++){
        codification.push_back(true);
    }
    codification.push_back(false);

    //Pusheamos binary, empezamos en (8-bits) para tener log2(m) bits codificando el resto.
    for(int j=(8-bits); j<binary.size(); j++){
        if (binary[j]=='1'){
            codification.push_back(true);
        }else {
            codification.push_back(false);
        }
    }

    // cout << "The vector is:" << endl << "    ";
    // for (const auto& b : codification) {
    //     cout << b << " ";
    // }
    // cout << endl;    
    return codification;
}

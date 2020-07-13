/** @file main.cc
 * Pruebas con el predictor MED
 */

#include <string>
#include <iostream>
//#include <memory>
#include "grey_image.h"
#include "med_predictor.h"
#include "error_calculator.h"
#include "context_sign_matrix.h"
#include "local_context.h"
#include "golomb_encoder.h"
#include "decompressor.h"
#include "file_handler.h"

/// Usar namespace de la biblioteca estándar
using namespace std;

static int** initialize_errors_matrix(int height, int width){
    int** errors = new int*[height];
    for (int h = 0; h < height; h++){
            errors[h] = new int[width];
            for (int w = 0; w < width; w++){
                  // fill in some initial values
                  errors[h][w] = 0;
            }
      }
      return errors;
}

static inline const vector<bool>& transformData( const string& code )
{

    // Test
    vector<char> cBits(code.begin(), code.end());
    vector<bool>* bBits = new vector<bool>();
    for(const char& c: cBits)
        bBits->push_back( c == '1');

    return *bBits;

}

int main(int argc, char* argv[])
{
    
    if(argc < 3)
    {

        cout << "USAGE: Compressor <image-path> <N>" << endl;
        exit(-1);

    }

    GreyImage oImg( argv[1] );
/*
    GreyImage oImg{4 , 6};
    oImg(0,0) = 42;
    oImg(0,1) = 84;
    oImg(0,2) = 42;
    oImg(0,3) = 84;
    oImg(0,4) = 244;
    oImg(0,5) = 254;
    //oImg(0,6) = 244;
    //oImg(0,7) = 254;
    oImg(1,0) = 200;
    oImg(1,1) = 150;
    oImg(1,2) = 26;
    oImg(1,3) = 68;
    oImg(1,4) = 20;
    oImg(1,5) = 25;
    //oImg(1,6) = 150;
    //oImg(1,7) = 26;
    oImg(2,0) = 142;
    oImg(2,1) = 184;
    oImg(2,2) = 26;
    oImg(2,3) = 138;
    oImg(2,4) = 78;
    oImg(2,5) = 78;
    //oImg(2,6) = 138;
    //oImg(2,7) = 78;
    oImg(2,5) = 22;
    oImg(3,0) = 2;
    oImg(3,1) = 4;
    oImg(3,2) = 126;
    oImg(3,3) = 198;
    oImg(3,4) = 219;
    oImg(3,5) = 251;
    //oImg(3,6) = 111;
    //oImg(3,7) = 82;
    //oImg(4,0) = 111;
    //oImg(4,1) = 82;
    //oImg(4,2) = 116;
    //oImg(4,3) = 148;
    //oImg(4,4) = 10;
    //oImg(4,5) = 22;
    //oImg(4,6) = 148;
    //oImg(4,7) = 10;
    //oImg(5,0) = 4;
    //oImg(5,1) = 81;
    //oImg(5,2) = 226;
    //oImg(5,3) = 38;
    //oImg(5,4) = 30;
    //oImg(5,5) = 242;
    //oImg(5,6) = 81;
    //oImg(5,7) = 226;
    //oImg(6,0) = 200;
    //oImg(6,1) = 150;
    //oImg(6,2) = 26;
    //oImg(6,3) = 68;
    //oImg(6,4) = 20;
    //oImg(6,6) = 244;
    //oImg(6,7) = 254;
    //oImg(7,2) = 116;
    //oImg(7,3) = 148;
    //oImg(7,4) = 10;
    //oImg(7,5) = 22;
    //oImg(7,6) = 148;
    //oImg(7,7) = 10;
    //oImg(7,0) = 4;
    //oImg(7,1) = 81;
*/
    //GreyImage oPred = fixed_prediction(oImg);

    /// Comprimir archivo
    string compressCode{golombEncoding(oImg, atoi(argv[2]))};
    //cout << "" << compressCode << endl;
    copy_to_file("archivo_comprimido", "P5", oImg.getWidth(), oImg.getHeight(), atoi(argv[2]), transformData(compressCode));

    /// Descomprimir archivo
    compressData oCompressData{ read_compressed("archivo_comprimido.loco") };
    //cout << "code2>" << get<0>(oCompressData) << endl;
    GreyImage oDecompress = decompress( get<0>(oCompressData), get<1>(oCompressData), get<2>(oCompressData), get<3>(oCompressData));

    /// Guardar en imagenes
    oImg.save("original.pgm");
    oDecompress.save("decompress.pgm");

    exit(0);

}
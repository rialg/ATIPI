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

int main(int argc, char *argv[])
{
  
    
    //GreyImage oImg("test/Imagenes-LOCO-PGM+PPM/barbara.pgm");
    //GreyImage oPrediction = fixed_prediction(oImg);
    
    GreyImage oImg{2 , 2};
    oImg(0,0) = 90;
    oImg(0,1) = 50;
    oImg(1,0) = 107;
    oImg(1,1) = 71;
    GreyImage oPred = fixed_prediction(oImg);
    const char* compressCode = golombEncoding(oImg, 2); 
    cout << "Compressed code: " << compressCode << endl;

    GreyImage oDecompress = decompress( compressCode, oImg.getHeight(), oImg.getWidth(), 2);

    oImg.save("original.pgm");
    oDecompress.save("decompress.pgm");
    for(int row = 0; row < oImg.getHeight() ; ++row )
        for(int col = 0; col < oImg.getWidth() ; ++col )
        {
            cout << "Img : ( " << row << ", " << col << ") = " << (int)oImg(row,col) << endl;
            cout << "Decompress : ( " << row << ", " << col << ") = " << (int)oDecompress(row,col) << endl;
            cout << endl;
        }

    exit(0);

}
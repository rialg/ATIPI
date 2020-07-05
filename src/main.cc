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
    //oImg.save("original_img.pgm");
    //oPrediction.save("med_new.pgm");
    /*
    int** errors = initialize_errors_matrix(oIMG.getHeight(),oIMG.getWidth());
    calculate_errors(oIMG, oPrediction, errors);
    printf("error on (row,col) (15,15) %i", errors[15][15]);

    cout << "\ncontextMat height: " << sizeof(errors) << " and contextMat width: " << sizeof(errors[0]) << endl;


    ContextSignMatrix contexts(oIMG);
    cout << "\ncontext of (row,col) (15,15): " << contexts(15,15).q1 << "," << contexts(15,15).q2 << "," << contexts(15,15).q3 << endl;
    cout << "\ncontextMat width: " << contexts.getWidth() << " and contextMat height: " << contexts.getHeight() << endl;
    

     /// Ejemplo de calculo de contexto local
    ContextTable oTable{ getLocalContext(3, oIMG.getWidth(), oIMG.getHeight()) };
    /// Ejemplo de calculo de orden del código de golomb para un pixel
    try
    {
    
        cout << "* Orden m para pixel (0, 0):" << getCodeOrder( PixelPos{0, 0}, oTable, errors) << endl;
        cout << "* Orden m para pixel (3, 500):" << getCodeOrder( PixelPos{3, 500}, oTable, errors) << endl;
        cout << "* Orden m para pixel (600, 500):" << getCodeOrder( PixelPos{600, 500}, oTable, errors) << endl;
    
    } catch( InvalidPixelPositionException* e ) {

        cerr << e->what() << endl;
        cout << e->what() << endl;
        //exit(-1);

    }
    

    GreyImage oMap{ RiceMapping(oPrediction.getHeight(), oPrediction.getWidth(), errors) };
    oMap.save("errors_img.pgm");
    */
    GreyImage oImg{2 , 2};
    oImg(0,0) = 90;
    oImg(0,1) = 50;
    oImg(1,0) = 107;
    oImg(1,1) = 71;
    /*
    oImg.save("imagen_pruebas.pgm");
    
    GreyImage oPrediction = fixed_prediction(oImg);
    GreyImage oError = oImg - oPrediction;
    oPrediction.save("image_pruebas_prediccion.pgm");

    for(int row = 0; row < oPrediction.getHeight() ; ++row )
        for(int col = 0; col < oPrediction.getWidth() ; ++col )
        {
            cout << "Img : ( " << row << ", " << col << ") = " << (int)oImg(row,col) << endl;
            cout << "Pred : ( " << row << ", " << col << ") = " << (int)oPrediction(row,col) << endl;
            cout << "Error : ( " << row << ", " << col << ") = " << (int)oError(row,col) << endl;
            cout << endl;
        }
    */

    cout << golombEncoding(oImg, 2) << endl;

    exit(0);

}
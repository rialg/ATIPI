/** @file main.cc
 * Pruebas con el predictor MED
 */

#include <string>
#include <iostream>
//#include <memory>
/*#include "grey_image.h"
#include "med_predictor.h"
#include "error_calculator.h"
#include "context_sign_matrix.h"*/
#include "local_context.h"

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
    /*
    GreyImage oIMG("test/Imagenes-LOCO-PGM+PPM/barbara.pgm");
    GreyImage oPrediction = fixed_prediction(oIMG);
    oIMG.save("original_img.pgm");
    oPrediction.save("med.pgm");

    int** errors = initialize_errors_matrix(oIMG.getHeight(),oIMG.getWidth());
    calculate_errors(oIMG, oPrediction, errors);
    printf("error on (row,col) (15,15) %i", errors[15][15]);
    cout << "\ncontextMat height: " << sizeof(errors) << " and contextMat width: " << sizeof(errors[0]);


    ContextSignMatrix contexts(oIMG);
    cout << "\ncontext of (row,col) (15,15): " << contexts(15,15).q1 << "," << contexts(15,15).q2 << "," << contexts(15,15).q3;
    cout << "\ncontextMat width: " << contexts.getWidth() << " and contextMat height: " << contexts.getHeight();
      */

     /// Ejemplo de calculo de contexto local
    ContextTable oTable{ getLocalContext(3, 3, 3) };
    for (const auto &entry : oTable) 
    {
        
        cout << "px: ( " << entry.first.first << ", " << entry.first.second << ") :" << endl;
        for(const auto &close : entry.second)
        {

            cout << "\tcercano: ( " << close.first << ", " << close.second << ")" << endl;

        }

    }

    exit(0);
}
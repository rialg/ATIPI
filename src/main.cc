/** @file main.cc
 * Pruebas con el predictor MED
 */

#include <iostream>
//#include <memory>
#include "grey_image.h"
#include "med_predictor.h"

/// Usar namespace de la biblioteca estándar
using namespace std;

int main(void)
{

    GreyImage oIMG("test/Imagenes-LOCO-PGM+PPM/barbara.pgm");
    oIMG.save("original_img.pgm");
    GreyImage oPrediction = fixed_prediction(oIMG);
    oPrediction.save("med.pgm");

    exit(0);
}
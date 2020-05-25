/** @file main.cc
 * Pruebas con el predictor MED
 */

#include <iostream>
#include "gray_image.h"

/// Usar namespace de la biblioteca estándar
using namespace std;

int main(void)
{

    GrayImage oIMG("test/Imagenes-LOCO-PGM+PPM/barbara.pgm");
    oIMG.save("prueba.pgm");

    exit(0);
}
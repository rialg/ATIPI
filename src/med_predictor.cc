/** @file med_predictor.c
 * Implementación del predictor MED
 * Median Edge Detector (MED) es un predictor fijo
 * utilizado en LOCO-I para detectar en que puntos de la imagen
 * el brillo cambia abruptamente (es decir, presenta discontinuidades)
 */

#include <iostream>
#include "med_predictor.h"

/// Usar namespace de la biblioteca estándar
using namespace std;

int main(void)
{

    GrayImage oIMG("test/Imagenes-LOCO-PGM+PPM/barbara.pgm");
    cout << oIMG(100,512) << endl;

    exit(0);
}
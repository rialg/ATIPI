/** @file gray_image.h
 * Interfaz de la clase GrayImage
 * Parseo de imagenes en formato PGM a un
 * objeto GrayImage
 * @see http://netpbm.sourceforge.net/doc/pgm.html
 */
#ifndef ATIPI_INCLUDE_GRAY_IMAGE_H_
#define ATIPI_INCLUDE_GRAY_IMAGE_H_

#include <exception>
#include <fstream>
#include <cstdint>
#include <string>

using namespace std;

/**
 * @class Grayimage
 * @brief Objeto imagen en escala de grises
*/
class GrayImage
{

    public:
        GrayImage();                        /// < Constructor por defecto
        GrayImage(const char* imageFile);   /// < Constructor
        ~GrayImage();                       /// < Destructor

    private:
        int width = 0;                  /// < Ancho de la imagen
        int height = 0;                 /// < Alto de la imagen
        uint8_t* imageMat = nullptr;   /// < Matriz de pixeles

};

/**
 * @class InvalidImageFormatException
 * @brief   Excepción usada para controlar que el formato de las imagenes
 *          PGM sea el adecuado, es decir, el número mágico sea "P5"
*/
class InvalidImageFormatException : public exception
{

    /**
     * @brief Explicación del error
     * @returns Texto explicativo
    */
    const char* what() const throw ()
    {

        return "El archivo no tiene el formato raw PGM";

    };

};

#endif /// < ATIPI_INCLUDE_GRAY_IMAGE_H_
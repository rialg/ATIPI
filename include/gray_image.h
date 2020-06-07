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
#include <tuple>

using namespace std;

/**
 * @class Grayimage
 * @brief Objeto imagen en escala de grises
*/
class GrayImage
{

    public:
        GrayImage();                        /// < Constructor por defecto
        GrayImage(int width, int height);   /// < Constructor
        GrayImage(const char* imageFile);   /// < Constructor
        ~GrayImage();                       /// < Destructor

        ///@brief Método de acceso
        uint8_t& operator()(size_t row, size_t col) { return imageMat[ row*width + col ]; };
        ///@brief Método de acceso sin modificar valor
        const uint8_t& operator()(size_t row, size_t col) const { return imageMat[ row*width + col ]; };
        ///@brief Método para guardar imageMat en un archivo PGM
        void save(const char* fileName);
        ///@brief Accessor
        int getWidth(){ return width; };
        ///@brief Accessor
        int getHeight(){ return height; };
        ///@brief Accessor
        uint8_t* getImageMat(){ return imageMat; };
        ///@brief Accessor
        const tuple<int, int> getShape(){ return tuple<int, int>(width, height); };

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
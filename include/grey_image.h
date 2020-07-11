/** @file grey_image.h
 * Interfaz de la clase GreyImage
 * Parseo de imagenes en formato PGM a un
 * objeto GreyImage
 * @see http://netpbm.sourceforge.net/doc/pgm.html
 */
#ifndef ATIPI_INCLUDE_GREY_IMAGE_H_
#define ATIPI_INCLUDE_GREY_IMAGE_H_

#include <exception>
#include <fstream>
#include <cstdint>
#include <string>
#include <tuple>

using namespace std;

/**
 * @class Greyimage
 * @brief Objeto imagen en escala de grises
*/
class GreyImage
{

    public:
        GreyImage();                                /// < Constructor por defecto
        GreyImage(int height, int width);           /// < Constructor
        GreyImage(const GreyImage& oImg);           /// < Copy Constructor
        GreyImage& operator=(const GreyImage& oImg);/// < Copy Assigment
        GreyImage(const char* imageFile);           /// < Constructor
        ~GreyImage();                               /// < Destructor

        ///@brief Método de acceso
        int16_t& operator()(size_t row, size_t col) { return imageMat[ row * height + col ]; };
        ///@brief Método de acceso sin modificar valor
        const int16_t& operator()(size_t row, size_t col) const { return imageMat[ row * height + col ]; };
        ///@brief Método de acceso sin modificar valor
        const int16_t& operator[](size_t position) const { return imageMat[ position ]; };
        /// @brief Operador de adición
        GreyImage& operator+=(const GreyImage& oDer);
        /// @brief Operador de substracción
        GreyImage& operator-=(const GreyImage& oDer);
        ///@brief Método para guardar imageMat en un archivo PGM
        void save(const char* fileName) const;
        ///@brief Accessor
        const int getWidth() const { return width; };
        ///@brief Accessor
        const int getHeight() const { return height; };
        ///@brief Accessor
        const tuple<int, int> getShape() const { return tuple<int, int>(width, height); };

    private:
        int width = 0;                  /// < Ancho de la imagen
        int height = 0;                 /// < Alto de la imagen
        int16_t* imageMat = nullptr;   /// < Matriz de pixeles

};

/**
 * @brief Operador de adición
*/
GreyImage& operator+(const GreyImage& oIzq, const GreyImage& oDer);

/**
 * @brief Operador de substracción
*/
GreyImage& operator-(const GreyImage& oIzq, const GreyImage& oDer);

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

/**
 * @class InvalidDimensionsException
 * @brief   Excepción usada para indicar que se opera con imágenes de
 *          diferente tamaño
*/
class InvalidDimensionsException : public exception
{

    /**
     * @brief Explicación del error
     * @returns Texto explicativo
    */
    const char* what() const throw ()
    {

        return "Se esta operando con imagenes de diferentes dimensiones";

    };

};

#endif /// < ATIPI_INCLUDE_GREY_IMAGE_H_
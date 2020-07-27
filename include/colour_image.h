/** @file colour_image.h
 * Interfaz de la clase ColourImage
 * Parseo de imagenes en formato PPM a tres
 * objetos de tipo GreyImage (ColourImage)
 * @see http://netpbm.sourceforge.net/doc/pgm.html
 */
#ifndef ATIPI_INCLUDE_COLOUR_IMAGE_H_
#define ATIPI_INCLUDE_COLOUR_IMAGE_H_

#include "grey_image.h"

/// @brief Enumeracion de colores
enum Colour {RED = 0, GREEN = 1, BLUE = 2};

/**
 * @class ColourImage
 * @brief Objeto imagen a color (RGB)
*/
class ColourImage
{

    public:
        ColourImage();                                /// < Constructor por defecto
        ColourImage(int height, int width);           /// < Constructor
        ColourImage(const GreyImage& oRed,
                    const GreyImage& oGreen,
                    const GreyImage& oBlue);           /// < Constructor
        ColourImage(const ColourImage& oImg);           /// < Copy Constructor
        ColourImage& operator=(const ColourImage& oImg);/// < Copy Assigment
        ColourImage(const char* imageFile);           /// < Constructor
        ~ColourImage();                               /// < Destructor

        ///@brief Método de acceso
        int16_t& getRedPixel(size_t row, size_t col) { return (*oRed)(row, col ); };
        ///@brief Método de acceso
        int16_t& getGreenPixel(size_t row, size_t col) { return (*oGreen)(row, col ); };
        ///@brief Método de acceso
        int16_t& getBluePixel(size_t row, size_t col) { return (*oBlue)(row, col ); };
        ///@brief Método de acceso
        GreyImage& getRedImage() const { return (*oRed); };
        ///@brief Método de acceso
        GreyImage& getGreenImage() const { return (*oGreen); };
        ///@brief Método de acceso
        GreyImage& getBlueImage() const { return (*oBlue); };
        /// @brief Operador de adición
        ColourImage& operator+=(const ColourImage& oDer);
        /// @brief Operador de substracción
        ColourImage& operator-=(const ColourImage& oDer);
        ///@brief Método para guardar imageMat en un archivo PGM
        void save(const char* fileName) const;
        ///@brief Accessor
        const int getWidth() const { return oRed->getWidth(); };
        ///@brief Accessor
        const int getHeight() const { return oRed->getHeight(); };
        ///@brief Accessor
        const tuple<int, int> getShape() const { return tuple<int, int>(oRed->getWidth(), oRed->getHeight()); };
        /// @brief Transformation of colour planes
        void transform();
        /// @brief Undo transformation of colour planes
        void undoTransform();

    private:
        GreyImage* oRed = nullptr; /// < Tono de rojo
        GreyImage* oGreen = nullptr; /// < Tono de verde
        GreyImage* oBlue = nullptr; /// < Tono de azul

};

/** 
 * @brief Operador de adición
 * @param oIzq [in] - Operando derecho 
 * @param oDer [in] - Operando derecho
 * @returns Resultado de la suma
*/
ColourImage& operator+(const ColourImage& oIzq, const ColourImage& oDer);

/** 
 * @brief Operador de substracción
 * @param oIzq [in] - Operando derecho 
 * @param oDer [in] - Operando derecho
 * @returns Resultado de la resta
*/
ColourImage& operator-(const ColourImage& oIzq, const ColourImage& oDer);

#endif /// < ATIPI_INCLUDE_COLOUR_IMAGE_H_
/** @file context_sign_matrix.h
 * clase que contiene una matris de context signs
 * ([qi, q2, q3], signo)
 * objeto ContextSignMatrix
 */
#ifndef ATIPI_INCLUDE_CONTEXT_SIGN_MATRIX_H_
#define ATIPI_INCLUDE_CONTEXT_SIGN_MATRIX_H_

#include <fstream>
#include <cstdint>
#include <tuple>
#include "grey_image.h"


using namespace std;

/**
 * @class contextSign
 * @brief Clase de contexto
*/
struct contextSign
{

    public:
        int q1 = 0; /// < Default
        int q2 = 0; /// < Default
        int q3 = 0; /// < Default
        bool changedSign = false;   /// < Default

};

/**
 * @class ContextSignMatrix
 * @brief Matriz con contextos y signos
*/
class ContextSignMatrix
{

    public:
        ContextSignMatrix();                             /// < Constructor por defecto
        ContextSignMatrix(int width, int height);        /// < Constructor
        ContextSignMatrix(const GreyImage& oIMG);              /// < Constructor
        ~ContextSignMatrix();                            /// < Destructor

        ///@brief Método de acceso
        contextSign& operator()(size_t row, size_t col) { return contextMat[ row*width + col ]; };
        ///@brief Accessor
        int getWidth(){ return width; };
        ///@brief Accessor
        int getHeight(){ return height; };
        ///@brief Accessor
        contextSign* getContextMat(){ return contextMat; };
        ///@brief Accessor
        const tuple<int, int> getShape(){ return tuple<int, int>(width, height); };

    private:
        int width = 0;                                                    /// < Ancho de la imagen
        int height = 0;                                                   /// < Alto de la imagen
        contextSign* contextMat = nullptr;                                /// < Matriz de contextos
        contextSign context_around(const GreyImage& oImage, int row, int col);  /// < Context around pixel
        int8_t region(int8_t value);                                      /// < region of gradient


};

#endif /// < ATIPI_INCLUDE_CONTEXT_SIGN_MATRIX_H_
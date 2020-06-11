/** @file context_sign_matrix.h
 * clase que contiene una matris de context signs
 * ([qi, q2, q3], signo)
 * objeto ContextSignMatrix
 */
#include "context_sign_matrix.h"

/// @brief Constructor por defecto
ContextSignMatrix::ContextSignMatrix(){};

/**
 * brief Constructor
 * @param [in] width - ancho de la imagen
 * @param [in] height - alto de la imagen
*/
ContextSignMatrix::ContextSignMatrix(int width, int height):
width{width}, 
height{height}, 
contextMat{new contextSign[width*height]}
{
    for( int i = 0; i < width*height; ++i )
        contextMat[i] = contextSign{0,0,0, false};

};

/**
 * brief Constructor
 * @param [in] oIMG - image
*/
ContextSignMatrix::ContextSignMatrix(const GreyImage& oIMG):
width{oIMG.getWidth()}, 
height{oIMG.getHeight()}, 
contextMat{new contextSign[width*height]}
{
   for (int row=1; row<height;row++){
            for (int col=1; col<width;col++){
                  contextMat[row*width + col] = context_around(oIMG, row ,col);  /* method that calculates the context*/
            }
    }

};

contextSign ContextSignMatrix::context_around(const GreyImage& oImage, int row, int col){

    /*
    Dados los bits:
        | c | b | d |
    | e | a | x | ...
    Agregamos fila0 y columna0 repetidas (extendemos fila un bit con repeticion del bit0)
        g1 = (d-b)
        g2 = (b-c)
        g3 = (c-a)
    */
   int8_t q1, q2, q3;
   contextSign context;

    if (col==oImage.getWidth()){      /*borde derecho - unexistant d ==> d=b*/
        int8_t  g1 = 0,
                g2 = oImage(row-1, col)-oImage(row-1, col-1),
                g3 = oImage(row-1, col-1) - oImage(row, col-1);

        q1 = region(g1);
        q2 = region(g2);
        q3 = region(g3);
    }
    else {
        int8_t g1 = oImage(row-1, col+1) - oImage(row-1, col),
               g2 = oImage(row-1, col) - oImage(row-1, col-1),
               g3 = oImage(row-1, col-1) - oImage(row, col-1);
        
        q1 = region(g1);
        q2 = region(g2);
        q3 = region(g3);
    }

    if (q1 < 0) {
        context = { -q1, -q2, -q3, true};
        return context;
    }else {
        context = { q1, q2, q3, false};
        return context;
    }
};

int8_t ContextSignMatrix::region(int8_t value){
    if (value <= -21) {
        return -4;
    }else if (-21 < value && value <= -7 ){
        return -3;
    }else if (-7 < value && value <= -3 ){
        return -2;
    }else if (-3 < value && value < 0 ){
        return -1;
    }else if ( value==0 ){
        return 0;
    }else if (3 > value && value > 0 ){
        return 1;
    }else if (7 > value && value >= 3 ){
        return 2;
    }else if (21 > value && value >= 7 ){
        return 3;
    }else if (value >= 21 ){
        return 4;
    }
};


/// @brief Destructor
ContextSignMatrix::~ContextSignMatrix()
{

    if(contextMat != nullptr)
        delete[] contextMat;
    
};
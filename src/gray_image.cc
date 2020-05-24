/** @file gray_image.cc
 * Implementación de la clase GrayImage
 * Parseo de imagenes en formato PGM a un
 * objeto GrayImage
 * @see http://netpbm.sourceforge.net/doc/pgm.html
 */

#include "gray_image.h"

/// @brief Constructor por defecto
GrayImage::GrayImage(){};

/**
 * @brief Constructor
 * @param [in] imageFile - ruta al archivo de la imagen
*/ 
GrayImage::GrayImage(const char* imageFile)
{

    /**
     * Parsear el contenido de los archivos PGM
    */
    ifstream oImageStream(imageFile, ios::binary);
    string line;
    
    /// Validar el formato del archivo
    getline(oImageStream, line);
    if( line.find( "P5" ) == string::npos )
        throw InvalidImageFormatException();
    
    /// Tomar dimensiones
    getline(oImageStream, line);
    width = stoi(line.substr(0, line.find(" ")));
    height = stoi(line.substr(line.find(" "), line.length() ));
    
    /// Crear arreglo de la imagen
    imageMat = new uint8_t[width*height];
    
    getline(oImageStream, line); /// < Descartar max_val
    
    int row = 0;
    while( getline(oImageStream, line) )
    {
        int col = 0;
        for(char c : line)
        {

            imageMat[row+col] = (uint8_t) c;
            col++;
        
        }
        row++;

    }
    
    oImageStream.close();

};

/// @brief Destructor
GrayImage::~GrayImage()
{

    if(imageMat != nullptr)
        delete[] imageMat;
    
};
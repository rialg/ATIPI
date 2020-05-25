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
 * brief Constructor
 * @param [in] width - ancho de la imagen
 * @param [in] height - alto de la imagen
*/
GrayImage::GrayImage(int width, int height):
width{width}, 
height{height}, 
imageMat{new uint8_t[width*height]}
{
    /// Crear imagen oscura
    for( int i = 0; i < width*height; ++i )
        imageMat[i] = 0;

};

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
    getline(oImageStream, line); /// < Tomar bytes de la imagen
    
    int row = 0, col = 0;
    for(char c : line)
    {
     
        imageMat[row*width+col] = (uint8_t) c;
        col++;

        if ( col % height == 0 )
        {
            col = 0;
            row++;
        }
        if(row >= width)
            break;

    }
    
    oImageStream.close();

};

/**
 * @brief Método para guardar imageMat en un archivo PGM
 * @param [in] fileName - nombre del archivo donde se guarda la imagen
*/
void GrayImage::save(const char* fileName)
{

    /// Abrir el archivo
    fstream fOut(fileName, ios::out | ios::app | ios::binary);

    fOut << "P5" << endl;
    fOut << width << " " << height << endl;
    fOut << "255" << endl;

    for( int row=0; row < width; ++row)
    {
        for( int col=0; col < height; ++col)
        {

            fOut << (char) imageMat[row*width+col];

        }

    }
    fOut.close();

};

/// @brief Destructor
GrayImage::~GrayImage()
{

    if(imageMat != nullptr)
        delete[] imageMat;
    
};
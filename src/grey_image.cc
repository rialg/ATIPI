/** @file gray_image.cc
 * Implementación de la clase GreyImage
 * Parseo de imagenes en formato PGM a un
 * objeto GreyImage
 * @see http://netpbm.sourceforge.net/doc/pgm.html
 */

#include "grey_image.h"

/// @brief Constructor por defecto
GreyImage::GreyImage(){};

/**
 * brief Constructor
 * @param [in] width - ancho de la imagen
 * @param [in] height - alto de la imagen
*/
GreyImage::GreyImage(int width, int height):
width{width}, 
height{height}, 
imageMat{new uint8_t[width*height]}
{
    /// Crear imagen oscura
    for( int i = 0; i < width*height; ++i )
        imageMat[i] = 0;

};

/// @brief Copy Constructor
GreyImage::GreyImage(const GreyImage& oImg):
width{oImg.getWidth()}, 
height{oImg.getHeight()}, 
imageMat{new uint8_t[oImg.getWidth()*oImg.getHeight()]}
{

    for( int i = 0; i < width*height; ++i )
        imageMat[i] = oImg[i];

};

/// @brief Copy Assigment
GreyImage& GreyImage::operator=(const GreyImage& oImg)
{

    if(&oImg == this)
        return *this;

    for( int i = 0; i < width*height; ++i )
        this->imageMat[i] = oImg[i];

    return *this;

};

/**
 * @brief Constructor
 * @param [in] imageFile - ruta al archivo de la imagen
*/ 
GreyImage::GreyImage(const char* imageFile)
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
     
        imageMat[row*height+col] = (uint8_t) c;
        col++;

        if ( col % width == 0 )
        {
            col = 0;
            row++;
        }
        if(row >= height)
            break;

    }
    
    oImageStream.close();

};

/**
 * @brief Método para guardar imageMat en un archivo PGM
 * @param [in] fileName - nombre del archivo donde se guarda la imagen
*/
void GreyImage::save(const char* fileName)
{

    /// Abrir el archivo
    fstream fOut(fileName, ios::out | ios::app | ios::binary);

    fOut << "P5" << endl;
    fOut << width << " " << height << endl;
    fOut << "255" << endl;

    for( int row=0; row < height; ++row)
    {
        for( int col=0; col < width; ++col)
        {

            fOut << (char) imageMat[row*height+col];

        }

    }
    fOut.close();

};

/// @brief Destructor
GreyImage::~GreyImage()
{

    if(imageMat != nullptr)
        delete[] imageMat;
    
};
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
 * @param width [in] - ancho de la imagen
 * @param height [in] - alto de la imagen
*/
GreyImage::GreyImage(int height, int width):
height{height},
width{width}, 
imageMat{new int16_t[width*height]}
{
    /// Crear imagen oscura
    for( int i = 0; i < width*height; ++i )
        imageMat[i] = 0;

};

/// @brief Copy Constructor
GreyImage::GreyImage(const GreyImage& oImg):
width{oImg.getWidth()}, 
height{oImg.getHeight()}, 
imageMat{new int16_t[oImg.getWidth()*oImg.getHeight()]}
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
 * @param imageFile [in] - ruta al archivo de la imagen
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
    imageMat = new int16_t[width*height];
    
    getline(oImageStream, line); /// < Descartar max_val

    /// < Leer datos byte a byte
    char c = oImageStream.get();
    int row = 0, col = 0;
    while( !oImageStream.eof() )
    {

        imageMat[ row * (height - (height-width)) + col ] = (int16_t) c;
        col++;

        if ( col % width == 0 )
        {
            col = 0;
            row++;
        }
        if(row >= height)
            break;

        oImageStream.get(c);
    }
    
    oImageStream.close();

};

/**
 * @brief Método para guardar imageMat en un archivo PGM
 * @param fileName [in] - nombre del archivo donde se guarda la imagen
*/
void GreyImage::save(const char* fileName) const
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

            fOut << (char) imageMat[ row * (height - (height-width)) + col ];

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

/**
 * @brief Operador de adición
 * @param oDer [in] - Operando derecho
 * @returns Imagen actualizada
*/
GreyImage& GreyImage::operator+=( const GreyImage& oDer )
{

    /// Check dimensions
    if( this->getHeight() != oDer.getHeight() ||
        this->getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    for(int row = 0; row < this->getHeight(); ++row )
        for(int col = 0; col < this->getWidth(); ++col )
            (*this)(row, col) += oDer(row, col);

    return *this;

}

/** @brief Operador de substracción
 * @param oDer [in] - Operando derecho
 * @returns Imagen actualizada
*/
GreyImage& GreyImage::operator-=(const GreyImage& oDer)
{

    /// Check dimensions
    if( this->getHeight() != oDer.getHeight() ||
        this->getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    for(int row = 0; row < this->getHeight(); ++row )
        for(int col = 0; col < this->getWidth(); ++col )
            (*this)(row, col) -= oDer(row, col);

    return *this;

}

/** 
 * @brief Operador de adición
 * @param oIzq [in] - Operando derecho 
 * @param oDer [in] - Operando derecho
 * @returns Resultado de la suma
*/
GreyImage& operator+(const GreyImage& oIzq, const GreyImage& oDer)
{

    /// Check dimensions
    if( oIzq.getHeight() != oDer.getHeight() ||
        oIzq.getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    GreyImage* oRet = new GreyImage(oIzq.getHeight(), oIzq.getWidth());

    for(int row = 0; row < oIzq.getHeight(); ++row )
        for(int col = 0; col < oIzq.getWidth(); ++col )
            (*oRet)(row, col) = oIzq(row, col) + oDer(row, col);

    return *oRet;

}

/** 
 * @brief Operador de substracción
 * @param oIzq [in] - Operando derecho 
 * @param oDer [in] - Operando derecho
 * @returns Resultado de la resta
*/
GreyImage& operator-(const GreyImage& oIzq, const GreyImage& oDer)
{

    /// @brief Check dimensions
    if( oIzq.getHeight() != oDer.getHeight() ||
        oIzq.getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    GreyImage* oRet = new GreyImage(oIzq.getHeight(), oIzq.getWidth());

    for(int row = 0; row < oIzq.getHeight(); ++row )
        for(int col = 0; col < oIzq.getWidth(); ++col )
            (*oRet)(row, col) = oIzq(row, col) - oDer(row, col);

    return *oRet;

}

/** @file colour_image.h
 * Interfaz de la clase ColourImage
 * Parseo de imagenes en formato PPM a tres
 * objetos de tipo GreyImage (ColourImage)
 * @see http://netpbm.sourceforge.net/doc/pgm.html
 */
#include "colour_image.h"

/// @brief Constructor por defecto
ColourImage::ColourImage(){};

/**
 * brief Constructor
 * @param width [in] - ancho de la imagen
 * @param height [in] - alto de la imagen
*/
ColourImage::ColourImage(int height, int width):
oRed{new GreyImage(height, width)},
oGreen{new GreyImage(height, width)},
oBlue{new GreyImage(height, width)}
{};

/// @brief Copy Constructor
ColourImage::ColourImage(const ColourImage& oImg):
oRed{new GreyImage(oImg.getRedImage())},
oGreen{new GreyImage(oImg.getGreenImage())},
oBlue{new GreyImage(oImg.getBlueImage())}
{};

/// @brief Copy Assigment
ColourImage& ColourImage::operator=(const ColourImage& oImg)
{

    if(&oImg == this)
        return *this;

    this->oRed = new GreyImage(oImg.getRedImage());
    this->oGreen = new GreyImage(oImg.getGreenImage());
    this->oBlue = new GreyImage(oImg.getBlueImage());

    return *this;

};

/**
 * @brief Constructor
 * @param imageFile [in] - ruta al archivo de la imagen
*/ 
ColourImage::ColourImage(const char* imageFile)
{

    /**
     * Parsear el contenido de los archivos PGM
    */
    ifstream oImageStream(imageFile, ios::binary);
    string line;
    
    /// Validar el formato del archivo
    getline(oImageStream, line);
    if( line.find( "P6" ) == string::npos )
        throw InvalidImageFormatException();
    
    /// Tomar dimensiones
    getline(oImageStream, line);
    while( line[0] == '#' )             /// Descartar comentarios
        getline(oImageStream, line);    /// Descartar comentarios
    int width = stoi(line.substr(0, line.find(" ")));
    int height = stoi(line.substr(line.find(" "), line.length() ));
    
    /// Crear imagenes de tono de gris
    oRed = new GreyImage(height, width);
    oGreen = new GreyImage(height, width);
    oBlue = new GreyImage(height, width);

    getline(oImageStream, line); /// < Descartar max_val
    while( line[0] == '#' )             /// Descartar comentarios
        getline(oImageStream, line);    /// Descartar comentarios
    /// < Leer datos byte a byte
    char c = oImageStream.get();
    int row = 0, col = 0, colour = 0;
    while( !oImageStream.eof() )
    {

        switch(colour)
        {
            case RED: /// READ 
                this->getRedPixel(row, col) = (int16_t) c;
                break;
            case GREEN:
                this->getGreenPixel(row, col) = (int16_t) c;
                break;
            case BLUE:
                this->getBluePixel(row, col) = (int16_t) c;
                break;
        }
        colour++;

        if ( colour % 3 == 0 ) /// R,G,B
        {
            colour=0;
            col++;
            if ( col % width == 0 )
            {
                col = 0;
                row++;
            }
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
void ColourImage::save(const char* fileName) const
{

    /// Abrir el archivo
    fstream fOut(fileName, ios::out | ios::app | ios::binary);

    fOut << "P6" << endl;
    fOut << this->getWidth() << " " << this->getHeight() << endl;
    fOut << "255" << endl;

    for( int row=0; row < this->getHeight(); ++row)
    {
        for( int col=0; col < this->getWidth(); ++col)
        {

            for( int colour = 0; colour < 3; colour++ )
            {
                switch(colour)
                {
                    case RED: /// READ 
                        fOut << (char) this->getRedImage()(row ,col);
                        break;
                    case GREEN:
                        fOut << (char) this->getGreenImage()(row ,col);
                        break;
                    case BLUE:
                        fOut << (char) this->getBlueImage()(row ,col);
                        break;
                }
            }

        }

    }
    fOut.close();

};

/// @brief Destructor
ColourImage::~ColourImage()
{

    if(oRed != nullptr)
        delete oRed;
    if(oGreen != nullptr)
        delete oGreen;
    if(oBlue != nullptr)
        delete oBlue;

};

/**
 * @brief Operador de adición
 * @param oDer [in] - Operando derecho
 * @returns Imagen actualizada
*/
ColourImage& ColourImage::operator+=( const ColourImage& oDer )
{

    /// Check dimensions
    if( this->getHeight() != oDer.getHeight() ||
        this->getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    this->getRedImage() += oDer.getRedImage();
    this->getGreenImage() += oDer.getGreenImage();
    this->getBlueImage() += oDer.getBlueImage();

    return *this;

}

/** @brief Operador de substracción
 * @param oDer [in] - Operando derecho
 * @returns Imagen actualizada
*/
ColourImage& ColourImage::operator-=(const ColourImage& oDer)
{

    /// Check dimensions
    if( this->getHeight() != oDer.getHeight() ||
        this->getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    this->getRedImage() -= oDer.getRedImage();
    this->getGreenImage() -= oDer.getGreenImage();
    this->getBlueImage() -= oDer.getBlueImage();

    return *this;

}

/** 
 * @brief Operador de adición
 * @param oIzq [in] - Operando derecho 
 * @param oDer [in] - Operando derecho
 * @returns Resultado de la suma
*/
ColourImage& operator+(const ColourImage& oIzq, const ColourImage& oDer)
{

    /// Check dimensions
    if( oIzq.getHeight() != oDer.getHeight() ||
        oIzq.getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    ColourImage* oRet = new ColourImage(oIzq.getHeight(), oIzq.getWidth());

    oRet->getRedImage() = oIzq.getRedImage() + oDer.getRedImage();
    oRet->getGreenImage() = oIzq.getGreenImage() + oDer.getGreenImage();
    oRet->getBlueImage() = oIzq.getBlueImage() + oDer.getBlueImage();

    return *oRet;

}

/** 
 * @brief Operador de substracción
 * @param oIzq [in] - Operando derecho 
 * @param oDer [in] - Operando derecho
 * @returns Resultado de la resta
*/
ColourImage& operator-(const ColourImage& oIzq, const ColourImage& oDer)
{

    /// Check dimensions
    if( oIzq.getHeight() != oDer.getHeight() ||
        oIzq.getWidth() != oDer.getWidth() )
        throw new InvalidDimensionsException();

    ColourImage* oRet = new ColourImage(oIzq.getHeight(), oIzq.getWidth());

    oRet->getRedImage() = oIzq.getRedImage() - oDer.getRedImage();
    oRet->getGreenImage() = oIzq.getGreenImage() - oDer.getGreenImage();
    oRet->getBlueImage() = oIzq.getBlueImage() - oDer.getBlueImage();

    return *oRet;

}
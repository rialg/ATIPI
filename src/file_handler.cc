#include "file_handler.h"

/**
 * @brief funcion que escribe bytes en archivo comprimido
 * @param oImage [in] GreyImage - imagen a comprimir
 * @param filename [in] string - nombre de archivo
 * @param type [in] string - tipo P5 o P6
 * @param width [in] int - image width
 * @param height [in] int - image height
 * @param N [in] int - context size
 * @param oRGB [in] Colour - color a comprimir (aplica solamente a las imagenes a color)
*/
void compress(const GreyImage& oImage, const string& filename, const string& type, int width, int height,  size_t N, Colour oRGB)
{

    /// 0. Abrir archivo a escribir
    ofstream pgmFile;

    if( type.find( "P5" ) != string::npos || oRGB == RED )
    {

        pgmFile.open(filename + ".loco");
        pgmFile << type << endl;
        pgmFile << width << " " << height << endl;
        pgmFile << N << endl;

    }
    else
        pgmFile.open(filename + ".loco", std::ios_base::app);

    /// 1. Apply MED
    GreyImage oPrediction = fixed_prediction(oImage);

    /// 2. Find prediction error
    GreyImage oError = oImage - oPrediction;

    /// 3. Find Rice mapping
    GreyImage oRiceMap = RiceMapping(oError);

    /// 4. Calculate context table for a given N size
    ContextTable oTable{ getLocalContext( N, oImage.getWidth(), oImage.getHeight()) };

    /// 5. Calculate the compressed image code
    string buffer{""};
    for(int row = 0; row < oImage.getHeight() ; ++row)
        for(int col = 0; col < oImage.getWidth() ; ++col)
        {
            int m = getCodeOrder(PixelPos{row, col} , oTable, oError);
            div_t result = div(oRiceMap(row, col), m);
            string codification = "";

            /// bin(rice mod m)
            if( m > 1 )
            {

                int exp = result.rem > 0 ? floor(log2((double) result.rem)) : 0;
                int rem = result.rem > 0 ? result.rem - (1 << exp) : 0;
                codification = result.rem > 0 ? "1" : "0";

                for(int i = 0; i < exp; ++i )
                    codification += "0";

                while(rem > 0)
                {

                    exp = floor(log2((double) rem));
                    rem -= 1 << exp;
                    codification[codification.length() - 1 - exp] = '1';

                }
                int pending = ceil(log2((double) m)) - codification.length();
                for(int j=0; j < pending; j++)
                    codification = "0"+codification;

            }

            /// uni(rice div m)
            for(int i=0; i<result.quot; i++){
                codification += "0";
            }
            codification += "1";

            buffer += codification;
            codification.clear();

            /// Ver si agregar o no bytes al archivo
            if( buffer.length() > 7 )
            {
                int i = 0;
                for(; i < buffer.length()/8; ++i)
                {

                    string sByte{buffer.begin()+(8*i),buffer.begin()+8*(1+i)};
                    bitset<8> byte_char(sByte);
                    char final_char = static_cast<char>( byte_char.to_ulong());
                    pgmFile << final_char;

                }

                buffer = string{buffer.begin()+(8*i), buffer.end()};

            }

        }
    //final bits that need padding
    if(!buffer.empty())
    {
        while(buffer.length() % 8 != 0)
            buffer += "0";

        for(int i=0; i < buffer.length()/8; ++i)
        {

            string sByte{buffer.begin()+(8*i),buffer.begin()+8*(1+i)};
            bitset<8> byte_char(sByte);
            char final_char = static_cast<char>( byte_char.to_ulong());
            pgmFile << final_char;

        }
        buffer.clear();

    }
    pgmFile.close();

}

/**
 * @brief funcion que escribe bytes en archivo
 * @param [in] string - nombre de archivo
 * @param [in] string - tipo P5 o P6
 * @param [in] int - image width
 * @param [in] int - image height
 * @param [in] int - n context size
 * @param [in] vector<bool> - bits a escribir
 * @returns errores
*/
void copy_to_file(string filename, string type, int width, int height,  int n, vector<bool> bits){
    ofstream pgmFile;
    pgmFile.open (filename + ".loco");
    pgmFile << type << endl << width << " " << height << endl << n << endl; // first lines
    
    string c;
    for (int i=0; i < bits.size(); i+=8){
        c = "";
        if (i+8 <= bits.size()){
            vector<bool> byte(bits.begin() + i, bits.begin() + i + 8);

            for (int j=0; j<8; j++){
                c.append(byte[j] ? "1" : "0") ;
            }
            bitset<8> byte_char(c);
            char final_char = static_cast<char>( byte_char.to_ulong());
            pgmFile << final_char;

        }else{                                                     //final bits that need padding
            vector<bool> byte(bits.begin() + i, bits.end());
            int missing_bits = 8 - bits.size()%8;

            for (int j=0; j<8-missing_bits; j++){
                c.append(byte[j] ? "1" : "0") ;
            }
            string missing = std::string(missing_bits, '0');
            bitset<8> byte_char(c + missing);
            char final_char = static_cast<char>( byte_char.to_ulong());
            pgmFile << final_char;
        }
    }

    pgmFile.close();

}

/**
 * @brief   Leer el stream de bytes del archivo comprimido
 *          y devolver el código (y metadatos) en una tupla
 * @param filePath [in] - Ruta (absoluta) al fichero comprimido
 * @returns tupla con código y metadatos
*/
const compressData& read_compressed(const char* filePath)
{

    string* code = new string();

    /// Read file
    ifstream oCompressedImage(filePath, ios::binary);

    /// Get decompressed image file size
    string line;
    getline(oCompressedImage, line);

    if( line.compare("P5") != 0 && line.compare("P6") != 0 ) /// Check format
        throw InvalidImageFormatException();

    line.clear();
    getline(oCompressedImage, line);
    int width = stoi(line.substr(0, line.find(" "))); // => To uncomment latter
    int height = stoi(line.substr(line.find(" "), line.length() )); // => To uncomment latter

    line.clear();
    getline(oCompressedImage, line);
    int N = stoi(line.substr(0, line.find(" ")));

    char c = oCompressedImage.get();
    while( !oCompressedImage.eof() )
    {

        for( int i = 7; i >= 0; --i )
            (*code) += string{ (c & ( 1 << i )) ? "1" : "0" };

        oCompressedImage.get(c);
    }

    compressData* oCompressData = new compressData(*code, height, width, N);
    return *oCompressData;

}

/**
 * @brief   Leer el stream de bytes del archivo comprimido
 *          y escribir imagen descomprimida
 * @param filePath [in] - Ruta (absoluta) al fichero comprimido
*/
void decompress_from_file(const char* filePath)
{

    string filename{fs::path(filePath).stem().string()};
    string code("");

    /// Read file
    ifstream oCompressedImage(filePath, ios::binary);

    /// Get decompressed image file size
    string line;
    getline(oCompressedImage, line);

    string sType = line; /// < Tipo de imagen
    if( sType.compare("P5") != 0 && sType.compare("P6") != 0 ) /// Check format
        throw InvalidImageFormatException();

    line.clear();
    getline(oCompressedImage, line);
    int width = stoi(line.substr(0, line.find(" "))); // => To uncomment latter
    int height = stoi(line.substr(line.find(" "), line.length() )); // => To uncomment latter

    line.clear();
    getline(oCompressedImage, line);
    int N = stoi(line.substr(0, line.find(" ")));

    /// Obtener los contextos locales
    ContextTable oTable{getLocalContext(N, width, height)};

    /// Empezar el proceso de descompresión del rojo
    string buffer = "";
    state oState(true, true, 0, 0, 0, 0, 0, 0);

    GreyImage   oErrorTemp{height, width},      /// < Error de predicción
                oPred{height, width},           /// < Predicción MED
                oDecompressedRed{height, width};   /// < Imagen descomprimida

    char c = oCompressedImage.get();
    while( !oCompressedImage.eof() && get<2>(oState) < height && get<3>(oState) < width )
    {

        for( int i = 7; i >= 0; --i )
            code += string{ (c & ( 1 << i )) ? "1" : "0" };

        stateless_decompress( code, oTable, height, width, N, oErrorTemp, oPred, oState, buffer, oDecompressedRed);
        code.clear();

        oCompressedImage.get(c);
    }

    ///@brief escribir imagen si es de tono de gris
    if( sType.compare("P5") == 0 )
    {

        oDecompressedRed.save(strcat( const_cast<char*>(filename.c_str()), ".pgm") );
        oCompressedImage.close();
        return;

    }

    /// Empezar el proceso de descompresión del verde
    oState = state(true, true, 0, 0, 0, 0, 0, 0);

    oErrorTemp = GreyImage{height, width},      /// < Error de predicción
    oPred = GreyImage{height, width};           /// < Predicción MED
    GreyImage oDecompressedGreen{height, width};/// < Imagen descomprimida

    while( !oCompressedImage.eof() && get<2>(oState) < height && get<3>(oState) < width )
    {

        for( int i = 7; i >= 0; --i )
            code += string{ (c & ( 1 << i )) ? "1" : "0" };

        stateless_decompress( code, oTable, height, width, N, oErrorTemp, oPred, oState, buffer, oDecompressedGreen);
        code.clear();

        oCompressedImage.get(c);
    }

    /// Empezar el proceso de descompresión del azul
    oState = state(true, true, 0, 0, 0, 0, 0, 0);

    oErrorTemp = GreyImage{height, width},      /// < Error de predicción
    oPred = GreyImage{height, width};           /// < Predicción MED
    GreyImage oDecompressedBlue{height, width}; /// < Imagen descomprimida

    while( !oCompressedImage.eof() && get<2>(oState) < height && get<3>(oState) < width )
    {

        for( int i = 7; i >= 0; --i )
            code += string{ (c & ( 1 << i )) ? "1" : "0" };

        stateless_decompress( code, oTable, height, width, N, oErrorTemp, oPred, oState, buffer, oDecompressedBlue);
        code.clear();

        oCompressedImage.get(c);
    }

    /// Descomprimir imagen a color
    ColourImage oDecompressed(oDecompressedRed, oDecompressedGreen, oDecompressedBlue);
    oDecompressed.save( strcat( const_cast<char*>(filename.c_str()), ".ppm") );
    oCompressedImage.close();

    return;

}
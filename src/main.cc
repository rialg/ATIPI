/** @file main.cc
 * Pruebas con el predictor MED
 */

#include <string>
#include <iostream>
#include <filesystem>
#include "grey_image.h"
#include "med_predictor.h"
#include "error_calculator.h"
#include "context_sign_matrix.h"
#include "local_context.h"
#include "golomb_encoder.h"
#include "decompressor.h"
#include "file_handler.h"

/// Usar namespace de la biblioteca estándar
using namespace std;
namespace fs = std::__fs::filesystem;

static int** initialize_errors_matrix(int height, int width){
    int** errors = new int*[height];
    for (int h = 0; h < height; h++){
            errors[h] = new int[width];
            for (int w = 0; w < width; w++){
                  // fill in some initial values
                  errors[h][w] = 0;
            }
      }
      return errors;
}

static inline const vector<bool>& transformData( const string& code )
{

    // Test
    vector<char> cBits(code.begin(), code.end());
    vector<bool>* bBits = new vector<bool>();
    for(const char& c: cBits)
        bBits->push_back( c == '1');

    return *bBits;

}

int main(int argc, char* argv[])
{
    
    if(argc < 3)
    {

        cout << "USAGE: Compressor <image-path> <N> | -d <compressed-image-path>" << endl;
        exit(-1);

    }

    if( strncmp( argv[1], "-d", strlen("-d")) != 0 )
    {

        /// Comprimir archivo
        cout << "Comprimiendo "<< argv[1] << endl;
        GreyImage oImg( argv[1] );

        string compressCode{golombEncoding(oImg, atoi(argv[2]))};
        string filename{fs::path(argv[1]).stem().string()};
        copy_to_file( filename.c_str(), "P5", oImg.getWidth(), oImg.getHeight(), atoi(argv[2]), transformData(compressCode));

    } else {

        /// Descomprimir archivo
        cout << "Descomprimiendo "<< argv[2] << endl;
        compressData oCompressData{ read_compressed(argv[2]) };
        GreyImage oDecompress = decompress( get<0>(oCompressData), get<1>(oCompressData), get<2>(oCompressData), get<3>(oCompressData));

        string filename{fs::path(argv[2]).stem().string()};
        oDecompress.save(strcat( const_cast<char*>(filename.c_str()), ".pgm") );

    }
    cout << "Operación terminada " << endl;

    exit(0);
}
#include "file_handler.h"

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
    pgmFile.open (filename + ".pgm");
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
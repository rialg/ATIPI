/** @file file_writer.h
 * Metodos para gestionar archivos
 */
#ifndef ATIPI_INCLUDE_FILE_HANDLER_H_
#define ATIPI_INCLUDE_FILE_HANDLER_H_

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <bitset>
#include <tuple>
#include <experimental/filesystem>
#include "grey_image.h"
#include "colour_image.h"
#include "med_predictor.h"
#include "golomb_encoder.h"
#include "decompressor.h"

using namespace std;
namespace fs = std::experimental::filesystem;

/// @brief Alias de tipo
/// tupla con: código, alto, ancho y tamaño del contexto (N)
using compressData = tuple<string,int, int, int>;

/**
 * @brief funcion que escribe bytes en archivo 
 * @param [in] string - nombre de archivo
 * @param [in] string - tipo P5 o P6
 * @param [in] int - image width
 * @param [in] int - image height
 * @param [in] int - n context size
 * @param [in] vector<bool> - bits a escribir
 * @returns 0
*/
void copy_to_file(string filename, string type, int width, int height, int n, vector<bool> bits);

/**
 * @brief   Leer el stream de bytes del archivo comprimido
 *          y devolver el código (y metadatos) en una tupla
 * @param filePath [in] - Ruta (absoluta) al fichero comprimido
 * @returns tupla con código y metadatos
*/
const compressData& read_compressed(const char* filePath);

/**
 * @brief funcion que escribe bytes en archivo comprimido
 * @param oImage [in] GreyImage - imagen a comprimir
 * @param filename [in] string - nombre de archivo
 * @param type [in] string - tipo P5 o P6
 * @param width [in] int - image width
 * @param height [in] int - image height
 * @param N [in] int - context size
 * @param oRGB [in] Colour - color a comprimir (aplica solamente a las imagenes a color)
 * @param transform [in] Se transforman los planos de color
*/
void compress(const GreyImage& oImage, const string& filename, const string& type, int width, int height,  size_t N, Colour oRGB, bool transform);

/**
 * @brief   Leer el stream de bytes del archivo comprimido
 *          y escribir imagen descomprimida
 * @param filePath [in] - Ruta (absoluta) al fichero comprimido
*/
void decompress_from_file(const char* filePath);

#endif /// < ATIPI_INCLUDE_FILE_HANDLER_H_
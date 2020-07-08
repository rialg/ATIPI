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
#include "grey_image.h"

using namespace std;

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
 * @brief   Leer el stream de bytes del archivo comprimido y
 *          y devolver el código (y metadatos) en una tupla
 * @param filePath [in] - Ruta (absoluta) al fichero comprimido
 * @returns tupla con código y metadatos
*/
const compressData& read_compressed(const char* filePath);

#endif /// < ATIPI_INCLUDE_FILE_HANDLER_H_
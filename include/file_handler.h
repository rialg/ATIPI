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

using namespace std;

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

#endif /// < ATIPI_INCLUDE_FILE_HANDLER_H_
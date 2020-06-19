/** @file local_context.h
 * Determinación del contexto local para 
 * hallar los estadísticos A (suma de valores
 * absolutos de los errores) y n (cantidad de 
 * muestras).
 */
#ifndef ATIPI_INCLUDE_LOCAL_CONTEXT_H_
#define ATIPI_INCLUDE_LOCAL_CONTEXT_H_

#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>

using namespace std;

/**
 * @typedef PixelPos
 * @brief   Coordenadas sobre la posición de un pixel
*/
using PixelPos = pair<int, int>;

/// @brief funcion de hash especializada
namespace std
{
    template<> struct hash<PixelPos>
    {
        std::size_t operator()(PixelPos const& pixel) const noexcept
        {
            return pixel.second * 512 + pixel.first; // col * width + row
        }
    };
};

/**
 * @typedef ContextTableBase
 * @brief Alias para especialización del contenedor del contexto local
*/
using ContextTableBase = unordered_map< PixelPos, vector<PixelPos> >;

/**
 * @typedef ContextMask
 * @brief   Mascara para hallar pixeles del contexto
*/
using ContextMask = vector<PixelPos>;

/**
 * @class InvalidPixelPositionException
 * @brief   Excepción usada para controlar el acceso a la 
 *          tabla de contextos locales
*/
class InvalidPixelPositionException : public exception
{

    /**
     * @brief Explicación del error
     * @returns Texto explicativo
    */
    public:
        const char* what() const throw ()
        {
        
            return "Invalid pixel position.";
    
        };

};

/**
 * @class ContextTable
 * @brief   Tabla con pares de desplazamientos para cada pixel de la imagen
 *           Obs.: Un pixel es igual a pair<uint_8, uint_8>
*/
class ContextTable : public ContextTableBase
{

    public:
        ContextTable();
        ~ContextTable();
        /**
          * @brief   Sobrecarga del operador
        */
        vector<PixelPos>& operator[]( const PixelPos& oPixel ){
            if( this->find(oPixel) == this->end() )
                throw new InvalidPixelPositionException();
            else
                return ContextTableBase::operator[]( oPixel );
        };

};

/**
 * @brief Función que calcula la tabla de contextos
 * @param [in] N - Tamaño del contexto
 * @param [in] width - Cantidad de columnas de pixeles de la imagen
 * @param [in] height - Cantidad de filas de pixeles de la imagen
 * @returns ContextTable, o tabla con pares de desplazamientos
*/
const ContextTable& getLocalContext(const int N, const int width, const int height);

#endif /// < ATIPI_INCLUDE_LOCAL_CONTEXT_H_
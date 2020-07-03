/** @file local_context.cc
 * Determinación del contexto local para 
 * hallar los estadísticos A (suma de valores
 * absolutos de los errores) y n (cantidad de 
 * muestras).
 */

#include "local_context.h"

/// @brief Class constructor
ContextTable::ContextTable()
{};

/// @brief Class destructor
ContextTable::~ContextTable()
{};

/**
 * @brief Función local que determina la mascara de los pixeles que pertenecen al contexto
 * @param [in] N - Tamaño del contexto
 * @returns oMask, lista de pixeles en la mascara del contexto local
*/
static ContextMask& createPixelMask(const size_t N)
{

    bool find_all = false;
    int distance = 0, total_found = 0;
    ContextMask* oMask = new ContextMask();
    do
    {

        distance++;
        int found = 0;
        int secDistance = 0;

        while ( secDistance <= distance && total_found+found < N )
        {

            if( distance > secDistance && total_found+found < N )
            {
                oMask->push_back(PixelPos{ 0 - secDistance, 0 - distance });
                found++;
            }
            if( total_found+found < N )
            {
                oMask->push_back(PixelPos{ 0 - distance, 0 - secDistance });
                found++;
            }
            if( secDistance > 0 && total_found+found < N )
            {
                oMask->push_back(PixelPos{ 0 - distance, 0 + secDistance });
                found++;
            }

        secDistance++; 
        }

        total_found += found;
        if(total_found == N || found == 0)
            find_all = true;

    } while(!find_all);
    return *oMask;

}

/**
 * @brief Función local para aplicar la mascara del contexto local a cada uno de los pixeles
 * @param [in] oPosition - Ubicación del pixel (x)
 * @param [in] oMask - Mascara del contexto
 * @param [in] width - Cantidad de columnas de pixeles de la imagen
 * @param [in] height - Cantidad de filas de pixeles de la imagen
 * @returns oRet, lista de pixeles en el contexto local de oPosition
*/
static vector<PixelPos>& applyMask(const PixelPos& oPosition, const ContextMask& oMask, const int width, const int height)
{

    vector<PixelPos>* oRet = new vector<PixelPos>();
    /// Tomar cada pixel de la mascara
    for(const auto& dot : oMask )
    {

        PixelPos oCandidate{ oPosition.first + dot.first, oPosition.second + dot.second };
        if( oCandidate.first >= 0       &&
            oCandidate.first < height   &&
            oCandidate.second >=0       &&
            oCandidate.second < width   )
            oRet->push_back(oCandidate);
        else
            continue;

    }
    return *oRet;

}

/**
 * @brief Función que calcula la tabla de contextos
 * @param [in] N - Tamaño del contexto
 * @param [in] width - Cantidad de columnas de pixeles de la imagen
 * @param [in] height - Cantidad de filas de pixeles de la imagen
 * @returns oTable, o tabla con pares de desplazamientos
*/
const ContextTable& getLocalContext(const size_t N, const int width, const int height)
{

    ContextTable* oTable = new ContextTable();
    ContextMask oMask{ createPixelMask(N) };

    for(int row = 0; row < width; ++row)
    {
        for(int col = 0; col < height; ++col)
        {

            bool find_all = false;
            int distance = 0, total_found = 0;
            PixelPos oPosition{ row, col };
            if( oTable->find(oPosition) == oTable->end() )
                oTable->insert({ oPosition, applyMask(oPosition, oMask, width, height) });

        }
    }
    
    return (*oTable);

}
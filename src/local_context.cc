/** @file local_context.cc
 * Determinación del contexto local para 
 * hallar los estadísticos A (suma de valores
 * absolutos de los errores) y n (cantidad de 
 * muestras).
 */

#include "local_context.h"

using namespace std;
/**
 * @brief Función local halla la lista de pixeles más cercanos a cierta distancia
 * @param [in] oPosition - Ubicación del pixel (x)
 * @param [in] distance - Distancia de los vecinos
 * @param [in] total_found - Cantidad de vecinos encontrados hasta el momento
 * @param [in] N - tamaño del contexto
 * @param [out] found - Cantidad de pixeles vecinos nuevos encontrados 
 * @returns oClosests, lista de pixeles a una distancia "distance"
*/
static vector<PixelPos>& find_closests( const PixelPos& oPosition, const int distance, const  int total_found, const int N, const int width, int& found)
{

    vector<PixelPos>* oRet = new vector<PixelPos>();
    
    int secDistance = 0;
    while ( secDistance <= distance && total_found+found < N )
    {

        if( oPosition.first - distance >= 0 && oPosition.second - secDistance >= 0 && total_found+found < N )
        {
            oRet->push_back(PixelPos{ oPosition.first - distance, oPosition.second - secDistance });
            found++;
        }
        if( distance > secDistance && oPosition.first - secDistance >= 0 && oPosition.second - distance >= 0 && total_found+found < N )
        {
            oRet->push_back(PixelPos{ oPosition.first - secDistance, oPosition.second - distance });
            found++;
        }
        if( secDistance > 0 && oPosition.first - distance >= 0 && oPosition.second + secDistance < width && total_found+found < N )
        {
            oRet->push_back(PixelPos{ oPosition.first - distance, oPosition.second + secDistance });
            found++;
        }

        secDistance++; 
    }

    return *oRet;

}

/**
 * @brief Función que calcula la tabla de contextos
 * @param [in] N - Tamaño del contexto
 * @param [in] width - Cantidad de columnas de pixeles de la imagen
 * @param [in] height - Cantidad de filas de pixeles de la imagen
 * @returns ContextTable, o tabla con pares de desplazamientos
*/
const ContextTable& getLocalContext(const int N, const int width, const int height)
{

    ContextTable* oTable = new ContextTable();

    for(int row = 0; row < width; ++row)
    {
        for(int col = 0; col < height; ++col)
        {

            bool find_all = false;
            int distance = 0, total_found = 0;
            PixelPos oPosition{ row, col };
            (*oTable)[oPosition] = vector<PixelPos>();

            do
            {
                
                distance++;
                int found = 0;
                vector<PixelPos> oClosests{ find_closests(oPosition, distance, total_found, N, width, found) };
                (*oTable)[oPosition].insert((*oTable)[oPosition].begin(), oClosests.begin(), oClosests.end() );
                total_found += found;

                if(total_found == N || found == 0)
                    find_all = true;    

            } while(!find_all);

        }
    }
    
    return (*oTable);

}
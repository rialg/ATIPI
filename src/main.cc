/** @file main.cc
 * Pruebas con el predictor MED
 */

#include <string>
#include <iostream>
//#include <memory>
#include "gray_image.h"
#include "med_predictor.h"
#include "error_calculator.h"
#include "context_sign_matrix.h"

/// Usar namespace de la biblioteca estándar
using namespace std;

int** initialize_errors_matrix(int height, int width){
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

int main(int argc, char *argv[])
{
    GrayImage oIMG("test/Imagenes-LOCO-PGM+PPM/barbara.pgm");
    GrayImage oPrediction = fixed_prediction(oIMG);
    oPrediction.save("med.pgm");

    int** errors = initialize_errors_matrix(oIMG.getHeight(),oIMG.getWidth());
    calculate_errors(oIMG, oPrediction, errors);
    printf("error on (row,col) (15,15) %i", errors[15][15]);
    cout << "\ncontextMat height: " << sizeof(errors) << " and contextMat width: " << sizeof(errors[0]);


    ContextSignMatrix contexts(oIMG);
    cout << "\ncontext of (row,col) (15,15): " << contexts(15,15).q1 << "," << contexts(15,15).q2 << "," << contexts(15,15).q3;
    cout << "\ncontextMat width: " << contexts.getWidth() << " and contextMat height: " << contexts.getHeight();

    exit(0);
}


#include <vector>

typedef vector< tuple<int,int> > tuple_list;

tuple_list desplazamientos(int MAX_WIDTH, int MAX_HEIGHT, int N, int Xr, int Xc ){
      int max_distance = 0;
      tuple_list closest_cells;

      if (Xr == 0){           /* Si estamos en fila0*/
            max_distance = Xc;
      }else{
            max_distance = max(Xr + Xc, Xr + (MAX_WIDTH - Xc));
      }
      
      for (int dis=0; dis = max_distance; dis++){
            tuple_list cells;
            cells = cells_with_distance_i(MAX_WIDTH, MAX_HEIGHT, Xr, Xc, dis);
            int i=0;
            while ( i < cells.size()){
                  if (closest_cells.size() < N){
                  closest_cells.push_back(cells[i]);
                  }else{
                        break;
                  }
            }
            if (closest_cells.size() == N){
                  break;
            }
      }

      return closest_cells;
}

tuple_list cells_with_distance_i(int MAX_WIDTH, int MAX_HEIGHT, int Xr, int Xc, int distance){
      tuple_list cells;
      for(int col=0; col <= distance; col++) {
            if (col==0){
                if (Xr-distance >= 0) {         /* max upper pixel; TOP of pyramid */
                        cells.push_back(std::make_tuple(Xr-distance, Xc));
                }
            }else if(col==distance){            /* leftmost pixel */
                  if (Xc-distance >= 0){
                        cells.push_back(std::make_tuple(Xr, Xc-distance));
                  }
            }else {                             /* sides of pyramid pixels */
                  int new_absolute_col = distance-col; 
                  int row = distance - new_absolute_col;

                  /* left side */
                  if (Xc - new_absolute_col > 0){      /* No nos pasamos de la columna 0 */ 
                        if (Xr - row > 0){            /* No nos pasamos de la fila 0 */ 
                              cells.push_back(std::make_tuple(Xr-row, Xc-new_absolute_col));
                        }
                  }
                  /* right side */
                  if (Xc + new_absolute_col < MAX_WIDTH){      /* No nos pasamos de la columna MAX_WIDTH */ 
                        if (Xr - row > 0){            /* No nos pasamos de la fila 0 */ 
                              cells.push_back(std::make_tuple(Xr-row, Xc + new_absolute_col));
                        }
                  }
            }
      }
}
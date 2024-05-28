#include "convolution.h"

#include <stdlib.h>

#include "image.h"

void convolve(float *result, const float *img, int w, int h,
              const float *matrix, int w_m, int h_m) {
    

    if ( result == NULL || img == NULL || w==0 || h==0 ||
            matrix == NULL || w_m == 0 || h_m == 0 ){
                
        return;                                             // Error Handling
    }
    float matrix_val;
    int get_pixel_x_coordinate;
    int get_pixel_y_coordinate;

    int matrix_middle_coordinate_x = (w_m - 1)/2;  // Calculate 'a' given in Project description
    int matrix_middle_coordinate_y = (h_m - 1)/2;  // Calculate 'b' given in Project description


    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            float matrix_sum = 0;

            // Calculate the convolution value at (x,y) using matrix below

            for (int j = 0; j < h_m; j++)
            {   
                for (int i = 0; i < w_m; i++)
                {
                    matrix_val = matrix[(w_m*j) + i];

                    get_pixel_x_coordinate = x - matrix_middle_coordinate_x + i;  // x for P ( x , _) in description
                    get_pixel_y_coordinate = y - matrix_middle_coordinate_y + j;  // y for P ( _ , y) in description

                    matrix_sum += matrix_val * get_pixel_value(img , w , h , get_pixel_x_coordinate , get_pixel_y_coordinate);

                }
                
            }

            result[(w * y) + x] = matrix_sum;

        }
        
    }
    

    
}

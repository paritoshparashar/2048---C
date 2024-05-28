#include "derivation.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "convolution.h"
#include "image.h"

void gradient_magnitude(float *result, const float *d_x, const float *d_y, int w, int h) {

    if (d_x == NULL || d_y == NULL || w==0 || h==0 || result == NULL){
        return;                                             // Error Handling
    }

    int imgArrLength = w*h;

    for (int i = 0; i < imgArrLength; i++)
    {
        double sumOfSquare = pow(d_x[i],2) + pow(d_y[i],2);
        double gradient = sqrt(sumOfSquare);                //  Calculate the gradient from partial derivatives

        result[i] = (float)gradient;                               // Store the gradient in the output image
    }
    
}

const float sobel_x[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};

const float sobel_y[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

void derivation_x_direction(float *result, const float *img, int w, int h) {
    convolve(result, img, w, h, sobel_x, 3, 3);
}

void derivation_y_direction(float *result, const float *img, int w, int h) {
    convolve(result, img, w, h, sobel_y, 3, 3);
}

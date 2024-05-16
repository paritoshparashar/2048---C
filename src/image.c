#include "image.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void apply_threshold(float *img, int w, int h, int T) {

    if (img == NULL || w==0 || h==0){
        return;                         // Error Handling
    }

    int imgArrLength = w*h;

    for (int i = 0; i < (imgArrLength); i++)
    {
        if (img[i] <= T)
        {
            img[i] = 0;                 // Color Black;
        }
        else 
        {
            img[i] = 255;               // Color White
        }
    }

}


void scale_image(float *result, const float *img, int w, int h) {
    
    if (img == NULL || w==0 || h==0 || result == NULL){
        return;                         // Error Handling
    }

    int imgArrLength = w*h;

    float min = 3.4e38f;
    float max = -3.4e38f;


    // Loop for calculating min and max

    for (int i = 0; i < imgArrLength; i++){
        
        if (img[i] < min){
            min = img[i];               // min pixel
        }

        if (img[i]>max){
            max = img[i];               // max pixel
        }
        
    }

    if (max == min){                     // Edge Case

        for (int i = 0; i < imgArrLength; i++){
            result[i] = 0;              // Output a Black Image
        }

    }

    else{                               // Normal Case

        float range = max - min;
    
        for (int i = 0; i < imgArrLength; i++){

            float scaledPixel = ((img[i] - min)/range) * 255 ;  // Calculate scaled pixel
            assert(scaledPixel<=255 && scaledPixel>=0);         // Error Handling 

            result[i] = scaledPixel;                            // Store the scaled pixel     
        }
    }
    
}

float get_pixel_value(const float *img, int w, int h, int x, int y) {


    if (img == NULL || w==0 || h==0 ){
        return 1;                         // Error Handling
    }

    float grayscale;
    int newX = x;
    int newY = y;

    int maxW = w-1;
    int maxH = h-1;

    // Calculate adjusted x coordinate below
    
    if (x < 0)
    {
        newX = (x*(-1)) - 1;
    }
    else if (x > (maxW))
    {
        newX = (2*(maxW)) - x + 1 ;
    }

    // Calculate adjusted y coordinate below
    
    if (y < 0)
    {
        newY = (y*(-1)) - 1;
    }
    else if (x > (maxH))
    {
        newY = (2*(maxH)) - y + 1 ;
    }
    
    //Error Handling
    if((newX >= w || newX <0) || (newY >= h || newY <0)){
        get_pixel_value(img , w , h , newX , newY);
    }

    printf("%d %d\n", newX , newY);
    
    assert((newX < w && newX >=0) && (newY < h && newY >=0));

    grayscale = img[(w*newY)+ newX];        // Get the new pixel value 
    return grayscale;
}

float *array_init(int size) {
    (void)size;

    // TODO: Implement me!

    return NULL;
}

void array_destroy(float *m) {
    (void)m;

    // TODO: Implement me!
}

float *read_image_from_file(const char *filename, int *w, int *h) {
    (void)filename;
    (void)w;
    (void)h;

    // TODO: Implement me!

    return NULL;
}

void write_image_to_file(const float *img, int w, int h, const char *filename) {
    (void)img;
    (void)w;
    (void)h;
    (void)filename;

    // TODO: Implement me!
}

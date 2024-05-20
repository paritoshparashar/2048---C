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
    else if (y > (maxH))
    {
        newY = (2*(maxH)) - y + 1 ;
    }
    
    //Error Handling
    if((newX >= w || newX <0) || (newY >= h || newY <0)){
        get_pixel_value(img , w , h , newX , newY);
    }

    assert((newX < w && newX >=0) && (newY < h && newY >=0));

    grayscale = img[(w*newY)+ newX];        // Get the new pixel value 
    return grayscale;
}

float *array_init(int size) {
    
    float* arr = malloc ( size * sizeof(arr[0]));

    assert(arr != NULL);

    return arr;
}

void array_destroy(float *m) {
    
    assert ( m != NULL);

    free (m);

    
}

float *read_image_from_file(const char *filename, int *w, int *h) {
    
    // Error handling = File not present

    if (filename == NULL){
        return NULL;
    }

    // Open file if it exists, don't forget to close it bud

    FILE* opendedFile = fopen (filename , "r");

    float width;
    float height;
    float maxBrightness;

    // Error handling = File format not correct

    if ( (fscanf(opendedFile , "P2 %f %f %f" , &width , &height , &maxBrightness )) != 3)
    {
        fclose(opendedFile);
        return NULL;    
    }

    // Change the float read values to int
    int maxBrightness_int = (int) maxBrightness;
    int width_int = (int) width;
    int height_int = (int) height;

    // Error handling = widht/height/maxBright not correct

    if ( width_int<=0 || height_int<=0 || maxBrightness_int!= 255)
    {
        fclose(opendedFile);
        return NULL;
    }

    assert (width_int > 0 && height_int > 0 && maxBrightness_int == 255);

    // Store width and height at the location where pointers are pointing to

    *w = width_int;
    *h = height_int;
    
    
    int lengthOfImageArr = (width_int * height_int) -1; 

    // Get the memory to store image
    float* image = array_init ((width_int * height_int));
    assert (image != NULL);

    for (int i = 0; i <= lengthOfImageArr; i++)
    {

        int readSuccess = fscanf ( opendedFile, "%f" , &image[i]);

        // Error Handling : pixel < 0 or pixel > 255 => broken image

        if (image[i] < 0 || image[i] > 255)
        {
            array_destroy (image);
            fclose(opendedFile);
            return NULL;
        }
        
        // Error Handling : Too few pixels
        
        if (readSuccess != 1)
        {
            array_destroy (image);
            fclose(opendedFile);
            return NULL;
        }
         
    }

    // Error Handling : Too many pixels

    float end;
    
    if (fscanf (opendedFile , "%f" , &end) != EOF)
    {
        array_destroy (image);
        fclose (opendedFile);
        return NULL;
    }

    // Successful : Close file and return the pointer to memory

    fclose (opendedFile);
    return image;

}

void write_image_to_file(const float *img, int w, int h, const char *filename) {
    
    FILE* output_file = fopen (filename , "w");

    if (output_file == NULL)
    {
        return;
    }

    // Write the headers

    fprintf ( output_file , "P2\n");
    fprintf ( output_file , "%d %d\n" , w , h);
    fprintf ( output_file , "255\n");

    // Load Pixels

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int pixel_val  = (int) img[w*i + j];

            fprintf ( output_file , "%d " , pixel_val);
        }
        
        fprintf ( output_file , "\n");
        
    }
    
    fclose (output_file);
    return;
    
}

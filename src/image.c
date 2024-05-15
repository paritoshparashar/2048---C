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
    (void)result;
    (void)img;
    (void)w;
    (void)h;

    // TODO: Implement me!
}

float get_pixel_value(const float *img, int w, int h, int x, int y) {
    (void)img;
    (void)w;
    (void)h;
    (void)x;
    (void)y;

    // TODO: Implement me!

    return 0;
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

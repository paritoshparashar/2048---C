#include <stdio.h>
#include <stdlib.h>

#include "argparser.h"
#include "convolution.h"
#include "derivation.h"
#include "gaussian_kernel.h"
#include "image.h"

int main(int const argc, char **const argv) {
    /**
     * Parse arguments. The parsed image file name and threshold are available
     * in the image_file_name and threshold global variables (see argparser.h).
     */
    parse_arguments(argc, argv);
    printf("Computing edges for image file %s with threshold %i\n",
           image_file_name, threshold);

    /**
     * Read Image from given file.
     *
     * If the input file is broken terminate with return value 1.
     *
     * Hint: The width and height of the image have to be accessible in the
     * scope of this function.
     */

       int* width;
       int* height;

       float* img_pointer = read_image_from_file (image_file_name , width , height);

       if (img_pointer == NULL)
       {
              return 1;
       }
       
       
    /**
     * Blur the image by using convolve with the given Gaussian kernel matrix
     * gaussian_k (defined in gaussian_kernel.h). The width of the matrix is
     * gaussian_w, the height is gaussian_h.
     *
     * Afterwards, write the resulting blurred image to the file out_blur.pgm.
     */

       float* convolved_img = array_init ( (*width) * (*height) );

       convolve ( convolved_img , img_pointer , *width , *height , gaussian_k , gaussian_w , gaussian_h);
       array_destroy (img_pointer);

       write_image_to_file (convolved_img , *width , *height , "out_blur.pgm");
       array_destroy (convolved_img);


    /**
     * Compute the derivation of the blurred image computed above in both x and
     * y direction.
     *
     * Afterwards, rescale both results and write them to the files out_d_x.pgm
     * and out_d_y.pgm respectively.
     */

       float* blur_img_pointer = read_image_from_file ("out_blur.pgm", width , height);


       // Compute derivation in 'x' and 'y' direction

       float* x_derived_img = array_init ((*width) * (*height));
       derivation_x_direction ( x_derived_img , blur_img_pointer , *width , *height);

       float* y_derived_img = array_init ((*width) * (*height));
       derivation_x_direction ( y_derived_img , blur_img_pointer , *width , *height);

       array_destroy (blur_img_pointer);


       // Rescale both 'x' and 'y' derived result

       float* x_scaled_img = array_init ((*width) * (*height));
       scale_image ( x_scaled_img , x_derived_img , *width , *height);

       float* y_scaled_img = array_init ((*width) * (*height));
       scale_image ( y_scaled_img , y_derived_img , *width , *height);


       // Write the scaled images to respective pgm files

       write_image_to_file ( x_scaled_img , *width , *height , "out_d_x.pgm");
       write_image_to_file ( y_scaled_img , *width , *height , "out_d_y.pgm");

       array_destroy (x_scaled_img);
       array_destroy (y_scaled_img);


    /**
     * Compute the gradient magnitude of the blurred image by using the
     * (unscaled!) derivations in x- and y-direction computed earlier.
     *
     * Afterwards, rescale the result and write it to out_gm.pgm.
     */

       // Compute Gradient of x and y derivations

       float* gradient_img = array_init ((*width) * (*height));

       gradient_magnitude ( gradient_img , x_derived_img , y_derived_img , *width , *height);

       array_destroy (x_derived_img);
       array_destroy (y_derived_img);

       // Write the gradient result to out_gm

       write_image_to_file (gradient_img , *width , *height , "out_gm.pgm");

    /**
     * Apply the threshold to the gradient magnitude.
     * Then write the result to the file out_edges.pgm.
     */
    // TODO: Implement me!

    /**
     * Remember to free dynamically allocated memory when it is no longer used!
     */
}

#include "image_resample.h"
#include "pictures.h"
#include "manage_images.h"
#include <stdio.h>

/**
 * @requires image is a non empty picture (width > 0, height > 0 by default)
 * @assigns image_resampled
 * @ensures returns the resampled picture
 */
picture resample_picture_nearest(picture image, unsigned int width, unsigned int height) {
    picture image_resampled;
    if (is_empty_picture(image) == -1) {
        image_resampled = create_picture(0, 0, 0);
    }
    else {
        image_resampled = create_picture(width, height, image.channels);

        /* compute the scale factors */
        double x_scale_factor = (double) image.width / width; /* first converts p.width to double */
        double y_scale_factor = (double) image.height / height;

        /* for each pixel (x,y,c) in the new image... */
        for (int x = 0 ; x < height ; x = x + 1) {
            for (int y = 0 ; y < width ; y = y + 1) {
                /* compute the nearest pixel coordinates (src_x,src_y,c) in the original image */
                int src_x = (int) x * x_scale_factor;
                int src_y = (int) y * y_scale_factor;

                /* copy the data for all channels */
                for (int c = 0 ; c < image.channels ; c = c + 1) {
                    image_resampled.data[(x * width + y) * image.channels + c] = image.data[(src_x * image.width + src_y) * image.channels + c];
                }
            }
        }
    }
    return image_resampled;
}

/**
 * @requires image is a non empty
 * @assigns image_resampled
 * @ensures returns the resampled image
 */
picture resample_picture_bilinear(picture image, unsigned int width, unsigned int height) {
    picture image_resampled;
    if (is_empty_picture(image) == -1) {
        image_resampled = create_picture(0, 0, 0);
    }
    else {
        image_resampled = create_picture(width, height, image.channels);

        /* compute the scale factors */
        double x_scale_factor = (double) image.width / width;
        double y_scale_factor = (double) image.height / height;

        /* for each pixel (x,y,c) in the new image... */
        for (int y = 0; y < height; y = y +1) {
            for (int x = 0; x < width; x = x + 1) {
                /* compute the nearest pixel coordinates (src_x,src_y,c) in the original image */
                double src_x = x * x_scale_factor;
                double src_y = y * y_scale_factor;

                /* compute the coordinates of the four surronding pixels of the nearest pixel */
                int x1 = (int) src_x; /* the lowest nearest on the x axis */
                int y1 = (int) src_y; /* the lowest nearest on the y axis */
                int x2; /* the highest nearest on the x axis */
                int y2; /* the highest nearest on the y axis */
                if (x1 + 1 < image.width) {
                    x2 = x1 + 1;
                }
                else {
                    x2 = x1;
                }
                if (y1 + 1 < image.height) {
                    y2 = y1 + 1;
                }
                else {
                    y2 = y1;
                }

                /* compute interpolation coefficients */
                double alpha = src_x - x1;
                double beta = src_y - y1;

                /* perform bilinear interpolation for each channel */
                for (int c = 0; c < image.channels; c = c + 1) {
                    double top_left = image.data[(y1 * image.width + x1) * image.channels + c];
                    double top_right = image.data[(y1 * image.width + x2) * image.channels + c];
                    double bottom_left = image.data[(y2 * image.width + x1) * image.channels + c];
                    double bottom_right = image.data[(y2 * image.width + x2) * image.channels + c];
                    image_resampled.data[(y * width + x) * image.channels + c] = (int) ((1 - alpha) * (1 - beta) * top_left + alpha * (1 - beta) * top_right + (1 - alpha) * beta * bottom_left + alpha * beta * bottom_right);
                }
            }
        }
    }
    return image_resampled;
}
#include "image_arithmetic.h"
#include "pictures.h"
#include "manage_images.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @requires p1 and p2 must be pictures with the same dimensions and channels and not empty.
 * @assigns Allocates memory for the resulting picture.
 * @ensures Returns a picture which is the absolute difference between the two images. If the dimensions or channels do not match, returns an empty picture.
 */
picture picture_difference(picture p1, picture p2) {
    /* returns an empty image if the caracteristics don't match */
    if (p1.width != p2.width || p1.height != p2.height || p1.channels != p2.channels || is_empty_picture(p1) == -1 || is_empty_picture(p2) == -1) {
        return create_picture(0, 0, 0);
    }

    picture p_diff = create_picture(p1.width, p1.height, p1.channels);
    for (int i = 0 ; i < p1.width * p1.height * p1.channels ; i = i + 1) {
        p_diff.data[i] = abs(p1.data[i] - p2.data[i]);
    }
    return p_diff;
}

/**
 * @requires p1 and p2 must be pictures with the same dimensions and not empty.
 * @assigns Allocates memory for the resulting picture.
 * @ensures Returns a picture representing the product of the two images. If the dimensions do not match, returns an empty picture.
 */
picture mult_picture(picture p1, picture p2) {
    if (p1.width != p2.width || p1.height != p2.height || is_empty_picture(p1) == -1 || is_empty_picture(p2) == -1) {
        return create_picture(0, 0, 0);
    }
    picture p_mult;
    if (p1.channels == p2.channels) {
        p_mult = create_picture(p1.width, p1.height, p1.channels);
        for (int i = 0 ; i < p1.width * p1.height * p1.channels ; i = i + 1) {
            p_mult.data[i] = (int) ((p1.data[i] * p2.data[i]) / MAX_BYTE);
        }
    }
    if (p1.channels == 1 && p2.channels == 3) {
        p_mult = create_picture(p1.width, p1.height, 3);
        for (int i = 0 ; i < p1.width * p1.height ; i = i + 1) {
            for (int c = 0 ; c < 3 ; c = c + 1) {
                p_mult.data[3 * i + c] = (int) ((p1.data[i] * p2.data[3 * i + c]) / MAX_BYTE);
            }
        }
    }
    if (p1.channels == 3 && p2.channels == 1) {
        p_mult = create_picture(p1.width, p1.height, 3);
        for (int i = 0 ; i < p1.width * p1.height ; i = i + 1) {
            for (int c = 0 ; c < 3 ; c = c + 1) {
                p_mult.data[3 * i + c] = (int) ((p1.data[3 * i + c] * p2.data[i]) / MAX_BYTE);
            }
        }
    }
    return p_mult;
}

/**
 * @requires Nothing.
 * @assigns Nothing.
 * @ensures Returns the maximum of the three integers.
 */
int max_int(int a, int b, int c) {
    int max = a;  // Assume a is the maximum initially

    if (b > max) {
        max = b;  // If b is greater, update max
    }

    if (c > max) {
        max = c;  // If c is greater, update max
    }

    return max;
}

/**
 * @requires p1, p2, and p3 must be pictures with the same dimensions and not empty.
 * @assigns Allocates memory for the resulting picture.
 * @ensures Returns an image which is the mix of the three images. If the dimensions do not match, returns an empty picture.
 */
picture mix_picture(picture p1, picture p2, picture p3) {
    /* return an empty picture if p1, p2 and p3 are not the same size */
    if (p1.width != p2.width || p1.height != p2.height || p1.width != p3.width || p1.height != p3.height || is_empty_picture(p1) == -1 || is_empty_picture(p2) == -1 || is_empty_picture(p3) == -1) {
        printf("Images are not the same size\n");
        return create_picture(0, 0, 0);
    }
    int max_channels = max_int(p1.channels, p2.channels, p3.channels);
    picture p_result = create_picture(p1.width, p1.height, max_channels);
    picture p1_color;
    picture p2_color;
    picture p3_color;
    if (max_channels == 3) {
        p1_color = convert_to_color_picture(p1);
        p2_color = convert_to_color_picture(p2);
        p3_color = convert_to_color_picture(p3);
    }
    else {
        p1_color = copy_picture(p1);
        p2_color = copy_picture(p2);
        p3_color = copy_picture(p3);
    }
    for (int i = 0 ; i < p1_color.width ; i = i + 1) {
        for (int j = 0 ; j < p1_color.height ; j = j + 1) {
            for (int c = 0 ; c < max_channels ; c = c + 1) {
                int index_1 = (i * p1_color.height + j) * p1_color.channels + c;
                int index_2 = (i * p2_color.height + j) * p2_color.channels + c;
                int index_3 = (i * p3_color.height + j) * p3_color.channels + c;
                int index_big = (i * p3_color.height + j) * max_channels + c; /* ppm */
                double alpha = (double) (p3_color.data[index_3] / MAX_BYTE);
                p_result.data[index_big] = (int) ((1 - alpha) * p1_color.data[index_1] + alpha * p2_color.data[index_2]);
            }
        }
    }
    return p_result;
}
#include "handle_pixels_directly.h"
#include "pictures.h"
#include "manage_images.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @requires p is a valid non empty picture structure and factor is a positive double value.
 * @assigns a copy of p.
 * @ensures Returns a new picture brightened by the factor, or an empty picture if p is empty.
 */
picture brighten_picture(picture p, double factor) {
    if (is_empty_picture(p) == -1) {
        return create_picture(0, 0, 0);
    }
    picture p_copy = copy_picture(p);
    for (int i = 0 ; i < p.width * p.height * p.channels ; i = i + 1) {
        int brightened_pixel = p.data[i] * factor; /* implicit conversion */
        if (brightened_pixel > MAX_BYTE) {
            p_copy.data[i] = MAX_BYTE; /* max brightness */
        }
        else {
            p_copy.data[i] = brightened_pixel;
        }
    }
    return p_copy;
}

/**
 * @requires p is a valid non empty picture structure number is a positive integer.
 * @assigns a copy of p
 * @ensures Returns a new picture with some pixels melted or an empty picture if p is empty.
 */
picture melt_picture(picture p, int number) {
    picture p_copy;
    if (is_empty_picture(p) == -1) {
        p_copy = create_picture(0, 0, 0);
    }
    else {
        p_copy = copy_picture(p);
        for (int i = 0 ; i < number ; i = i + 1) {
            int r = rand() % (p.width * p.height);
            int index = (r * p.channels);
            if (index > (p.width)*(p.channels)) {
                if (((p_copy.data[index] + p_copy.data[index + 1] + p_copy.data[index + 2])/3) > ((p_copy.data[index - p.width] + p_copy.data[index + 1 - p.width] + p_copy.data[index + 2 - p.width])/3)) {
                    p_copy.data[index] = p_copy.data[index - (p.width*p.channels)];
                    p_copy.data[index + 1] = p_copy.data[index + 1 - (p.width*p.channels)];
                    p_copy.data[index + 2] = p_copy.data[index + 2 - (p.width*p.channels)];
                }
            }
        }
    }
    return p_copy;
}
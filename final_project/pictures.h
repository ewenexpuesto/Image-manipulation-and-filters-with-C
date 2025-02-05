/*
 * pictures.h
 * Contains definitions of data for images and bytes
 * Contains functions to manipulate images
 */

#ifndef PICTURES_H
#define PICTURES_H

#define MAX_BYTE 255

typedef unsigned char byte; /* 0 to 255 as unsigned char */

typedef struct picture {
    unsigned int width; /* unsigned because always positive */
    unsigned int height;
    unsigned int channels; /* 1 for pgm and 3 for ppm */
    byte * data; /* a pointer towards bytes (can be a byte tab[]) */
} picture;

/** 
 * Inverts the colors of an image
 * @param [in] p the image to invert
 * @return the inverted image
 */
picture inverse_picture(picture p);

/**
 * Normalize an image dynamically
 * @param [in] p the image to normalize
 * @return the normalized image
 */
picture normalize_dynamic_picture(picture p);

/**
 * Discretize an image
 * @param [in] p the image to discretize
 * @param [in] nb_levels the number of levels to set
 * @return the image discretized
 */
picture set_levels_picture(picture p, byte nb_levels);

#endif
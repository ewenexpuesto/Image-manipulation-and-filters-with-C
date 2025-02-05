/*
 * lut.h
 * Contains functions to manipulate lookup tables for images.
 *  - create_lut: creates a lookup table of a given size
 *  - clean_lut: frees the memory allocated for a lookup table
 *  - apply_lut: applies a lookup table to an image
 */

#ifndef LUT_H
#define LUT_H

#include "pictures.h"

typedef struct lut {
    int n;
    int * tab;
} lut;

/**
 * Creates a lookup table
 * @param [in] n the size of the lookup table
 * @return the lookup table
 */
lut create_lut(int n);

/**
 * Frees the memory allocated for a lookup table
 * @param [in, out] l the lookup table to free
 */
void clean_lut(lut * l);

/**
 * Applies a lookup table to an image
 * @param [in] p the image to apply the lookup table to
 * @param [in] l the lookup table to apply
 * @return the image with the lookup table applied
 */
picture apply_lut(picture p, lut l);

#endif
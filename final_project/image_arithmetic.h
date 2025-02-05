/*
 * image_arithmetic.h
 * Contains functions to perform arithmetic operations on images.
 *  - picture_difference: computes the absolute difference between two images
 *  - mult_picture: multiplies two images
 *  - max_int: computes the maximum of three integers
 *  - mix_picture: mixes two images according to a third image
 */

#ifndef IMAGE_ARITHMETIC_H
#define IMAGE_ARITHMETIC_H

#include "pictures.h"

/**
 * Computes the difference between two images
 * @param [in] p1 the first image
 * @param [in] p2 the second image
 * @return the absolute difference between the two images
 */
picture picture_difference(picture p1, picture p2);

/**
 * Multiplies two images
 * @param [in] p1 the first image
 * @param [in] p2 the second image
 * @return an image which is the product of the two images
 */
picture mult_picture(picture p1, picture p2);

/**
 * Computes the maximum of three integers
 * @param [in] a the first integer
 * @param [in] b the second integer
 * @param [in] c the third integer
 * @return the maximum of the three integers
 */
int max_int(int a, int b, int c);

/**
 * Mixes two images according to a third image
 * @param [in] p1 the first image
 * @param [in] p2 the second image
 * @param [in] p3 the third image
 * @return an image which is the mix of the three images
 */
picture mix_picture(picture p1, picture p2, picture p3);

#endif
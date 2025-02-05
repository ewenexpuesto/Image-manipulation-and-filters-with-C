/*
 * handle_pixels_directly.h
 * Contains functions to manipulate pixels of pictures directly.
 *  - brighten_picture: brightens an image by a given factor
 *  - melt_picture: melts the pixels of an image downwards by a given number
 */

#ifndef HANDLE_PIXELS_DIRECTLY_H
#define HANDLE_PIXELS_DIRECTLY_H

#include "pictures.h"

/**
 * Brightens an image
 * @param [in] p the image to brighten
 * @param [in] value the factir to brighten the pixels by
 * @return the brightened image
 */
picture brighten_picture(picture p, double factor);

/**
 * Melts the value of pixels of an image
 * @param [in] p the image to melt
 * @param [in] value the number of pixels to choose randomly
 * @return the downwards melted image
 */
picture melt_picture(picture p, int number);

#endif
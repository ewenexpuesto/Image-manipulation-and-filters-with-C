/*
 * image_resample.h
 * Contains functions to resample images using different methods.
 *  - resample_picture_nearest: resamples an image using the nearest neighbor method
 *  - resample_picture_bilinear: resamples an image using the bilinear method
 */

#ifndef IMAGE_RESAMPLE_H
#define IMAGE_RESAMPLE_H

#include "pictures.h"

/**
 * Resample an image using the nearest neighbor method
 * @param [in] image the image to resample
 * @param [in] width the new width of the image
 * @param [in] height the new height of the image
 * @return the resampled image
 */
picture resample_picture_nearest(picture p, unsigned int width, unsigned int height);

/**
 * Resample an image using the bilinear method
 * @param [in] image the image to resample
 * @param [in] width the new width of the image
 * @param [in] height the new height of the image
 * @return the resampled image
 */
picture resample_picture_bilinear(picture image, unsigned int width, unsigned int height);

#endif
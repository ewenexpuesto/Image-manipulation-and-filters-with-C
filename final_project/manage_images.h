/*
 * manage_images.h
 * Contains functions to manage images, including creation, copying, and checking properties
 */

#ifndef MANAGE_IMAGES_H
#define MANAGE_IMAGES_H

#include "pictures.h"

/**
 * Creates an empty image
 * @param [in] width the width of the image
 * @param [in] height the height of the image
 * @param [in] channels the number of channels of the image
 * @return an empty image of size width x height x channels
 */
picture create_picture(unsigned int width, unsigned int height, unsigned int channels);

/**
 * Frees the memory allocated for an image
 * @param [in, out] p the image to free
 */
void clean_picture(picture * p);

/**
 * Copies an image
 * @param [in] p the image to copy
 * @return a copy of the image p
 */
picture copy_picture(picture p);

/**
 * Checks if an image is empty
 * @param [in] p the image to check
 * @return -1 if the image is empty, 0 otherwise
 */
int is_empty_picture(picture p);

/**
 * Checks if an image is in grayscale
 * @param [in] p the image to check
 * @return 1 if the image is in grayscale, 0 otherwise
 */
int is_gray_picture(picture p);

/**
 * Checks if an image is in color
 * @param [in] p the image to check
 * @return 1 if the image is in color, 0 otherwise
 */
int is_color_picture(picture p);

/**
 * Displays the information of an image
 * @param [in] p the image to display
 */
void info_picture(picture p);

/**
 * Converts a grayscale image to a color image
 * @param [in] p the grayscale image to convert
 * @return a color image
 */
picture convert_to_color_picture(picture p);

/**
 * Converts a color image to a grayscale image
 * @param [in] p the color image to convert
 * @return a grayscale image
 */
picture convert_to_gray_picture(picture p);

/**
 * Splits an image into three images according to the channels
 * @param [in] p the image to split
 * @return an array of three images
 */
picture * split_picture(picture p);

/**
 * Merges three images of different channels into a single image
 * @param [in] red the red channel
 * @param [in] green the green channel
 * @param [in] blue the blue channel
 * @return a color image, the mix of the three channels
 */
picture merge_picture(picture red, picture green, picture blue);

#endif
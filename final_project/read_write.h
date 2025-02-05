/*
 * read_write.h
 * Contains functions to read and write pictures from/to files.
 *  - read_picture: reads a picture from a file
 *  - write_picture: writes a picture to a file
 *  - free_picture: frees the memory allocated for a picture
 */

#ifndef PIXELS_H
#define PIXELS_H

#include "pictures.h"

enum color {RED, GREEN, BLUE}; /* what to use for ? */

/**
 * Reads a picture from a file
 * @param [in] filename the name of the file to read
 * @return the picture read from the file
 */
picture read_picture(char * filename);

/**
 * Writes a picture to a file
 * @param [in] p the picture to write
 * @param [in] filename the name of the file to write to
 * @return 0 if the picture was written successfully, -1 otherwise
 */
int write_picture(picture p, char * filename);

/**
 * Frees the memory allocated for a picture
 * @param [in, out] p the picture to free
 */
void free_picture(picture * p);

#endif
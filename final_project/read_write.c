#include "read_write.h"
#include "pictures.h"
#include "filename.h"
#include "manage_images.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @requires nothing.
 * @assigns allocates memory for the picture data.
 * @ensures returns a picture structure with the image data if successful or an empty picture otherwise.
 */
picture read_picture(char * filename) {
    FILE * f;
    f = fopen(filename, "r");

    /* if there is an error opening the file*/
    if (f == NULL) { 
        perror("Error opening file");
        picture img = create_picture(0, 0, 0);
        return img;
    }

    /* get the extension */
    char * ext = ext_from_path(filename);

    char buffer[128]; 
    int width;
    int height;
    int max;

    /* read the first line */
    fgets(buffer, 128, f);

    /* check if it is a binary PGM file (for instance not ASCII) */
    if (strcmp(ext, "pgm") == 0) {
        if (strcmp(buffer, "P5\n")) {
            perror ("Not a binary PGM file "); 
            fclose(f);
            picture img = create_picture(0, 0, 0);
            return img;
        }
    }
    if (strcmp(ext, "ppm") == 0) {
        if (strcmp(buffer, "P6\n" )) {
            perror ("Not a binary PPM file "); 
            fclose(f);
            picture img = create_picture(0, 0, 0);
            return img;
        }
    }

    /* read the next line (dimension or "#") */
    fgets(buffer, 128, f);

    /* reading comment lines to skip */
    while (buffer[0] == '#') {
        fgets(buffer, 128, f);
    }

    /* get image dimensions */
    sscanf(buffer, "%d %d", &width, &height);

    /* check if width or height at 0 */
    if (width == 0 || height == 0) {
        perror("Width or height is 0 ");
        fclose(f);
        picture img = create_picture(0, 0, 0);
        return img;
    }

    /* read the next line (max or "#") */
    fgets(buffer, 128, f);

    /* reading comment lines to skip */
    while (buffer[0] == '#') {
        fgets(buffer, 128, f);
    }

    /* read the next line and get the max */
    sscanf(buffer, "%d", &max);

    /* check if max is 255 */
    if (max != MAX_BYTE) {
        perror("Max is not 255 ");
        fclose(f);
        picture img = create_picture(0, 0, 0);
        return img;
    }

    /* reading comment lines to skip */
    while (buffer[0] == '#') {
        fgets(buffer, 128, f);
    }

    /* get the size of the file starting from the current position */
    long current_position = ftell(f); /* number of lines read until now */
    fseek(f, 0, SEEK_END); /* place the cursor at the end */
    long file_size = ftell(f); /* total number of lines */
    long remaining_size = file_size - current_position;

    /* check if the number of pixels corresponds to width * height * channels */
    if (strcmp(ext, "pgm") == 0 && width * height * sizeof(byte) != remaining_size) {
        perror("Number of pixels does not correspond to width * height * channels ");
        fclose(f);
        picture img = create_picture(0, 0, 0);
        return img;
    }
    if (strcmp(ext, "ppm") == 0 && width * height * sizeof(byte) * 3 != remaining_size) {
        perror("Number of pixels does not correspond to width * height * channels ");
        fclose(f);
        picture img = create_picture(0, 0, 0);
        return img;
    }

    /* set the cursor back to the start past the header */
    fseek(f, current_position, SEEK_SET);
    
    /* allocate memory */
    if (strcmp(ext, "pgm") == 0) {
        byte * data = (byte *) malloc(width * height * sizeof(byte));
        /* reads starting at the file pointer */
        fread(data, sizeof(byte), width * height, f);
        
        fclose(f);

        picture img;
        img.width = width;
        img.height = height;
        img.channels = 1; /* grayscale image */
        img.data = data;

        return img;
    }

    if (strcmp(ext, "ppm") == 0) {
        byte * data = (byte *) malloc(width * height * 3 * sizeof(byte));
        /* reads starting at the file pointer */
        fread(data, sizeof(byte), width * height * 3, f);

        fclose(f);

        picture img;
        img.width = width;
        img.height = height;
        img.channels = 3; /* color image */
        img.data = data;

        return img;
    }

    picture img = create_picture(0, 0, 0);
    return img;
}

/**
 * @requires nothing
 * @assigns writes to the file specified by filename.
 * @ensures writes the picture data to the file in PGM or PPM format, returns 0 on success, -1 on failure.
 */
int write_picture(picture img, char * filename) {
    FILE * f = fopen(filename, "wb");

    if (f == NULL) { 
        perror("Error opening file");
        return -1;
    }

    /* get the extension and check if ppm or pgm */
    char * ext = ext_from_path(filename);
    if (strcmp(ext, "pgm") != 0 && strcmp(ext, "ppm") != 0) {
        perror("Not a pgm or ppm file");
        fclose(f);
        return -1;
    }

    /* checks if file type corresponds to the image type */
    if (img.channels == 1 && strcmp(ext, "pgm") != 0) {
        printf("Error: Expected PGM file for grayscale image, but got %s\n", ext);
        fclose(f);
        return -1;
    }
    if (img.channels == 3 && strcmp(ext, "ppm") != 0) {
        printf("Error: Expected PPM file for color image, but got %s\n", ext);
        fclose(f);
        return -1;
    }

    /* write the header */
    if (img.channels == 1) {
        fprintf(f, "P5\n%d %d\n255\n", img.width, img.height);
    }
    if (img.channels == 3) {
        fprintf(f, "P6\n%d %d\n255\n", img.width, img.height);
    }

    /* write the data according to the channel */
    fwrite(img.data, sizeof(byte), img.width * img.height * img.channels, f);

    fclose (f);

    return 0;
}

/**
 * @requires nothing.
 * @assigns frees the memory allocated for the picture.
 * @ensures the data pointer in the picture structure is set to NULL.
 */
void free_picture(picture * img) {
    if (img->data != NULL) {
        free(img->data);
        img->data = NULL;
    }
}
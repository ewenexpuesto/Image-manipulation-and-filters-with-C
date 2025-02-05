#include "pictures.h"
#include "manage_images.h"
#include <stdlib.h>
#include <stdio.h>

/* 
@requires nothing
@assigns allocates memory for p.data
@ensures returns an empty image of size width x height x channels
*/
picture create_picture(unsigned int width, unsigned int height, unsigned int channels) {
    picture p;
    p.width = width;
    p.height = height;
    p.channels = channels;
    p.data = (byte *) calloc(width * height * channels, sizeof(byte));
    return p;
}

/* 
@requires a non empty picture
@assigns frees memory allocated for p->data, sets p->data to NULL, and resets width, height, and channels to 0
@ensures p is cleaned
*/
void clean_picture(picture * p) {
    if (is_empty_picture(* p) == 0) {
        free(p->data);
        p->data = NULL;
        p->width = 0;
        p->height = 0;
        p->channels = 0;
    }
}

/* 
@requires a non empty picture p
@assigns allocates memory for p_copy.data
@ensures returns a copy of the image p, or an empty image if p is empty
*/
picture copy_picture(picture p) {
    picture p_copy;
    if (is_empty_picture(p) == -1) {
        p_copy = create_picture(0, 0, 0);
    }
    else {
        p_copy = create_picture(p.width, p.height, p.channels);
        for (int i = 0 ; i < p.width * p.height * p.channels ; i = i + 1) {
            p_copy.data[i] = p.data[i];
        }
    }
    clean_picture(&p);
    return p_copy;
}

/* 
@requires nothing
@assigns nothing
@ensures returns -1 if the picture is empty, 0 otherwise
*/
int is_empty_picture(picture p) {
    if (p.width == 0 || p.height == 0 || p.channels == 0 || p.data == NULL) {
        return -1;
    }
    return 0;
}

/* 
@requires nothing
@assigns nothing
@ensures returns 1 if the picture is grayscale, 0 otherwise
*/
int is_gray_picture(picture p) {
    if (p.channels == 1) {
        return 1;
    }
    return 0;
}

/* 
@requires nothing
@assigns nothing
@ensures returns 1 if the picture is color, 0 otherwise
*/
int is_color_picture(picture p) {
    if (p.channels == 3) {
        return 1;
    }
    return 0;
}

/* 
@requires nothing
@assigns nothing
@ensures prints the dimensions and channels of the picture
*/
void info_picture(picture p) {
    printf("(%d X %d X %d)\n", p.width, p.height, p.channels);
}

/* 
@requires nothing
@assigns allocates memory for p_color.data if p is grayscale
@ensures returns a color picture converted from grayscale if p is grayscale, otherwise returns a copy of p
*/
picture convert_to_color_picture(picture p) {
    if (is_gray_picture(p) != 1) {
        picture copy_p;
        copy_p = copy_picture(p);
        return copy_p;
    }
    else {
        picture p_color = create_picture(p.width, p.height, 3);

        /* converts each pixel from grayscale to color */
        for (int i = 0 ; i < p.width * p.height ; i = i + 1) {
            p_color.data[3 * i] = p.data[i];
            p_color.data[3 * i + 1] = p.data[i];
            p_color.data[3 * i + 2] = p.data[i];
        }
        return p_color;
    }
}

/* 
@requires p nothing
@assigns allocates memory for p_gray.data if p is color
@ensures returns a grayscale picture converted from color if p is color, otherwise returns a copy of p
*/
picture convert_to_gray_picture(picture p) {
    if (is_color_picture(p) == 1) {
        picture p_gray = create_picture(p.width, p.height, 1);

        /* convert each pixel from color to grayscale */
        for (int i = 0 ; i < p.width * p.height ; i = i + 1) {
            p_gray.data[i] = (0.299 * (p.data[3 * i])) + (0.587 * (p.data[3 * i + 1])) + (0.114 * (p.data[3 * i + 2]));
        }

        return p_gray;
    }
    else {
        picture copy_p;
        copy_p = copy_picture(p);
        return copy_p;
    }
}

/* 
@requires p nothing
@assigns allocates memory for p_split if p is a color picture
@ensures returns an array of pictures split by color channels if p is a color picture, otherwise returns a copy of p
*/
picture * split_picture(picture p) {
    /* if p cannot be split */
    if (p.channels != 3) {
        clean_picture(&p);
        return NULL;
    }

    /* if p is not a color picture */
    if (is_color_picture(p) != 1) {
        picture * ptr = (picture *) malloc(sizeof(picture));
        ptr[0] = copy_picture(p);
        return ptr;
    }

    /* a tab of 3 elements for a color image */
    picture * p_split = (picture *) malloc(p.channels * sizeof(picture));

    /* for each color... */
    for (int i = 0 ; i < p.channels ; i = i + 1) {
        p_split[i] = create_picture(p.width, p.height, 1);
        for (int j = 0 ; j < p.width * p.height ; j = j + 1) {
            p_split[i].data[j] = p.data[p.channels * j + i]; /* sorted by color */
        }
    }
    return p_split;
}

/* 
@requires red, green, and blue are pictures with the same dimensions and channels
@assigns allocates memory for the merged picture
@ensures returns a color image, the mix of the three channels
*/
picture merge_picture(picture red, picture green, picture blue) {
    /* if the pictures are not the same type */
    if (red.channels != green.channels || red.channels != blue.channels) {
        return create_picture(0, 0, 0);
    }

    /* if the pictures are not the same size */
    if (red.width != green.width || red.width != blue.width || red.height != green.height || red.height != blue.height) {
        return create_picture(0, 0, 0);
    }

    picture p = create_picture(red.width, red.height, 3);

    for (int i = 0 ; i < red.width * red.height ; i = i + 1) {
        p.data[3 * i] = red.data[i];
        p.data[3 * i + 1] = green.data[i];
        p.data[3 * i + 2] = blue.data[i];
    }
    return p;
}
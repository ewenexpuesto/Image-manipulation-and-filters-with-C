#include "lut.h"
#include "pictures.h"
#include "manage_images.h"
#include <stdlib.h>

/**
 * @requires n >= 0
 * @assigns allocates memory for the lut l
 * @ensures returns the lookup table, return {0, NULL} if n < 0
 */
lut create_lut(int n) {
    lut l = {0, NULL}; /* initialized lut */
    if (n < 0) {
        return l;
    }
    l.n = n;
    l.tab = (int *) calloc(n, sizeof(int));
    return l;
}

/**
 * @requires nothing
 * @assigns frees memory allocated for l->tab, sets l->tab to NULL, sets l->n to 0
 * @ensures l->tab is NULL and l->n is 0
 */
void clean_lut(lut * l) {
    free(l->tab);
    l->tab = NULL;
    l->n = 0;
}

/**
 * @requires not empty picture p, not empty lut l
 * @assigns allocates memory for p_copy.data
 * @ensures returns the image with the lookup table applied
 */
picture apply_lut(picture p, lut l) {
    if (is_empty_picture(p) == -1 || l.tab == NULL) {
        return create_picture(0, 0, 0);
    }
    picture p_copy = copy_picture(p);
    for (int i = 0 ; i < p.width * p.height * p.channels ; i = i + 1) {
        p_copy.data[i] = l.tab[p.data[i]];
    }
    return p_copy;
}
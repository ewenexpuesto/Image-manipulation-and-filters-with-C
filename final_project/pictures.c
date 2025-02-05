#include "pictures.h"
#include "lut.h"
#include "manage_images.h"
#include <stdio.h>

/**
 * @requires nothing
 * @assigns a copy of p
 * @ensures Returns a picture with all pixel values inverted.
 */
picture inverse_picture(picture p) {
    lut l = create_lut(MAX_BYTE + 1);
    for (int i = 0 ; i < MAX_BYTE + 1 ; i = i + 1) {
        l.tab[i] = MAX_BYTE - i;
    }
    picture p_copy = apply_lut(p, l);
    return p_copy;
}

/**
 * @requires nothing
 * @assigns a copy of p
 * @ensures Returns a picture normalized
 */
picture normalize_dynamic_picture(picture p) {
    int min = MAX_BYTE;
    int max = 0;
    for (int i = 0 ; i < p.width * p.height * p.channels ; i = i + 1) {
        if (p.data[i] < min) {
            min = p.data[i];
        }
        if (p.data[i] > max) {
            max = p.data[i];
        }
    }
    lut l = create_lut(MAX_BYTE + 1);
    if (max != min) {
        for (int i = min ; i < max + 1 ; i = i + 1) {
            l.tab[i] = (int) ((MAX_BYTE * (i - min)) / (max - min)); /* implicit conversion */
        }
    }
    picture p_copy = apply_lut(p, l);
    return p_copy;
}

/**
 * @requires nb_levels > 1
 * @assigns a copy of p
 * @ensures Returns a picture with pixel values discretized in nb_levels levels if nb_levels > 1, or an empty picture otherwise
 */
picture set_levels_picture(picture p, byte nb_levels) {
    lut l = create_lut(MAX_BYTE);
    picture p_copy;
    if (nb_levels > 1) {
        for (int i = 0 ; i < MAX_BYTE ; i = i + 1) {
            l.tab[i] = (int) ((((int) (((float) i / MAX_BYTE) * nb_levels))) * (MAX_BYTE / (nb_levels -1)));
        }
        p_copy = apply_lut(p, l);
    }
    return p_copy;
}
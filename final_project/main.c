#include "pictures.h"
#include "filename.h"
#include "read_write.h"
#include "manage_images.h"
#include "handle_pixels_directly.h"
#include "image_arithmetic.h"
#include "image_resample.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Image pre-processing */

void process_images(picture * picture_lenna_color, picture * picture_lenna_gray, picture * picture_lenna_BW) {
    * picture_lenna_color = read_picture("images/Lenna_color.ppm");
    * picture_lenna_gray = read_picture("images/Lenna_gray.pgm");
    * picture_lenna_BW = read_picture("images/Lenna_BW.pgm");
}

/* Image processing */

void process_conversion(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_convert_color = convert_to_color_picture(picture_lenna_gray);
    write_picture(lenna_gray_convert_color, "images/Lenna_gray_convert_color.ppm");
    picture lenna_color_convert_gray = convert_to_gray_picture(picture_lenna_color);
    write_picture(lenna_color_convert_gray, "images/Lenna_color_convert_gray.pgm");
    clean_picture(&lenna_gray_convert_color);
    clean_picture(&lenna_color_convert_gray);
}

void process_split(picture picture_lenna_color) {
    picture * lenna_split = split_picture(picture_lenna_color);
    write_picture(lenna_split[0], "images/Lenna_color_red.pgm");
    write_picture(lenna_split[1], "images/Lenna_color_green.pgm");
    write_picture(lenna_split[2], "images/Lenna_color_blue.pgm");
    for (int i = 0; i < 3; i++) {
        clean_picture(&lenna_split[i]);
    }
    free(lenna_split);
}

void process_brighten(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_brighten = brighten_picture(picture_lenna_gray, 1.5);
    write_picture(lenna_gray_brighten, "images/Lenna_gray_brighten.pgm");
    picture lenna_color_brighten = brighten_picture(picture_lenna_color, 1.5);
    write_picture(lenna_color_brighten, "images/Lenna_color_brighten.ppm");
    clean_picture(&lenna_gray_brighten);
    clean_picture(&lenna_color_brighten);
}

void process_melt(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_melted = melt_picture(picture_lenna_gray, picture_lenna_gray.width * picture_lenna_gray.height * picture_lenna_gray.channels * 5);
    write_picture(lenna_gray_melted, "images/Lenna_gray_melted.pgm");
    picture lenna_color_melted = melt_picture(picture_lenna_color, picture_lenna_color.width * picture_lenna_color.height * picture_lenna_color.channels * 5);
    write_picture(lenna_color_melted, "images/Lenna_color_melted.ppm");
    clean_picture(&lenna_gray_melted);
    clean_picture(&lenna_color_melted);
}

void process_inverse(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_inverse = inverse_picture(picture_lenna_gray);
    write_picture(lenna_gray_inverse, "images/Lenna_gray_inverse.pgm");
    picture lenna_color_inverse = inverse_picture(picture_lenna_color);
    write_picture(lenna_color_inverse, "images/Lenna_color_inverse.ppm");
    clean_picture(&lenna_gray_inverse);
    clean_picture(&lenna_color_inverse);
}

void process_dynamic(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_dynamic = normalize_dynamic_picture(picture_lenna_gray);
    write_picture(lenna_gray_dynamic, "images/Lenna_gray_dynamic.pgm");

    picture * lenna_color_dynamic_split = split_picture(picture_lenna_color);
    picture lenna_color_dynamic = merge_picture(normalize_dynamic_picture(lenna_color_dynamic_split[0]), normalize_dynamic_picture(lenna_color_dynamic_split[1]), normalize_dynamic_picture(lenna_color_dynamic_split[2]));
    write_picture(lenna_color_dynamic, "images/Lenna_color_dynamic.ppm");
    for (int i = 0; i < 3; i++) {
        clean_picture(&lenna_color_dynamic_split[i]);
    }
    free(lenna_color_dynamic_split);
    clean_picture(&lenna_color_dynamic);
    clean_picture(&lenna_gray_dynamic);
}

void process_levels(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_levels = set_levels_picture(picture_lenna_gray, 8);
    write_picture(lenna_gray_levels, "images/Lenna_gray_levels.pgm");
    picture lenna_color_levels = set_levels_picture(picture_lenna_color, 8);
    write_picture(lenna_color_levels, "images/Lenna_color_levels.ppm");
    clean_picture(&lenna_gray_levels);
    clean_picture(&lenna_color_levels);
}

void process_resample(picture picture_lenna_color, picture picture_lenna_gray) {
    picture lenna_gray_smaller_nearest = resample_picture_nearest(picture_lenna_gray, picture_lenna_gray.width / 1.36, picture_lenna_gray.height / 1.36);
    write_picture(lenna_gray_smaller_nearest, "images/Lenna_gray_smaller_nearest.pgm");
    picture lenna_color_smaller_nearest = resample_picture_nearest(picture_lenna_color, picture_lenna_color.width / 1.36, picture_lenna_color.height / 1.36);
    write_picture(lenna_color_smaller_nearest, "images/Lenna_color_smaller_nearest.ppm");
    clean_picture(&lenna_gray_smaller_nearest);
    clean_picture(&lenna_color_smaller_nearest);

    picture lenna_gray_smaller_bilinear = resample_picture_bilinear(picture_lenna_gray, picture_lenna_gray.width / 1.36, picture_lenna_gray.height / 1.36);
    write_picture(lenna_gray_smaller_bilinear, "images/Lenna_gray_smaller_bilinear.pgm");
    picture lenna_color_smaller_bilinear = resample_picture_bilinear(picture_lenna_color, picture_lenna_color.width / 1.36, picture_lenna_color.height / 1.36);
    write_picture(lenna_color_smaller_bilinear, "images/Lenna_color_smaller_bilinear.ppm");
    clean_picture(&lenna_gray_smaller_bilinear);
    clean_picture(&lenna_color_smaller_bilinear);

    picture lenna_gray_larger_nearest = resample_picture_nearest(picture_lenna_gray, picture_lenna_gray.width * 1.36, picture_lenna_gray.height * 1.36);
    write_picture(lenna_gray_larger_nearest, "images/Lenna_gray_larger_nearest.pgm");
    picture lenna_color_larger_nearest = resample_picture_nearest(picture_lenna_color, picture_lenna_color.width * 1.36, picture_lenna_color.height * 1.36);
    write_picture(lenna_color_larger_nearest, "images/Lenna_color_larger_nearest.ppm");
    clean_picture(&lenna_gray_larger_nearest);
    clean_picture(&lenna_color_larger_nearest);

    picture lenna_gray_larger_bilinear = resample_picture_bilinear(picture_lenna_gray, picture_lenna_gray.width * 1.36, picture_lenna_gray.height * 1.36);
    write_picture(lenna_gray_larger_bilinear, "images/Lenna_gray_larger_bilinear.pgm");
    picture lenna_color_larger_bilinear = resample_picture_bilinear(picture_lenna_color, picture_lenna_color.width * 1.36, picture_lenna_color.height * 1.36);
    write_picture(lenna_color_larger_bilinear, "images/Lenna_color_larger_bilinear.ppm");
    clean_picture(&lenna_gray_larger_bilinear);
    clean_picture(&lenna_color_larger_bilinear);
}

void process_difference(picture picture_lenna_gray_bilinear, picture picture_lenna_gray_nearest, picture picture_lenna_color_bilinear, picture picture_lenna_color_nearest) {
    picture lenna_gray_difference = normalize_dynamic_picture(picture_difference(picture_lenna_gray_bilinear, picture_lenna_gray_nearest));
    write_picture(lenna_gray_difference, "images/Lenna_gray_difference.pgm");
    picture lenna_color_difference = normalize_dynamic_picture(picture_difference(picture_lenna_color_bilinear, picture_lenna_color_nearest));
    write_picture(lenna_color_difference, "images/Lenna_color_difference.ppm");
    clean_picture(&lenna_gray_difference);
    clean_picture(&lenna_color_difference);
}

void process_product(picture picture_lenna_color, picture picture_lenna_gray, picture picture_lenna_BW) {
    picture lenna_gray_product = mult_picture(picture_lenna_gray, picture_lenna_BW);
    write_picture(lenna_gray_product, "images/Lenna_gray_product.pgm");
    picture lenna_color_product = mult_picture(picture_lenna_color, picture_lenna_BW);
    write_picture(lenna_color_product, "images/Lenna_color_product.ppm");
    clean_picture(&lenna_gray_product);
    clean_picture(&lenna_color_product);
}

void process_mixture(picture picture_lenna_color, picture picture_lenna_gray, picture picture_lenna_BW) {
    picture lenna_gray_mixture = mix_picture(picture_lenna_gray, inverse_picture(picture_lenna_gray), picture_lenna_BW);
    write_picture(lenna_gray_mixture, "images/Lenna_gray_mixture.pgm");
    picture lenna_color_mixture = mix_picture(picture_lenna_color, inverse_picture(picture_lenna_color), picture_lenna_BW);
    write_picture(lenna_color_mixture, "images/Lenna_color_mixture.ppm");
    clean_picture(&lenna_gray_mixture);
    clean_picture(&lenna_color_mixture);
}

/* Manual */

void print_usage() {
    printf("Usage: process Lenna images [options]\n");
    printf("Options:\n");
    printf("  -h, --help      Display this help message\n");
    printf("  --conversion    Process image conversion\n");
    printf("  --split         Process image split\n");
    printf("  --brighten      Process image brighten\n");
    printf("  --melt          Process image melt\n");
    printf("  --inverse       Process image inverse\n");
    printf("  --dynamic       Process image dynamic normalization\n");
    printf("  --levels        Process image levels\n");
    printf("  --resample      Process image resample\n");
    printf("  --difference    Process image difference\n");
    printf("  --product       Process image product\n");
    printf("  --mixture       Process image mixture\n");
    printf("  --all           Process all images\n");
}

/* Main */

int main(int argc, char * argv[]) {
    if (argc < 2) { /* <=> no option */
        print_usage();
        return -1;
    }

    picture picture_lenna_color, picture_lenna_gray, picture_lenna_BW;
    process_images(& picture_lenna_color, & picture_lenna_gray, & picture_lenna_BW);

    for (int i = 1 ; i < argc ; i = i + 1) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage();
            return 0;
        } else if (strcmp(argv[i], "--conversion") == 0) {
            process_conversion(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--split") == 0) {
            process_split(picture_lenna_color);
        } else if (strcmp(argv[i], "--brighten") == 0) {
            process_brighten(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--melt") == 0) {
            process_melt(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--inverse") == 0) {
            process_inverse(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--dynamic") == 0) {
            process_dynamic(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--levels") == 0) {
            process_levels(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--resample") == 0) {
            process_resample(picture_lenna_color, picture_lenna_gray);
        } else if (strcmp(argv[i], "--difference") == 0) {
            process_difference(resample_picture_bilinear(picture_lenna_gray, picture_lenna_gray.width * 1.36, picture_lenna_gray.height * 1.36), resample_picture_nearest(picture_lenna_gray, picture_lenna_gray.width * 1.36, picture_lenna_gray.height * 1.36), resample_picture_bilinear(picture_lenna_color, picture_lenna_color.width * 1.36, picture_lenna_color.height * 1.36), resample_picture_nearest(picture_lenna_color, picture_lenna_color.width * 1.36, picture_lenna_color.height * 1.36));
        } else if (strcmp(argv[i], "--product") == 0) {
            process_product(picture_lenna_color, picture_lenna_gray, picture_lenna_BW);
        } else if (strcmp(argv[i], "--mixture") == 0) {
            process_mixture(picture_lenna_color, picture_lenna_gray, picture_lenna_BW);
        } else if (strcmp(argv[i], "--all") == 0) {
            process_conversion(picture_lenna_color, picture_lenna_gray);
            process_split(picture_lenna_color);
            process_brighten(picture_lenna_color, picture_lenna_gray);
            process_melt(picture_lenna_color, picture_lenna_gray);
            process_inverse(picture_lenna_color, picture_lenna_gray);
            process_dynamic(picture_lenna_color, picture_lenna_gray);
            process_levels(picture_lenna_color, picture_lenna_gray);
            process_resample(picture_lenna_color, picture_lenna_gray);
            process_difference(resample_picture_bilinear(picture_lenna_gray, picture_lenna_gray.width * 1.36, picture_lenna_gray.height * 1.36), resample_picture_nearest(picture_lenna_gray, picture_lenna_gray.width * 1.36, picture_lenna_gray.height * 1.36), resample_picture_bilinear(picture_lenna_color, picture_lenna_color.width * 1.36, picture_lenna_color.height * 1.36), resample_picture_nearest(picture_lenna_color, picture_lenna_color.width * 1.36, picture_lenna_color.height * 1.36));
            process_product(picture_lenna_color, picture_lenna_gray, picture_lenna_BW);
            process_mixture(picture_lenna_color, picture_lenna_gray, picture_lenna_BW);
        } else {
            printf("Unknown option: %s\n", argv[i]);
            print_usage();
            return -1;
        }
    }

    clean_picture(&picture_lenna_color);
    clean_picture(&picture_lenna_gray);
    clean_picture(&picture_lenna_BW);

    return 0;
}
#include "image.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <png.h>

int fail(FILE* fp, const char* err);

int write_png(image_t* img, const char* file_name) {
  size_t x, y;
  png_structp png_ptr;
  png_infop info_ptr;
  png_byte** row_pointers;

  int depth = 8;
  int pixel_size = 3;

  /* init the file and structs */

  FILE* fp = fopen(file_name, "wb");
  if (!fp) {
    return fail(fp, "Failed to open file for writing");
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return fail(fp, "png_create_write_struct failed");
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return fail(fp, "png_create_info_struct failed");
  }

  /* setup error handling */

  if (setjmp(png_jmpbuf(png_ptr))) {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    return fail(fp, "error");
  }

  /* set image attributes */

  png_set_IHDR(png_ptr,
               info_ptr,
               img->width,
               img->height,
               depth,
               PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);

  /* init rows */

  row_pointers = png_malloc(png_ptr, sizeof(png_byte*) * img->height);
  for (y = 0; y < img->height; ++y) {
    png_byte* row = png_malloc(png_ptr, sizeof(uint8_t) * img->width * pixel_size);
    row_pointers[y] = row;
    for (x = 0; x < img->width; ++x) {
      pixel_t* pixel = pixel_at(img, x, y);
      *row++ = pixel->red;
      *row++ = pixel->green;
      *row++ = pixel->blue;
    }
  }

  /* write data to file */

  png_init_io(png_ptr, fp);
  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  /* cleanup */

  for (y = 0; y < img->height; y++) {
    png_free(png_ptr, row_pointers[y]);
  }
  png_free(png_ptr, row_pointers);

  png_destroy_write_struct(&png_ptr, &info_ptr);

  fclose(fp);
  return 0;
}

int pix(int value, int max) {
  if (value < 0) {
    return 0;
  }
  return (int)(256.0 * ((double) (value)/(double) max));
}

pixel_t* pixel_at(image_t* img, int x, int y) {
  return img->pixels + img->width * y + x;
}

int fail(FILE* fp, const char* err) {
  fprintf(stderr, "[write_png] %s", err);
  if (fp) {
    fclose(fp);
  }
  return -1;
}

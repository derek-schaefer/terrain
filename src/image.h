#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>
#include <string.h>

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} pixel_t;

typedef struct {
  pixel_t* pixels;
  size_t width;
  size_t height;
} image_t;

pixel_t* pixel_at(image_t* image, int x, int y);

int write_png(image_t* image, const char* filename);

#endif

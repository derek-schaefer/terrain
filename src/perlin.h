#ifndef _PERLIN_H
#define _PERLIN_H

#define MIN_NOISE_TOTAL (-1.0)
#define MAX_NOISE_TOTAL (1.0)

typedef struct {
  double frequency;
  double persistence;
  int octaves;
} PerlinOptions;

int noise_int(int x, int y);

double normalize(double n);

double perlin_noise(int x, int y, int seed, const PerlinOptions* options);

#endif

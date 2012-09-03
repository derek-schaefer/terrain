#include "perlin.h"

#include <math.h> /* gcc -lm */

double interpolate(double x, double y, double a) {
  double v;
  v = (1 - cos(a * M_PI)) * 0.5;
  return x * (1 - v) + y * v;
}

int noise_int(int x, int y) {
  int n;
  n = x + y * 57;
  n = (n << 13) ^ n;
  return (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
}

double noise_float(int x, int y) {
  return (1.0 - noise_int(x, y) / 1073741824.0);
}

double noise_2d(int x, int y, int seed) {
  int _x, _y;
  _x = noise_int(x, seed);
  _y = noise_int(y, seed);
  return noise_float(_x, _y);
}

double smoothe(double x, double y, int seed) {
  int _x, _y;
  double n1, n2, n3, n4;
  double i1, i2;
  _x = (int) x;
  _y = (int) y;
  n1 = noise_2d(_x, _y, seed);
  n2 = noise_2d(_x + 1, _y, seed);
  n3 = noise_2d(_x, _y + 1, seed);
  n4 = noise_2d(_x + 1, _y + 1, seed);
  i1 = interpolate(n1, n2, x - _x);
  i2 = interpolate(n3, n4, x - _x);
  return interpolate(i1, i2, y - _y);
}

double perlin_noise(int x, int y, int seed, const PerlinOptions* options) {
  int i, octaves;
  double total, frequency, persistence, amplitude;
  frequency = options->frequency;
  persistence = options->persistence;
  octaves = options->octaves;
  amplitude = 1.0 / octaves * (octaves / 2.0);
  total = 0.0;
  for (i = 0; i < octaves; i++) {
    total += smoothe(x * frequency, y * frequency, seed) * amplitude;
    frequency *= 2;
    amplitude *= persistence;
  }
  if (total < MIN_NOISE_TOTAL) {
    total = MIN_NOISE_TOTAL;
  } else if (total > MAX_NOISE_TOTAL) {
    total = MAX_NOISE_TOTAL;
  }
  return total;
}

double normalize(double n) {
  return (n + 1.0) / 2.0;
}

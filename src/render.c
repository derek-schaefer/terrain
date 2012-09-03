#include "render.h"
#include "perlin.h"
#include "biome.h"
#include "terrain.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern int MAX_X;
extern int MAX_Y;

/*
Configuration
-------------
Frequency: spacing (low = more)
Persistence: blur (low = more)
Octaves: detail (high = more)
*/

const PerlinOptions TOP_VIEW_OPTIONS = {
  0.005,
  0.75,
  8,
};

void render(char* fname, int seed) {
  biome_t biome;
  pixel_t* block;
  int x, y, moisture_seed, temperature_seed;
  double moisture, temperature;
  double temp_min, temp_max, temp_avg;
  double moisture_min, moisture_max, moisture_avg;
  image_t img;
  pixel_t* pixel;
  img.width = SIZE_X;
  img.height = SIZE_Y;
  temp_min = 0.0, temp_max = 0.0, temp_avg = 0.0;
  moisture_min = 0.0, moisture_max = 0.0, moisture_avg = 0.0;
  printf("Seed: %d\n", seed);
  img.pixels = calloc(sizeof(pixel_t), img.width * img.height);
  moisture_seed = noise_int(seed, 2938);
  temperature_seed = noise_int(seed, 7483);
  for (y = 0; y < MAX_Y; y++) {
    for (x = 0; x < MAX_X; x++) {
	  moisture = normalize(perlin_noise(x, y, moisture_seed, &TOP_VIEW_OPTIONS));
	  if (moisture < moisture_min) moisture_min = moisture;
	  if (moisture > moisture_max) moisture_max = moisture;
	  moisture_avg += moisture;
	  temperature = normalize(perlin_noise(x, y, temperature_seed, &TOP_VIEW_OPTIONS));
	  if (temperature < temp_min) temp_min = temperature;
	  if (temperature > temp_max) temp_max = temperature;
	  temp_avg += temperature;
	  biome = get_biome(moisture, temperature);
	  block = biome_generate_block(biome, moisture, temperature);
	  pixel = pixel_at(&img, x, y);
	  pixel->red = block->red;
	  pixel->green = block->green;
	  pixel->blue = block->blue;
    }
  }
  printf("Moisture min: %f\n", moisture_min);
  printf("Moisture max: %f\n", moisture_max);
  printf("Moisture avg: %f\n", moisture_avg / (MAX_X * MAX_Y));
  printf("Temp min: %f\n", temp_min);
  printf("Temp max: %f\n", temp_max);
  printf("Temp avg: %f\n", temp_avg / (MAX_X * MAX_Y));
  write_png(&img, fname);
  free(img.pixels);
}

#ifndef _BIOME_H
#define _BIOME_H

#include "image.h"

/* Biome thresholds */

#define DESERT_BIOME_MOISTURE_MIN     (0.00)
#define DESERT_BIOME_MOISTURE_MAX     (0.33)
#define DESERT_BIOME_TEMP_MIN         (0.66)
#define DESERT_BIOME_TEMP_MAX         (1.00)

#define GRASSLAND_BIOME_MOISTURE_MIN  (0.33)
#define GRASSLAND_BIOME_MOISTURE_MAX  (0.50)
#define GRASSLAND_BIOME_TEMP_MIN      (0.50)
#define GRASSLAND_BIOME_TEMP_MAX      (0.66)

#define FOREST_BIOME_MOISTURE_MIN     (0.50)
#define FOREST_BIOME_MOISTURE_MAX     (0.65)
#define FOREST_BIOME_TEMP_MIN         (0.25)
#define FOREST_BIOME_TEMP_MAX         (0.50)

#define WATER_BIOME_MOISTURE_MIN      (0.65)
#define WATER_BIOME_MOISTURE_MAX      (1.00)

#define SNOW_BIOME_TEMP_MIN           (0.00)
#define SNOW_BIOME_TEMP_MAX           (0.25)

typedef enum {
  EMPTY_BIOME,
  DESERT_BIOME,
  GRASSLAND_BIOME,
  FOREST_BIOME,
  WATER_BIOME,
  SNOW_BIOME
} biome_t;

biome_t get_biome(double moisture, double temperature);

pixel_t* biome_generate_block(biome_t biome, double moisture, double temperature);

#endif

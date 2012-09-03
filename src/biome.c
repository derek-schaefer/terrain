#include "biome.h"

#include <stdio.h>

biome_t get_biome(double moisture, double temperature) {
  if (moisture >= DESERT_BIOME_MOISTURE_MIN && /* min 0.0 */
      moisture <= DESERT_BIOME_MOISTURE_MAX && /* max 1.0 */
      temperature > DESERT_BIOME_TEMP_MIN &&
      temperature <= DESERT_BIOME_TEMP_MAX)
    return DESERT_BIOME;
  if ((moisture > GRASSLAND_BIOME_MOISTURE_MIN &&
       moisture <= GRASSLAND_BIOME_MOISTURE_MAX &&
       temperature > GRASSLAND_BIOME_TEMP_MIN) ||
      (temperature > GRASSLAND_BIOME_TEMP_MIN &&
       temperature <= GRASSLAND_BIOME_TEMP_MAX &&
       moisture < GRASSLAND_BIOME_MOISTURE_MAX))
    return GRASSLAND_BIOME;
  if ((moisture > FOREST_BIOME_MOISTURE_MIN &&
       moisture <= FOREST_BIOME_MOISTURE_MAX &&
       temperature > FOREST_BIOME_TEMP_MIN) ||
      (temperature > FOREST_BIOME_TEMP_MIN &&
       temperature <= FOREST_BIOME_TEMP_MAX &&
       moisture < FOREST_BIOME_MOISTURE_MAX))
    return FOREST_BIOME;
  if (moisture >= WATER_BIOME_MOISTURE_MIN)
    return WATER_BIOME;
  if (temperature >= SNOW_BIOME_TEMP_MIN)
    return SNOW_BIOME;
  printf("OUT OF BOUNDS!!!: %f, %f\n", moisture, temperature);
  return EMPTY_BIOME;
}

pixel_t empty_color   = {  0,   0,   0};
pixel_t sky_color     = { 51, 102, 255};
pixel_t stone_color   = {155, 155, 155};
pixel_t dirt_color    = {102,  51,   0};
pixel_t grass_color   = { 51, 102,   0};
pixel_t sand_color    = {230, 115,   0};
pixel_t water_color   = { 51, 102, 255};
pixel_t snow_color    = {255, 255, 255};
pixel_t coal_color    = {100, 100, 100};
pixel_t lava_color    = {204,   0,   0};
pixel_t diamond_color = { 51, 255, 204};

pixel_t* biome_generate_block(biome_t biome, double moisture, double temperature) {
  switch (biome) {
  case DESERT_BIOME:
    return &sand_color;
  case GRASSLAND_BIOME:
    return &dirt_color;
  case FOREST_BIOME:
    return &grass_color;
  case WATER_BIOME:
    return &water_color;
  case SNOW_BIOME:
    return &snow_color;
  default:
    return &empty_color;
  }
}

#include "render.h"
#include "terrain.h"

#include <stdlib.h>
#include <stdio.h>

int MAX_X;
int MAX_Y;

int main(int argc, char* argv[]) {
  if (argc < 4) {
    printf("Usage: terrain output_file seed size\n");
    exit(1);
  }
  MAX_Y = MAX_X = atoi(argv[3]);
  render(argv[1], atoi(argv[2]));
  return 0;
}

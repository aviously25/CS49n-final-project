#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "neopixel.h"
#include "rpi.h"
#include <stdint.h>

// stores color info
struct rgb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

// stores a location on the grid
struct Location {
  uint8_t row;
  uint8_t col;
};


/* Writes to an 8x32 grid.
Takes in a neo_t, 'row' value from 1-8, 'col' values from 1-32, and struct rgb
*/
void writeTo8x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb);

/* Writes to two 8x32 grids.
Takes in a neo_t, 'row' value from 1-16, 'col' values from 1-32, and struct rgb
*/
void writeTo16x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb);

/* UNTESTED! Writes to four 8x32 grids.
Takes in a neo_t, 'row' value from 1-32, 'col' values from 1-32, and struct rgb
*/
void writeTo32x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb);

void drawTopWall(neo_t matrix, uint8_t topLeftX, uint8_t height);
void drawBottomWall(neo_t matrix, uint8_t bottomLeftX, uint8_t height);
void drawBird(neo_t matrix, uint8_t topY);

void drawText(neo_t matrix, char *str);
#endif

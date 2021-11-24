#include "graphics.h"
#include "neopixel.h"

void writeTo8x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb) {
  assert(row <= 8 && row >= 1);
  assert(col <= 32 && col >= 1);

  if (col % 2 == 1) {
    neopix_write(matrix, 8 * (31 - (col - 1)) + (row - 1), rgb.r, rgb.g, rgb.b);
  } else {
    neopix_write(matrix, 8 * (31 - (col - 1)) + (7 - (row - 1)), rgb.r, rgb.g,
                 rgb.b);
  }
}

void writeTo16x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb) {
  assert(row <= 16 && row >= 1);
  assert(col <= 32 && col >= 1);

  // handles the 1st 8x32 matrix
  if (row <= 8) {
    if (col % 2 == 1) {
      neopix_write(matrix, 8 * (31 - (col - 1)) + (row - 1), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, 8 * (31 - (col - 1)) + (7 - (row - 1)), rgb.r, rgb.g,
                   rgb.b);
    }
  } else { // handle 2nd matrix
    if (col % 2 == 1) {
      neopix_write(matrix, (8 * (col - 1)) + 256 + (row - 9), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, (8 * (col - 1)) + 256 + (7 - (row - 9)), rgb.r,
                   rgb.g, rgb.b);
    }
  }
}

void writeTo32x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb) {
  assert(row <= 16 && row >= 1);
  assert(col <= 32 && col >= 1);

  // handles the 1st 8x32 matrix
  if (row <= 8) {
    if (col % 2 == 1) {
      neopix_write(matrix, 8 * (31 - (col - 1)) + (row - 1), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, 8 * (31 - (col - 1)) + (7 - (row - 1)), rgb.r, rgb.g,
                   rgb.b);
    }
  } else if (row <= 16) { // handle 2nd matrix
    if (col % 2 == 1) {
      neopix_write(matrix, (8 * (col - 1)) + 256 + (row - 9), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, (8 * (col - 1)) + 256 + (7 - (row - 9)), rgb.r,
                   rgb.g, rgb.b);
    }
  } else if (row <= 24) { // third matrix, should be similar logic to the first
    if (col % 2 == 1) {
      neopix_write(matrix, 8 * (31 - (col - 1)) + 512 + (row - 1), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, 8 * (31 - (col - 1)) + 512 + (7 - (row - 1)), rgb.r,
                   rgb.g, rgb.b);
    }
  } else { // fourth matrix, should be similar logic to the second one
    if (col % 2 == 1) {
      neopix_write(matrix, (8 * (col - 1)) + 768 + (row - 9), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, (8 * (col - 1)) + 768 + (7 - (row - 9)), rgb.r,
                   rgb.g, rgb.b);
    }
  }
}

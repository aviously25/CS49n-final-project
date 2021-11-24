#include "graphics.h"
#include "neopixel.h"

#define WALL_WIDTH 4

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

void drawTopWall(neo_t matrix, uint8_t topLeftX, uint8_t height) {
  assert(height >= 3);

  const struct rgb WALL = {0, 0xff, 0};

  // left edge
  for (int r = 1; r <= height - 2; r++) {
    writeTo32x32(matrix, r, topLeftX + 1, WALL);
  }
  for (int r = height - 2; r <= height; r++) {
    writeTo32x32(matrix, r, topLeftX, WALL);
  }

  // bottom edge
  for (int c = topLeftX + 1; c < topLeftX + WALL_WIDTH; c++) {
    writeTo32x32(matrix, height, c, WALL);
  }

  // right edge
  for (int r = 1; r <= height - 2; r++) {
    writeTo32x32(matrix, r, topLeftX + WALL_WIDTH - 2, WALL);
  }
  for (int r = height - 2; r <= height; r++) {
    writeTo32x32(matrix, r, topLeftX + WALL_WIDTH - 1, WALL);
  }
}

void drawBottomWall(neo_t matrix, uint8_t bottomLeftX, uint8_t height) {
  assert(height >= 3);

  const struct rgb WALL = {0, 0xff, 0};
  const int MATRIX_HEIGHT = 16;

  // left edge
  for (int r = MATRIX_HEIGHT; r > MATRIX_HEIGHT - (height - 2); r--) {
    writeTo32x32(matrix, r, bottomLeftX + 1, WALL);
  }
  for (int r = MATRIX_HEIGHT - (height - 3); r > MATRIX_HEIGHT - height; r--) {
    writeTo32x32(matrix, r, bottomLeftX, WALL);
  }

  // top edge
  for (int c = bottomLeftX + 1; c < bottomLeftX + WALL_WIDTH; c++) {
    writeTo32x32(matrix, MATRIX_HEIGHT - height + 1, c, WALL);
  }

  // right edge
  for (int r = MATRIX_HEIGHT; r > MATRIX_HEIGHT - (height - 2); r--) {
    writeTo32x32(matrix, r, bottomLeftX + WALL_WIDTH - 2, WALL);
  }
  for (int r = MATRIX_HEIGHT - (height - 3); r > MATRIX_HEIGHT - height; r--) {
    writeTo32x32(matrix, r, bottomLeftX + WALL_WIDTH - 1, WALL);
  }
}

void drawBird(neo_t matrix, uint8_t topY) {
  const struct rgb BIRD = {0xff, 0xff, 0};
  writeTo32x32(matrix, topY, 6, BIRD);
  writeTo32x32(matrix, topY + 1, 6, BIRD);
  writeTo32x32(matrix, topY + 1, 5, BIRD);
  writeTo32x32(matrix, topY + 1, 4, BIRD);
  writeTo32x32(matrix, topY + 2, 5, BIRD);
}

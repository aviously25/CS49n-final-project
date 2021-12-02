#include "graphics.h"
#include "letters.h"
#include "neopixel.h"
#include "rpi.h"
#include <stdint.h>

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
  // make sure its valid
  if (col < 1 || col > 32 || row < 1 || row > 32) {
    return;
  }

  // handles the 1st 8x32 matrix
  if (row > 0 && row <= 8) {
    if (col % 2 == 1) {
      neopix_write(matrix, 8 * (31 - (col - 1)) + (row - 1), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, 8 * (31 - (col - 1)) + (7 - (row - 1)), rgb.r, rgb.g,
                   rgb.b);
    }
  } else if (row > 8 && row <= 16) { // handle 2nd matrix
    if (col % 2 == 1) {
      neopix_write(matrix, (8 * (col - 1)) + 256 + (row - 9), rgb.r, rgb.g,
                   rgb.b);
    } else {
      neopix_write(matrix, (8 * (col - 1)) + 256 + (7 - (row - 9)), rgb.r,
                   rgb.g, rgb.b);
    }
  } else if (row > 16 &&
             row <= 24) { // third matrix, should be similar logic to the first
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

// use *col to emulate pass by reference
void drawLetter(neo_t matrix, char c, uint8_t *col) {
  const struct rgb LETTER = {0, 0, 0xff};

  printk("Char: %s, col: %d \n", &c, *col);

  switch (c) {
  case 'A':
    drawA(matrix, *col, LETTER);
    break;
  case 'B':
    drawB(matrix, *col, LETTER);
    break;
  case 'C':
    drawC(matrix, *col, LETTER);
    break;
  case 'D':
    drawD(matrix, *col, LETTER);
    break;
  case 'E':
    drawE(matrix, *col, LETTER);
    break;
  case 'F':
    drawF(matrix, *col, LETTER);
    break;
  case 'G':
    drawG(matrix, *col, LETTER);
    break;
  case 'H':
    drawH(matrix, *col, LETTER);
    break;
  case 'I':
    drawI(matrix, *col, LETTER);
    break;
  case 'J':
    drawJ(matrix, *col, LETTER);
    break;
  case 'K':
    drawK(matrix, *col, LETTER);
    break;
  case 'L':
    drawL(matrix, *col, LETTER);
    break;
  case 'M':
    drawM(matrix, *col, LETTER);
    break;
  case 'N':
    drawN(matrix, *col, LETTER);
    break;
  case 'O':
    drawO(matrix, *col, LETTER);
    break;
  case 'P':
    drawP(matrix, *col, LETTER);
    break;
  case 'Q':
    drawQ(matrix, *col, LETTER);
    break;
  case 'R':
    drawR(matrix, *col, LETTER);
    break;
  case 'S':
    drawS(matrix, *col, LETTER);
    break;
  case 'T':
    drawT(matrix, *col, LETTER);
    break;
  case 'U':
    drawU(matrix, *col, LETTER);
    break;
  case 'V':
    drawV(matrix, *col, LETTER);
    break;
  case 'W':
    drawW(matrix, *col, LETTER);
    break;
  case 'X':
    drawX(matrix, *col, LETTER);
    break;
  case 'Y':
    drawY(matrix, *col, LETTER);
    break;
  case 'Z':
    drawZ(matrix, *col, LETTER);
    break;
  case ' ':
    //*col += 2;
    break;
  default:
    break;
  }
}
void drawText(neo_t matrix, char str[]) {
  str = convLetters(str);
  int str_size = strlen(str);
  char *front = str;

  int firstCol = 28;
  uint8_t col = firstCol;

  while (1) {
    // neopix_clear(matrix);
    for (int i = 0; i < strlen(str); i++) {
      drawLetter(matrix, str[i],
                 &col); // pass in &col since the draw letter changes col
      col = col + 6;
    }

    str = front;
    firstCol--;
    printk("first col: %d\n", firstCol);
    int limit = (-6 * strlen(str));
    if (firstCol < limit) {
      firstCol = 28;
    }
    col = firstCol;
    neopix_flush(matrix);
    delay_ms(100);
  }
}

#include "graphics.h"
#include "letters.h"
#include "neopixel.h"
#include "rpi.h"
#include <stdint.h>

#define WALL_WIDTH 4

// void writeTo8x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb) {
//   assert(row <= 8 && row >= 1);
//   assert(col <= 32 && col >= 1);
//
//   if (col % 2 == 1) {
//     neopix_write(matrix, 8 * (31 - (col - 1)) + (row - 1), rgb.r, rgb.g,
//     rgb.b);
//   } else {
//     neopix_write(matrix, 8 * (31 - (col - 1)) + (7 - (row - 1)), rgb.r,
//     rgb.g,
//                  rgb.b);
//   }
// }
//
// void writeTo16x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb) {
//   assert(row <= 16 && row >= 1);
//   assert(col <= 32 && col >= 1);
//
//   // handles the 1st 8x32 matrix
//   if (row <= 8) {
//     if (col % 2 == 1) {
//       neopix_write(matrix, 8 * (31 - (col - 1)) + (row - 1), rgb.r, rgb.g,
//                    rgb.b);
//     } else {
//       neopix_write(matrix, 8 * (31 - (col - 1)) + (7 - (row - 1)), rgb.r,
//       rgb.g,
//                    rgb.b);
//     }
//   } else { // handle 2nd matrix
//     if (col % 2 == 1) {
//       neopix_write(matrix, (8 * (col - 1)) + 256 + (row - 9), rgb.r, rgb.g,
//                    rgb.b);
//     } else {
//       neopix_write(matrix, (8 * (col - 1)) + 256 + (7 - (row - 9)), rgb.r,
//                    rgb.g, rgb.b);
//     }
//   }
// }
//

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
  const struct rgb LETTER = {0xff, 0, 0xff};

  // printk("Char: %s, col: %d \n", &c, *col);

  switch (c) {
  case 'A':
    *col += drawA(matrix, *col, LETTER) + 1;
    break;
  case 'B':
    *col += drawB(matrix, *col, LETTER) + 1;
    break;
  case 'C':
    *col += drawC(matrix, *col, LETTER) + 1;
    break;
  case 'D':
    *col += drawD(matrix, *col, LETTER) + 1;
    break;
  case 'E':
    *col += drawE(matrix, *col, LETTER) + 1;
    break;
  case 'F':
    *col += drawF(matrix, *col, LETTER) + 1;
    break;
  case 'G':
    *col += drawG(matrix, *col, LETTER) + 1;
    break;
  case 'H':
    *col += drawH(matrix, *col, LETTER) + 1;
    break;
  case 'I':
    *col += drawI(matrix, *col, LETTER) + 1;
    break;
  case 'J':
    *col += drawJ(matrix, *col, LETTER) + 1;
    break;
  case 'K':
    *col += drawK(matrix, *col, LETTER) + 1;
    break;
  case 'L':
    *col += drawL(matrix, *col, LETTER) + 1;
    break;
  case 'M':
    *col += drawM(matrix, *col, LETTER) + 1;
    break;
  case 'N':
    *col += drawN(matrix, *col, LETTER) + 1;
    break;
  case 'O':
    *col += drawO(matrix, *col, LETTER) + 1;
    break;
  case 'P':
    *col += drawP(matrix, *col, LETTER) + 1;
    break;
  case 'Q':
    *col += drawQ(matrix, *col, LETTER) + 1;
    break;
  case 'R':
    *col += drawR(matrix, *col, LETTER) + 1;
    break;
  case 'S':
    *col += drawS(matrix, *col, LETTER) + 1;
    break;
  case 'T':
    *col += drawT(matrix, *col, LETTER) + 1;
    break;
  case 'U':
    *col += drawU(matrix, *col, LETTER) + 1;
    break;
  case 'V':
    *col += drawV(matrix, *col, LETTER) + 1;
    break;
  case 'W':
    *col += drawW(matrix, *col, LETTER) + 1;
    break;
  case 'X':
    *col += drawX(matrix, *col, LETTER) + 1;
    break;
  case 'Y':
    *col += drawY(matrix, *col, LETTER) + 1;
    break;
  case 'Z':
    *col += drawZ(matrix, *col, LETTER) + 1;
    break;
  case ' ':
    *col += 2;
    break;
  case '0':
    *col += draw0(matrix, *col, LETTER) + 1;
    break;
  case '1':
    *col += draw1(matrix, *col, LETTER) + 1;
    break;
  case '2':
    *col += draw2(matrix, *col, LETTER) + 1;
    break;
  case '3':
    *col += draw3(matrix, *col, LETTER) + 1;
    break;
  case '4':
    *col += draw4(matrix, *col, LETTER) + 1;
    break;
  case '5':
    *col += draw5(matrix, *col, LETTER) + 1;
    break;
  case '6':
    *col += draw6(matrix, *col, LETTER) + 1;
    break;
  case '7':
    *col += draw7(matrix, *col, LETTER) + 1;
    break;
  case '8':
    *col += draw8(matrix, *col, LETTER) + 1;
    break;
  case '9':
    *col += draw9(matrix, *col, LETTER) + 1;
    break;
  default:
    break;
  }
}
void drawScrollingText(neo_t matrix, char str[], int touch_pin) {
  // init touch sensor
  gpio_set_input(touch_pin);

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
    int limit = (-6 * strlen(str));
    if (firstCol < limit) {
      firstCol = 28;
    }
    col = firstCol;
    neopix_flush(matrix);
    delay_ms(100);

    if (gpio_read(touch_pin)) {
      break;
    }
  }
}

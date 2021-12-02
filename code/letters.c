#include "letters.h"
#include "graphics.h"
#include "neopixel.h"
#include "rpi.h"
#include <ctype.h>

char *convLetters(char str[]) {
  char *front = str;

  for (int i = 0; i < strlen(str); i++) {
    // str[i] = toupper(str[i]);
  }

  return front;
}

void drawA(neo_t h, uint8_t leftPos, struct rgb color) {
  // left line
  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos, color);
  }
  // top line
  for (int c = leftPos + 1; c < leftPos + 4; c++) {
    writeTo32x32(h, 2, c, color);
  }
  // middle line
  for (int c = leftPos + 1; c < leftPos + 4; c++) {
    writeTo32x32(h, 4, c, color);
  }
  // right line
  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 4, color);
  }
}

void drawB(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);

  for (int r = 2; r <= 3; r++)
    writeTo32x32(h, r, leftPos + 4, color);
  for (int r = 5; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawC(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawD(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 3; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}
void drawE(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawF(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  writeTo32x32(h, 2, leftPos + 4, color);
}

void drawG(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);

  writeTo32x32(h, 2, leftPos + 4, color);
  for (int r = 4; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawH(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 4, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawI(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawJ(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 2, leftPos, color);
  for (int r = 5; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);

  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 3, color);
  writeTo32x32(h, 2, leftPos + 4, color);
}

void drawK(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  for (int r = 3; r <= 5; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawL(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 6, leftPos + 1, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 3, color);
  writeTo32x32(h, 6, leftPos + 4, color);
}

void drawM(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 3, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 3, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawN(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 3, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 5, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawO(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 3; r <= 5; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 3; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawP(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  writeTo32x32(h, 3, leftPos + 4, color);
}

void drawQ(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 5; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 5; r += 3)
    writeTo32x32(h, r, leftPos + 1, color);

  for (int r = 2; r <= 5; r += 3)
    writeTo32x32(h, r, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 2, color);

  for (int r = 2; r <= 5; r += 3)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawR(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  writeTo32x32(h, 5, leftPos + 3, color);
  for (int r = 3; r <= 6; r += 3)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawS(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 4; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 6, leftPos, color);

  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);

  for (int r = 4; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
  writeTo32x32(h, 2, leftPos + 4, color);
}

void drawT(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 2, leftPos, color);
  writeTo32x32(h, 2, leftPos + 1, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 2, color);
  writeTo32x32(h, 2, leftPos + 3, color);
  writeTo32x32(h, 2, leftPos + 4, color);
}

void drawU(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 6, leftPos + 1, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawV(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 3; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 4; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 1, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  for (int r = 4; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 3; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawW(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 5; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 6; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 6; r <= 6; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 4, color);
}
void drawX(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 3; r <= 5; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  for (int r = 3; r <= 5; r += 4)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);
}

void drawY(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 2, leftPos, color);
  writeTo32x32(h, 3, leftPos, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 5, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  writeTo32x32(h, 4, leftPos + 3, color);
  writeTo32x32(h, 3, leftPos + 4, color);
  writeTo32x32(h, 2, leftPos + 4, color);
}

void drawZ(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int c = leftPos; c < leftPos + 5; c++) {
    writeTo32x32(h, 2, c, color);
  }

  writeTo32x32(h, 3, leftPos + 3, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 5, leftPos + 1, color);

  for (int c = leftPos; c < leftPos + 5; c++) {
    writeTo32x32(h, 6, c, color);
  }
}

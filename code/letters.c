#include "letters.h"
#include "graphics.h"
#include "neopixel.h"
#include "rpi.h"
#include <stdint.h>

char *convLetters(char str[]) {
  char *front = str;

  for (int i = 0; i < strlen(str); i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      str[i] = str[i] - 32;
    }
  }

  return front;
}

int drawA(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawB(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawC(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawD(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}
int drawE(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawF(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  writeTo32x32(h, 2, leftPos + 4, color);

  return 5;
}

int drawG(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawH(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 4, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawI(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawJ(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawK(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  for (int r = 3; r <= 5; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawL(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 6, leftPos + 1, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 3, color);
  writeTo32x32(h, 6, leftPos + 4, color);

  return 5;
}

int drawM(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 3, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 3, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawN(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 3, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 5, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawO(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawP(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 2, color);
  for (int r = 2; r <= 4; r += 2)
    writeTo32x32(h, r, leftPos + 3, color);
  writeTo32x32(h, 3, leftPos + 4, color);

  return 5;
}

int drawQ(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawR(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawS(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}

int drawT(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 2, leftPos, color);
  writeTo32x32(h, 2, leftPos + 1, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 2, color);
  writeTo32x32(h, 2, leftPos + 3, color);
  writeTo32x32(h, 2, leftPos + 4, color);

  return 5;
}

int drawU(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos, color);
  writeTo32x32(h, 6, leftPos + 1, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 3, color);
  for (int r = 2; r <= 6; r++)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawV(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 3; r++)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 4; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 1, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  for (int r = 4; r <= 5; r++)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 3; r++)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawW(neo_t h, uint8_t leftPos, struct rgb color) {
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

  return 5;
}
int drawX(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos, color);
  for (int r = 3; r <= 5; r += 2)
    writeTo32x32(h, r, leftPos + 1, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  for (int r = 3; r <= 5; r += 4)
    writeTo32x32(h, r, leftPos + 3, color);
  for (int r = 2; r <= 6; r += 4)
    writeTo32x32(h, r, leftPos + 4, color);

  return 5;
}

int drawY(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 2, leftPos, color);
  writeTo32x32(h, 3, leftPos, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 5, leftPos + 2, color);
  writeTo32x32(h, 6, leftPos + 2, color);
  writeTo32x32(h, 4, leftPos + 3, color);
  writeTo32x32(h, 3, leftPos + 4, color);
  writeTo32x32(h, 2, leftPos + 4, color);

  return 5;
}

int drawZ(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int c = leftPos; c < leftPos + 5; c++) {
    writeTo32x32(h, 2, c, color);
  }

  writeTo32x32(h, 3, leftPos + 3, color);
  writeTo32x32(h, 4, leftPos + 2, color);
  writeTo32x32(h, 5, leftPos + 1, color);

  for (int c = leftPos; c < leftPos + 5; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 5;
}

int draw0(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos, color);
  }

  writeTo32x32(h, 2, leftPos + 1, color);

  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 3, color);
  }

  writeTo32x32(h, 6, leftPos + 1, color);

  return 3;
}

int draw1(neo_t h, uint8_t leftPos, struct rgb color) {

  writeTo32x32(h, 3, leftPos, color);
  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 1, color);
  }
  writeTo32x32(h, 6, leftPos, color);
  writeTo32x32(h, 6, leftPos + 2, color);

  return 3;
}

int draw2(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }

  writeTo32x32(h, 3, leftPos + 2, color);
  writeTo32x32(h, 4, leftPos + 1, color);
  writeTo32x32(h, 5, leftPos + 0, color);

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 3;
}

int draw3(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }

  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 2, color);
  }

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 4, c, color);
  }

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 3;
}

int draw4(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r < 5; r++) {
    writeTo32x32(h, r, leftPos, color);
  }

  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 2, color);
  }

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 4, c, color);
  }

  return 3;
}

int draw5(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 5, leftPos + 2, color);
  writeTo32x32(h, 3, leftPos, color);

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 4, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 3;
}

int draw6(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 5, leftPos + 2, color);

  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos, color);
  }

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 4, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 3;
}

int draw7(neo_t h, uint8_t leftPos, struct rgb color) {
  writeTo32x32(h, 3, leftPos + 2, color);

  for (int r = 4; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 1, color);
  }

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }

  return 3;
}

int draw8(neo_t h, uint8_t leftPos, struct rgb color) {

  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos, color);
  }
  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 2, color);
  }

  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 4, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 3;
}

int draw9(neo_t h, uint8_t leftPos, struct rgb color) {
  for (int r = 2; r < 7; r++) {
    writeTo32x32(h, r, leftPos + 2, color);
  }
  writeTo32x32(h, 3, leftPos, color);
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 2, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 4, c, color);
  }
  for (int c = leftPos; c < leftPos + 3; c++) {
    writeTo32x32(h, 6, c, color);
  }

  return 3;
}

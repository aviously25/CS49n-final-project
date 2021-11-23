/*
 * simple test to use your buffered neopixel interface to push a cursor around
 * a light array.
 */
//#include "WS2812B.h"
#include "neopixel.h"
#include "rpi.h"

// the pin used to control the light strip.
enum { pix_pin = 21 };

// stores color info
struct rgb {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

// crude routine to write a pixel at a given location.
void place_cursor(neo_t h, int i) {
  neopix_write(h, i - 2, 0xff, 0, 0);
  neopix_write(h, i - 1, 0, 0xff, 0);
  neopix_write(h, i, 0, 0, 0xff);
  neopix_flush(h);
}

void writeTo8x32(neo_t matrix, uint8_t row, uint8_t col, struct rgb rgb) {
  assert(row <= 8 && row >= 1);
  assert(col <= 32 && col >= 1);

  if (col % 2 == 1) {
    neopix_write(matrix, 8 * (col - 1) + (row - 1), rgb.r, rgb.g, rgb.b);
  } else {
    neopix_write(matrix, 8 * (col - 1) + 7 - (row - 1), rgb.r, rgb.g, rgb.b);
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

void notmain(void) {
  kmalloc_init();
  enable_cache();
  gpio_set_output(pix_pin);

  // make sure when you implement the neopixel
  // interface works and pushes a pixel around your light
  // array.
  unsigned npixels = 512; // you'll have to figure this out.
  neo_t h = neopix_init(pix_pin, npixels);

  // does 10 increasingly faster loops.
  /*    for(int j = 0; j < 10; j++) {
          output("loop %d\n", j);
          for(int i = 0; i < npixels; i++) {
              place_cursor(h,i);
              delay_ms(10-j);
          }
      } */

  const struct rgb BLUE = {0, 0, 0xff};
  const struct rgb GREEN = {0, 0xff, 0};

  // write A
  for (int r = 4; r < 8; r++) {
    writeTo16x32(h, r, 4, BLUE);
  }
  writeTo16x32(h, 3, 5, BLUE);
  writeTo16x32(h, 2, 6, BLUE);
  writeTo16x32(h, 3, 7, BLUE);
  writeTo16x32(h, 5, 5, BLUE);
  writeTo16x32(h, 5, 6, BLUE);
  writeTo16x32(h, 5, 7, BLUE);
  for (int r = 4; r < 8; r++) {
    writeTo16x32(h, r, 8, BLUE);
  }

  // write V
  writeTo16x32(h, 4, 10, BLUE);
  writeTo16x32(h, 5, 10, BLUE);
  writeTo16x32(h, 6, 10, BLUE);
  writeTo16x32(h, 7, 11, BLUE);
  writeTo16x32(h, 6, 12, BLUE);
  writeTo16x32(h, 5, 12, BLUE);
  writeTo16x32(h, 4, 12, BLUE);

  // write i
  writeTo16x32(h, 3, 14, BLUE);
  writeTo16x32(h, 5, 14, BLUE);
  writeTo16x32(h, 6, 14, BLUE);
  writeTo16x32(h, 7, 14, BLUE);

  neopix_flush(h);

  output("done!\n");
}

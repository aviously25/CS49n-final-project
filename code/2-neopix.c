/*
 * simple test to use your buffered neopixel interface to push a cursor around
 * a light array.
 */
//#include "WS2812B.h"
// #include "graphics.h"
#include "graphics.h"
#include "letters.h"
#include "neopixel.h"
#include "rpi.h"

// the pin used to control the light strip.
enum { pix_pin = 21 };

// some common colors
const struct rgb BLUE = {0, 0, 0xff};
const struct rgb GREEN = {0, 0xff, 0};
const struct rgb RED = {0xff, 0, 0};

// crude routine to write a pixel at a given location.
void place_cursor(neo_t h, int i) {
  neopix_write(h, i - 2, 0xff, 0, 0);
  neopix_write(h, i - 1, 0, 0xff, 0);
  neopix_write(h, i, 0, 0, 0xff);
  neopix_flush(h);
}

void notmain(void) {
  kmalloc_init();
  enable_cache();
  gpio_set_output(pix_pin);

  // make sure when you implement the neopixel
  // interface works and pushes a pixel around your light
  // array.
  unsigned numPanels = 2; // you'll have to figure this out.
  neo_t h = neopix_init(pix_pin, 256 * numPanels);

  // does 10 increasingly faster loops.
  /*    for(int j = 0; j < 10; j++) {
          output("loop %d\n", j);
          for(int i = 0; i < npixels; i++) {
              place_cursor(h,i);
              delay_ms(10-j);
          }
      } */

  // write A
  // for (int r = 4; r < 8; r++) {
  //   writeTo16x32(h, r, 4, BLUE);
  // }
  // writeTo16x32(h, 3, 5, BLUE);
  // writeTo16x32(h, 2, 6, BLUE);
  // writeTo16x32(h, 3, 7, BLUE);
  // writeTo16x32(h, 5, 5, BLUE);
  // writeTo16x32(h, 5, 6, BLUE);
  // writeTo16x32(h, 5, 7, BLUE);
  // for (int r = 4; r < 8; r++) {
  //   writeTo16x32(h, r, 8, BLUE);
  // }

  // write V
  // writeTo16x32(h, 4, 10, BLUE);
  // writeTo16x32(h, 5, 10, BLUE);
  // writeTo16x32(h, 6, 10, BLUE);
  // writeTo16x32(h, 7, 11, BLUE);
  // writeTo16x32(h, 6, 12, BLUE);
  // writeTo16x32(h, 5, 12, BLUE);
  // writeTo16x32(h, 4, 12, BLUE);

  // write i
  // writeTo16x32(h, 3, 14, BLUE);
  // writeTo16x32(h, 5, 14, BLUE);
  // writeTo16x32(h, 6, 14, BLUE);
  // writeTo16x32(h, 7, 14, BLUE);

  // drawTopWall(h, 9, 5);
  // drawBottomWall(h, 9, 5);
  // drawBird(h, 8);

  // drawA(h, 8, RED);
  // writeTo32x32(h, 17, 1, RED);
  char str[6] = {'H', 'E', 'L', 'O', '\0'};
  drawText(h, str);
  neopix_flush(h);

  output("done!\n");
}

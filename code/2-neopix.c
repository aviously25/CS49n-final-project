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

  // drawTopWall(h, 9, 5);
  // drawBottomWall(h, 9, 5);
  // drawBird(h, 8);

  // drawA(h, 8, RED);
  // writeTo32x32(h, 17, 1, RED);
  char *str = "BRUH";

  // NOTE: this function is running in an infinite while loop at the moment
  drawText(h, str);
  // so nothing below this will be running

  // neopix_flush(h);

  output("done!\n");
}

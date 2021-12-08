#include "graphics.h"
#include "rpi.h"

// the pin used to control the light strip.
enum { pix_pin = 21 };

// some common colors
const struct rgb BLUE = {0, 0, 0xff};
const struct rgb GREEN = {0, 0xff, 0};
const struct rgb RED = {0xff, 0, 0};

void notmain(void) {
  kmalloc_init();
  enable_cache();
  gpio_set_output(pix_pin);

  // make sure when you implement the neopixel
  // interface works and pushes a pixel around your light
  // array.
  unsigned numPanels = 2;
  neo_t h = neopix_init(pix_pin, 256 * numPanels);
}

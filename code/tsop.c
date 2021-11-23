/* trying to send/rec */
#include "rpi.h"
#include "WS2812B.h"
#include "neopixel.h"
#include <stdio.h>
// #include "ir-tsop322.h"

enum { ir_eps = 200, pix_pin = 21, ir_pin =20 };
// we should never get this.
enum { NOISE = 0 } ;

struct readings { unsigned usec, v; };

void set_pattern(unsigned x, neo_t h) {
    output("convert an input value to a string\n");

    switch(x){
      case 233970673:
        // "UP KEY CASE" turn red
        for(int i = 0; i < h->npixel; i++){
          neopix_write(h,i,0xff,0,0);
        }
        break;
      case 217258993:
        //"DOWN" turn greed
        for(int i = 0; i < h->npixel; i++){
          neopix_write(h,i,0,0xff,0);
        }
        break;
      case 250682353:
        // ">O" turn off 
        for(int i = 0; i < h->npixel; i++){
          neopix_write(h,i,0,0,0);
        }
        break;
      case 200547313:
        // 0< : turn blue
        for(int i = 0; i < h->npixel; i++){
          neopix_write(h,i,0,0,0xff);
        }
        break;
      case 183835633:
        // X
        for(int t = 0; t < 10; t++){

          for(int i = 0; i < h->npixel; i++){
            neopix_write(h,i,0,0,0xff);
          }
          neopix_flush(h);
          delay_ms(100);
          for(int i = 0; i < h->npixel; i++){
            neopix_write(h,i,0,0xff,0);
          }
          neopix_flush(h);
          delay_ms(100);
        }
        break;
    }
}

// adapt your read_while_equal: return 0 if timeout passed, otherwise
// the number of microseconds + 1 (to prevent 0).
static int read_while_eq(int pin, int v, unsigned timeout) {
  unsigned start = timer_get_usec();

    while (gpio_read(pin) == v)
    {
        if (timer_get_usec() - start > timeout)
            return 0;
        gpio_read(pin);
    }

    return timer_get_usec()-start+1;
}

// integer absolute value.
static int abs(int x) {
    return x < 0 ? -x : x; 
}

// return 1 if <t_expect> is within eps of <t_actual>
static int within(unsigned t_expect, unsigned t_actual, unsigned eps) {
    return abs(t_expect - t_actual) < eps;
}

// return 0 if e is within eps of lb, 1 if its within eps of ub
static int pick(struct readings *e, unsigned lb, unsigned ub) {
  if(abs(e->usec - lb) < ir_eps) return 0;
  if(abs(e->usec - ub) < ir_eps) return 1;
panic("invalid time: <%d> expected %d or %d\n", e->usec, lb, ub);
}

// return 1 if is a skip: skip = delay of 550-/+eps
static int is_skip(struct readings *e) {
    return abs(e->usec - 550) < ir_eps && e->v == 0;
}

// header is a delay of 9000 and then a delay of 4500
int is_header(struct readings *r, unsigned n) {
    if(n < 2)
        return 0;

    return within(r[0].usec, 9000, ir_eps) && within(r[1].usec, 4500, ir_eps);
}

// convert <r> into an integer by or'ing in 0 or 1 depending on the time.
// assert that they are seperated by skips!
unsigned convert(struct readings *r, unsigned n) {
    if(!is_header(r,n))
        return NOISE;
    assert(n > 4);
    assert(is_skip(&r[2]));

    unsigned val = 0;
    int counter = 0;

    for(int i = 3; i < n; i++){
      if(!is_skip(&r[i])){
        int temp = pick(&r[i], 600, 1600);
        val |= (temp << counter);
        counter++;

        //printk("r[%d] usec value: [%d]", i, r[i].usec);
        //printk("picking: %d\n", temp);
      }
    }

    return val;
}

static void print_readings(struct readings *r, int n) {
    assert(n);
    printk("-------------------------------------------------------\n");
    for(int i = 0; i < n; i++) {
        if(i) 
            assert(!is_header(r+i,n-i));
        printk("\t%d: %d = %d usec\n", i, r[i].v, r[i].usec);
    }
    printk("readings=%d\n", n);
    if(!is_header(r,n))
        printk("NOISE\n");
    else
        printk("convert=%x\n", convert(r,n));
}

// read in values until we get a timeout, return the number of readings.  
static int get_readings(int in, struct readings *r, unsigned N) {
    unsigned timeout = 15000;
    int n,expect;
    for(n=expect=0; n<N; n++) {
        int usecs = read_while_eq(in, expect, timeout);

        // if timeout, return number of readings
        if(usecs == 0){
          return n-1;
        }

        // is the input pin high or low?
        r[n].v = expect;
        r[n].usec = usecs;


        expect = 1 - expect;
    }

    return n;

    panic("too many readings\n");
}

// initialize the pin.
int tsop_init(int input) {
    gpio_set_input(input);
    gpio_set_pullup(input);
    return 1;
}

void notmain(void) {

    kmalloc_init();
    enable_cache(); 
    gpio_set_output(pix_pin);

    // make sure when you implement the neopixel 
    // interface works and pushes a pixel around your light
    // array.
    unsigned npixels = 56;  // you'll have to figure this out.
    neo_t h = neopix_init(pix_pin, npixels);

    tsop_init(ir_pin);
    output("about to start reading\n");

    while(1) {
        // wait until signal: or should we timeout?
        while(gpio_read(ir_pin));
#       define N 256
        static struct readings r[N];
        int n = get_readings(ir_pin, r, N);

        output("done getting readings\n");
    
        unsigned x = convert(r,n);
        //output("converted to %x\n", x);

        //printk("%u\n", (int)x);
        set_pattern(x, h);
        neopix_flush(h);
    }
	printk("stopping ir send/rec!\n");
    clean_reboot();
}

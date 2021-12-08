#include "graphics.h"
#include "hc-sr04.h"
#include "neopixel.h"
#include "rpi.h"
#include <stdint.h>

#define DELAY 50000

// the pin used to control the light strip.
enum {
  timeout = 55000,
  pix_pin = 16,
  echo_pin1 = 21,
  trigger_pin1 = 20,
  echo_pin2 = 26,
  trigger_pin2 = 19,
  touch_input = 13
};

// some common colors
const struct rgb BLUE = {0, 0, 0xff};
const struct rgb GREEN = {0, 0xff, 0};
const struct rgb RED = {0xff, 0, 0};

typedef struct paddle {
  int x, y;
  int score;
  int len;
} paddle_t;

typedef struct ball {
  int x, y;
  int next_x, next_y;
  int x_vel, y_vel;
} ball_t;

typedef struct dimensions {
  int x, y;
} dimensions_t;

void draw_ball(neo_t h, ball_t *input);
void draw_paddle(neo_t h, paddle_t *paddle);
void draw_score(neo_t h, paddle_t *player1, paddle_t *player2,
                dimensions_t *wall);
void paddle_collisions(ball_t *inpt_ball, paddle_t *inpt_paddle);
void paddle_pos(paddle_t *paddle, char dir);

void resetPaddles(paddle_t *paddle1, paddle_t *paddle2, dimensions_t *walls);
void resetBall(ball_t *usr_ball, dimensions_t *walls);

int wall_collisions(ball_t *usr_ball, dimensions_t *walls);
int kbdhit();

// ----------------------------Main-------------------------------
void notmain(void) {
  kmalloc_init();
  enable_cache();
  gpio_set_output(pix_pin);

  // initialize sonar and touch
  hc_sr04_t inpt1 = hc_sr04_init(trigger_pin1, echo_pin1);
  hc_sr04_t inpt2 = hc_sr04_init(trigger_pin2, echo_pin2);

  // initialize led matrix
  unsigned numPanels = 4;
  neo_t h = neopix_init(pix_pin, 256 * numPanels);

  // create 32 x 24 grid for pong
  dimensions_t walls = {32, 16};

  // create paddles
  paddle_t player1 = {0};
  paddle_t player2 = {0};

  player1.x = 2;
  player1.y = 2;
  player1.len = walls.y / 4;
  player1.score = 0;

  player2.x = walls.x - 2;
  player2.y = 2;
  player2.len = walls.y / 4;
  player2.score = 0;

  // create ball
  ball_t usr_ball = {0};

  usr_ball.x = walls.x / 2;
  usr_ball.y = walls.y / 2;
  usr_ball.next_x = 0;
  usr_ball.next_y = 0;
  usr_ball.x_vel = 1;
  usr_ball.y_vel = 1;

  // main game
  unsigned player1_inpt = 2;
  unsigned player2_inpt = 2;
  int run = 1;

  while (run) {
    draw_ball(h, &usr_ball);
    draw_paddle(h, &player1);
    draw_paddle(h, &player2);
    neopix_flush(h);
    delay_us(DELAY);

    /* set next positions */
    usr_ball.next_x = usr_ball.x + usr_ball.x_vel;
    usr_ball.next_y = usr_ball.y + usr_ball.y_vel;

    // get player input (max: 47)
    player1_inpt = hc_sr04_get_distance(inpt1, timeout);
    player2_inpt = hc_sr04_get_distance(inpt2, timeout);
    // player2_inpt = getInput(2);
    player1_inpt = ((player1_inpt * 16) / 16);
    if (player1_inpt > 16) {
      player1_inpt = 16;
    }

    player2_inpt = ((player2_inpt * 16) / 16);
    if (player2_inpt > 16) {
      player2_inpt = 16;
    }
    player1.y = player1_inpt;
    player2.y = player2_inpt;

    /* check for collisions */
    paddle_collisions(&usr_ball, &player1);
    paddle_collisions(&usr_ball, &player2);
    if (wall_collisions(&usr_ball, &walls)) {
      char *game_over = "game over";
      drawScrollingText(h, game_over, 13);

      resetPaddles(&player1, &player2, &walls);
      resetBall(&usr_ball, &walls);
    }

    // draw_score(h, &player1, &walls);
  }

  clean_reboot();
}
// ---------------------------------------------------------------------------------------------

/*
 * function : wall_collisions
 * purpose  : to check for collisions on the terminal walls
 * input    : ball_t *, dimensions_t *
 * output   : nothing (stored within the structs)
 */
int wall_collisions(ball_t *usr_ball, dimensions_t *walls) {
  /* check if we're supposed to leave quick */
  if (usr_ball->next_x < 0 || usr_ball->next_x > walls->x - 1) {
    return 1;
  }

  /* check for X */
  if (usr_ball->next_x >= walls->x) {
    usr_ball->x_vel *= -1;
  } else {
    usr_ball->x += usr_ball->x_vel;
  }

  /* check for Y */
  if (usr_ball->next_y >= walls->y || usr_ball->next_y < 0) {
    usr_ball->y_vel *= -1;
  } else {
    usr_ball->y += usr_ball->y_vel;
  }

  return 0;
}

/* -------------------------------------------------------------------------- */

void paddle_collisions(ball_t *inpt_ball, paddle_t *inpt_paddle) {
  /*
   * simply check if next_% (because we set the next_x && next_y first)
   * is within the bounds of the paddle's CURRENT position
   */

  if (inpt_ball->next_x == inpt_paddle->x) {
    if (inpt_paddle->y <= inpt_ball->y &&
        inpt_ball->y <= inpt_paddle->y + inpt_paddle->len) {

      inpt_paddle->score++;
      inpt_ball->x_vel *= -1;
    }
  }

  return;
}

/* -------------------------------------------------------------------------- */

/*
 * functions : draw_ball && draw_paddle
 * purpose   : condense the drawing functions to functions
 * input     : ball_t * && paddle_t *
 * output    : void
 */
void draw_ball(neo_t h, ball_t *input) {
  writeTo32x32(h, input->y, input->x, BLUE);
  return;
}

void draw_paddle(neo_t h, paddle_t *paddle) {
  int i;

  for (i = 0; i < paddle->len; i++)
    writeTo32x32(h, paddle->y + i, paddle->x, RED);

  return;
}

void draw_score(neo_t h, paddle_t *player1, paddle_t *player2,
                dimensions_t *wall) {
  char player1_score = player1->score + '0';
  char player2_score = player2->score + '0';
  // drawScrollingText(h, score_txt);
  // char *score_txt = "Score: " + inpt_paddle->score;
  // mvprintw(0, wall->x / 2 - 7, "Score: %d", inpt_paddle->score);

  return;
}

// -------------- reset functions ------------
void resetPaddles(paddle_t *paddle1, paddle_t *paddle2, dimensions_t *walls) {
  paddle1->x = 2;
  paddle1->y = 2;
  paddle1->len = walls->y / 4;
  paddle1->score = 0;

  paddle2->x = walls->x - 2;
  paddle2->y = 2;
  paddle2->len = walls->y / 4;
  paddle2->score = 0;
}

void resetBall(ball_t *usr_ball, dimensions_t *walls) {
  usr_ball->x = walls->x / 2;
  usr_ball->y = walls->y / 2;
  usr_ball->next_x = 0;
  usr_ball->next_y = 0;
  usr_ball->x_vel = 1;
  usr_ball->y_vel = 1;
}

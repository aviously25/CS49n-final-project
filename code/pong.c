#include "gpio.h"
#include "graphics.h"
#include "hc-sr04.h"
#include "letters.h"
#include "neopixel.h"
#include "rpi.h"
#include <stdint.h>

#define DELAY 50000

// the pin used to control the light strip.
enum
{
  timeout = 55000,
  pix_pin = 16,
  echo_pin1 = 21,
  trigger_pin1 = 20,
  echo_pin2 = 26,
  trigger_pin2 = 19,
  touch_input = 13
};

// some common colors
const struct rgb BLUE = {0, 0, 200};
const struct rgb GREEN = {0, 200, 0};
const struct rgb RED = {200, 0, 0};
const struct rgb ORANGE = {200, 150, 0};
const struct rgb YELLOW = {200, 200, 0};
const struct rgb WHITE = {200, 200, 200};

typedef struct paddle
{
  int x, y;
  int score;
  int len;
} paddle_t;

typedef struct ball
{
  int x, y;
  int next_x, next_y;
  int x_vel, y_vel;
} ball_t;

typedef struct dimensions
{
  int x, y;
} dimensions_t;

void draw_ball(neo_t h, ball_t *input);
void draw_paddle(neo_t h, paddle_t *paddle);
void draw_score(neo_t h, paddle_t *player1, paddle_t *player2,
                dimensions_t *wall);
void paddle_collisions(ball_t *inpt_ball, paddle_t *paddle1, paddle_t *paddle2);
int wall_collisions(ball_t *usr_ball, dimensions_t *walls);
void paddle_pos(paddle_t *paddle, char dir);

void resetPaddles(paddle_t *paddle1, paddle_t *paddle2, dimensions_t *walls);
void resetBall(ball_t *usr_ball, dimensions_t *walls);

int getRandom();
void draw_P1(neo_t h, struct rgb color);
void draw_P2(neo_t h, struct rgb color);
void draw_bar_under_one(neo_t h);
void draw_bar_under_two(neo_t h);

int kbdhit();

// ----------------------------Main-------------------------------
void notmain(void)
{
  kmalloc_init();
  enable_cache();
  gpio_set_output(pix_pin);

  // initialize sonar and touch
  hc_sr04_t inpt1 = hc_sr04_init(trigger_pin1, echo_pin1);
  hc_sr04_t inpt2 = hc_sr04_init(trigger_pin2, echo_pin2);

  gpio_set_input(touch_input); // touch

  // initialize led matrix
  unsigned numPanels = 4;
  neo_t h = neopix_init(pix_pin, 256 * numPanels);

  // create 32 x 24 grid for pong
  dimensions_t walls = {30, 23};

  // create paddles
  paddle_t player1 = {0};
  paddle_t player2 = {0};

  resetPaddles(&player1, &player2, &walls);

  // create ball
  ball_t usr_ball = {0};
  resetBall(&usr_ball, &walls);

  // get number of players
  char *numPlayerTxt = "select number of players";
  drawScrollingText(h, numPlayerTxt, touch_input);
  draw_P1(h, BLUE);
  draw_P2(h, BLUE);
  draw_bar_under_one(h);
  int unselected = 1;
  int pIndex = 1;
  int count = 0;
  int two_players = 0;

  while (unselected)
  {
    draw_P1(h, BLUE);
    draw_P2(h, BLUE);
    // draw_bar_under_one(h);
    if (pIndex == 1)
      draw_bar_under_one(h);
    else if (pIndex == 0)
      draw_bar_under_two(h);
    if (gpio_read(touch_input))
    {
      // changing number of players
      pIndex += 1;
      pIndex = pIndex % 2;
      if (pIndex == 1)
        draw_bar_under_one(h);
      else if (pIndex == 0)
        draw_bar_under_two(h);
      // store initial color here
      struct rgb playercolor = {0, 0, 0xff};

      while (count != 8)
      {
        delay_ms(250);
        if (gpio_read(touch_input))
        { // decrease value
          if (pIndex == 0)
          {
            playercolor.r = playercolor.r / 2;
            playercolor.g = playercolor.g / 2;
            playercolor.b = playercolor.b / 2;
            draw_P1(h, playercolor);
            neopix_flush(h);
          }
          else
          {
            playercolor.r = playercolor.r / 2;
            playercolor.g = playercolor.g / 2;
            playercolor.b = playercolor.b / 2;
            draw_P2(h, playercolor);
            neopix_flush(h);
          }
          count++;
        }
        else
        {
          // reset color values to stored
          count = 0;
          break;
        }
      }
      if (count == 8)
      {
        unselected = 0;
        two_players = pIndex == 1 ? 1 : 0;
      }
    }
    neopix_flush(h);
  }

  // main game
  unsigned player1_inpt = 2;
  unsigned player2_inpt = 2;
  int run = 1;

  //
  int numSamples = 3;
  unsigned runCount = 0;
  int player1_inputs[] = {2, 2, 2};
  int player2_inputs[] = {2, 2, 2};

  // main game run
  while (run)
  {
    // draw components
    draw_ball(h, &usr_ball);
    draw_paddle(h, &player1);
    draw_paddle(h, &player2);
    draw_score(h, &player1, &player2, &walls);
    drawBorder(h, GREEN);
    neopix_flush(h);

    // check score
    if (player1.score >= 9 || player2.score >= 9)
    {
      char *game_over = "game over";
      drawScrollingText(h, game_over, 13);

      resetPaddles(&player1, &player2, &walls);
      player1.score = 0;
      player2.score = 0;
      resetBall(&usr_ball, &walls);
    }

    delay_us(DELAY / numSamples);

    /* set next positions */
    /* set next positions */

    if (runCount % numSamples == 0)
    {
      usr_ball.next_x = usr_ball.x + usr_ball.x_vel;
      usr_ball.next_y = usr_ball.y + usr_ball.y_vel;
    }

    // get player input (max: 47)
    player1_inpt = hc_sr04_get_distance(inpt1, timeout) * 24 / 12;

    if (two_players)
      player2_inpt = hc_sr04_get_distance(inpt2, timeout) * 24 / 12;
    else
    {
      if (usr_ball.next_y > walls.y - player2.len)
        player2_inpt = walls.y - player2.len;
      else if (usr_ball.next_y < 1)
        player2_inpt = 1;
      else
        player2_inpt = usr_ball.next_y;
    }

    if (player1_inpt > walls.y)
    {
      player1_inpt = walls.y - player1.len;
    }

    if (player2_inpt > walls.y)
    {
      player2_inpt = walls.y - player2.len;
    }

    player1_inputs[runCount % numSamples] = player1_inpt;
    player2_inputs[runCount % numSamples] = player2_inpt;

    if (runCount % numSamples == numSamples - 1)
    {
      int average1 = 0;
      int average2 = 0;
      for (int i = 0; i < numSamples; i++)
      {
        average1 += player1_inputs[i];
        average2 += player2_inputs[i];
      }
      average1 /= numSamples;
      average2 /= numSamples;
      player1.y = average1;
      player2.y = average2;

      /* check for collisions */
      paddle_collisions(&usr_ball, &player1, &player2);

      // check if ball hit player1's wall
      int wall_collision = wall_collisions(&usr_ball, &walls);
      if (wall_collision != 0)
      {
        // increment proper player score
        if (wall_collision == 1)
          player2.score++;
        else if (wall_collision == 2)
          player1.score++;

        resetPaddles(&player1, &player2, &walls);
        resetBall(&usr_ball, &walls);
        draw_score(h, &player1, &player2, &walls);
        delay_ms(1000);
      }

      runCount = 0;
    }
    else
    {
      runCount++;
    }
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
int wall_collisions(ball_t *usr_ball, dimensions_t *walls)
{
  // check if touched player 1's wall
  if (usr_ball->next_x < 2)
  {
    printk("wc\n");
    return 1;
  }
  else if (usr_ball->next_x > walls->x + 1)
  {
    printk("wc\n");
    return 2;
  }
  else
  {
    usr_ball->x += usr_ball->x_vel;
  }

  /* check for Y */
  if (usr_ball->next_y >= walls->y || usr_ball->next_y < 0)
  {
    printk("wc\n");
    usr_ball->y_vel *= -1;
  }
  else
  {
    usr_ball->y += usr_ball->y_vel;
  }

  return 0;
}

/* -------------------------------------------------------------------------- */

void paddle_collisions(ball_t *inpt_ball, paddle_t *paddle1, paddle_t *paddle2)
{
  /*
   * simply check if next_% (because we set the next_x && next_y first)
   * is within the bounds of the paddle's CURRENT position
   */

  // Handles paddle 1
  if (inpt_ball->next_x <= paddle1->x)
  {
    if (paddle1->y <= inpt_ball->y &&
        inpt_ball->y <= paddle1->y + paddle1->len)
    {

      // inpt_paddle->score++;
      inpt_ball->x_vel *= -1;
      printk("pc\n");
    }
  }

  // Handles paddle 2
  if (inpt_ball->next_x >= paddle2->x)
  {
    if (paddle2->y <= inpt_ball->y &&
        inpt_ball->y <= paddle2->y + paddle2->len)
    {

      // inpt_paddle->score++;
      inpt_ball->x_vel *= -1;
      printk("pc\n");
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
void draw_ball(neo_t h, ball_t *input)
{
  writeTo32x32(h, 9 + input->y, input->x, BLUE);
  return;
}

void draw_paddle(neo_t h, paddle_t *paddle)
{
  int i;

  for (i = 0; i < paddle->len; i++)
    writeTo32x32(h, 9 + paddle->y + i, paddle->x, RED);

  return;
}

void draw_score(neo_t h, paddle_t *player1, paddle_t *player2,
                dimensions_t *wall)
{
  char player1_score = player1->score + '0';
  char player2_score = player2->score + '0';
  uint8_t col = 2;
  drawLetter(h, player1_score, &col);
  drawP(h, col += 1, WHITE);
  drawO(h, col += 5, WHITE);
  drawN(h, col += 5, WHITE);
  drawG(h, col += 5, WHITE);

  col = 29;
  drawLetter(h, player2_score, &col);

  return;
}

// -------------- reset functions ------------
void resetPaddles(paddle_t *paddle1, paddle_t *paddle2, dimensions_t *walls)
{
  paddle1->x = 3;
  paddle1->y = 2;
  paddle1->len = walls->y / 4;
  // paddle1->score = 0;

  paddle2->x = walls->x;
  paddle2->y = 2;
  paddle2->len = walls->y / 4;
  // paddle2->score = 0;
}

void resetBall(ball_t *usr_ball, dimensions_t *walls)
{
  usr_ball->x = 1 + (walls->x / 2);
  usr_ball->y = walls->y / 2;
  usr_ball->next_x = 0;
  usr_ball->next_y = 0;
  usr_ball->x_vel = getRandom();
  usr_ball->y_vel = getRandom();
}

// ---------------------- MISC ----------------------
// get random int from (-1, 0, or 1)
int getRandom()
{
  int rand = rpi_rand16() % 4;
  if (rand == 0)
    return -2;
  if (rand == 1)
    return -1;
  if (rand == 2)
    return 1;

  return 2;
}

void draw_P1(neo_t h, struct rgb color)
{

  for (int i = 1; i <= 7; i++)
  {
    writeTo32x32(h, 16 + i, 10, color);
    writeTo32x32(h, 16 + 3, 8, color);
    writeTo32x32(h, 16 + 2, 9, color);
    writeTo32x32(h, 16 + 7, 8, color);
    writeTo32x32(h, 16 + 7, 9, color);
    writeTo32x32(h, 16 + 7, 10, color);
    writeTo32x32(h, 16 + 7, 11, color);
  }
}

void draw_P2(neo_t h, struct rgb color)
{

  writeTo32x32(h, 16 + 1, 20, color);
  for (int r = 4; r <= 7; r++)
    writeTo32x32(h, 16 + r, 20, color);

  for (int r = 1; r <= 7; r += 3)
    writeTo32x32(h, 16 + r, 21, color);
  for (int r = 1; r <= 7; r += 3)
    writeTo32x32(h, 16 + r, 22, color);
  for (int r = 1; r <= 7; r += 3)
    writeTo32x32(h, 16 + r, 23, color);

  for (int r = 1; r <= 4; r++)
    writeTo32x32(h, 16 + r, 24, color);
  writeTo32x32(h, 16 + 7, 24, color);
}

void draw_bar_under_one(neo_t h)
{
  struct rgb color = GREEN;
  for (int r = 1; r <= 4; r++)
    writeTo32x32(h, 16 + 9, 7 + r, color);
}

void draw_bar_under_two(neo_t h)
{
  struct rgb color = GREEN;
  for (int r = 1; r <= 5; r++)
    writeTo32x32(h, 16 + 9, 19 + r, color);
}

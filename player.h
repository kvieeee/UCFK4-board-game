/**
 * File: player.h
 * Author: Kvie Nguyen (kvn17), Zoe Sharp (zsh44)
 * Date: 5th October 2021
 * Description: This player.h file includes all function from player.c
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "navswitch.h"
#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "timer.h"
#include "tinygl.h"

typedef struct 
{
  int8_t x;
  int8_t y;
} Player_t;

/* Bitmap for level 0 maze display */
static const uint8_t maze_design_level_0[] =
{
    0x08, 0x6E, 0x08, 0x3B, 0x02
};

/* Bitmap for level 1 maze display */
static const uint8_t maze_design_level_1[] =
{
    0x00, 0x7E, 0x42, 0x56, 0x10
};

/* Bitmap for level 2 maze display */
static const uint8_t maze_design_level_2[] =
{
    0x1D, 0x46, 0x74, 0x46, 0x70
};

void player_init(Player_t *player, uint8_t size_x, uint8_t size_y);
void display_player(Player_t *player);
void player_move(Player_t *player);
bool player_reached_end (uint8_t level_counter, Player_t *player);


#endif

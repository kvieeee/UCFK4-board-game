/**
 * File: player.c
 * Author: Kvie Nguyen (kvn17), Zoe Sharp (zsh44)
 * Date: 5th October 2021
 * Description: Initialize the player, display player and get the player to move on board
*/

#include "player.h"

/* Player_init: Initialize the player */
void player_init(Player_t *player, uint8_t size_x, uint8_t size_y)
{
    /* Set the position of the player */
    player->x = size_x;
    player->y = size_y;
}

/* Display_player: Display the player using tinyg_draw_point */
void display_player(Player_t *player)
{
    /* Set the flasher variables */
    static uint8_t flasher_state = 1;
    static uint16_t flasher_counter = 0;
    
    /* Draw the player as a point on the matrix display */
    tinygl_point_t point = {player->x, player->y};
    tinygl_draw_point(point, flasher_state);
    tinygl_update();
    
    /* Increment flasher counter and check if it has reached
     specific value, then switch state and reset*/
    flasher_counter++;
    if (flasher_counter > 100) {
        flasher_state = !flasher_state;
        flasher_counter = 0;
    }
    
    
}

/* Player_move: Moving player using navswitch */
void player_move(Player_t *player)
{
    /* Check if any of the directions of the navswitch has been pressed */
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        
        /* Check if there is a wall to north of player */
        bool wall = display_pixel_get(player->x, (player->y-1));
        
        if ((player->y > 0) && (wall == 0)) {
            
            /* Move player up and clear previous postion*/
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            player->y--;
            
        } else if (wall == 1) {
            
            /* If the postion wanting to be moved to is a wall, return to start */
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            /* Set new postion to start of maze */
            player->x = 0;
            player->y = 6;
        }
    }
    if (navswitch_push_event_p(NAVSWITCH_SOUTH))
    {
        /* Check if there is a wall to south of player */
        bool wall = display_pixel_get(player->x, (player->y+1));
        
        if ((player->y < 6)&& (wall == 0)) {
            
            /* Move player down and clear previous postion*/
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            player->y++;
            
        } else if (wall == 1) {
            
            /* If the postion wanting to be moved to is a wall, return to start */
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            
            /* Set new postion to start of maze */
            player->x = 0;
            player->y = 6;
        }
    }
    if (navswitch_push_event_p(NAVSWITCH_EAST))
    {
        /* Check if there is a wall to east of player */
        bool wall = display_pixel_get((player->x+1), player->y);
        
        if ((player->x < 4) && (wall == 0)) {
            
            /* Move player left and clear previous postion*/
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            player->x++;
            
        } else if (wall == 1) {
            
            /* If the postion wanting to be moved to is a wall, return to start */
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            
            /* Set new postion to start of maze */
            player->x = 0;
            player->y = 6;
        }
    }
        
    if (navswitch_push_event_p(NAVSWITCH_WEST))
    {
        /* Check if there is a wall to west of player */
        bool wall = display_pixel_get((player->x-1), player->y);
        
        if ((player->x > 0) && (wall == 0)) {
            
            /* Move player right and clear previous postion*/
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            player->x--;
            
        } else if (wall == 1) {
            
            /* If the postion wanting to be moved to is a wall, return to start */
            tinygl_point_t point = {player->x, player->y};
            tinygl_draw_point(point, 0);
            
            /* Set new postion to start of maze */
            player->x = 0;
            player->y = 6;
        }
    }

   

}

/* Player_reached_end: Checks if player has reached endpoint of maze */
bool player_reached_end (uint8_t level_counter, Player_t *player) {
    
    /* Initalise end postions */
    uint8_t end_position_x = 0;
    uint8_t end_position_y = 0;
    
    /* Set end postions depending on what the current level is */
    if (level_counter == 0) {
        end_position_x = 0;
        end_position_y = 2;
    } else if (level_counter == 1) {
        end_position_x = 4;
        end_position_y = 6;
    } else if (level_counter == 2) {
        end_position_x = 2;
        end_position_y = 1;
    }
    
    /* If both the x and y postion fo the player is the same as the end point return true */
    if ((player->x == end_position_x) && (player->y == end_position_y)) {
        return true;
    } else {
        return false;
    }


}

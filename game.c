/**
 * File: game.c
 * Author: Kvie Nguyen (kvn17), Zoe Sharp (zsh44)
 * Date: 5th October 2021
 * Description: A maze game where player start at a point, move around to find the end point
*/

#include "navswitch.h"
#include "system.h"
#include "pio.h"
#include "pacer.h"
#include "timer.h"
#include "player.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "button.h"
#include "led.h"
#include "display.h"

#define PACER_RATE 500
#define MESSAGE_RATE 15

/** Construct Maze_t which has different types of maze and levels of game difficulty */
typedef struct 
{
    uint8_t maze;
    uint8_t level;
} Maze_t;

/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Initialise the led martix */
static void maze_display_init(void)
{
    /* Initialise LED matrix pins.  */
    // Configure columns
    pio_config_set (LEDMAT_COL1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_COL5_PIO, PIO_OUTPUT_HIGH);
    
    // Configure rows
    pio_config_set (LEDMAT_ROW1_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW2_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW3_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW4_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW5_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW6_PIO, PIO_OUTPUT_HIGH);
    pio_config_set (LEDMAT_ROW7_PIO, PIO_OUTPUT_HIGH);
}


/* Display_column: display the current column LED display */
static void display_column(uint8_t row_pattern, uint8_t current_column)
{
    static uint8_t prev_col = 0;
    pio_output_high(cols[prev_col]);
    prev_col = current_column;
    /* Go through each column and and use bitmap to turn on each specific point*/
    for (int i = 0; i < 7; i++ ) {
        if ((row_pattern >> i) & 1) {
            tinygl_point_t maze_point = {current_column, i};
            tinygl_draw_point(maze_point, i);
        }
    }
    
}

/* Maze_display_task: display the current level maze display */
static void maze_display_task(uint8_t level_counter)
{
    tinygl_update();
    for (uint8_t i = 0; i < 5; i ++) {
        /* Check what level is currently set */
        if (level_counter == 0) {
            display_column(maze_design_level_0[i], i);
        } else if (level_counter == 1) {
            display_column(maze_design_level_1[i], i);
        } else if (level_counter == 2) {
            display_column(maze_design_level_2[i], i);
        }
    
    }
    
}

/* Display_text: function to display given text */
static void display_text(char* message) {
    
    tinygl_text(message);
    
    while (1) {
        pacer_wait();
        tinygl_update();
        button_update();
        if (button_push_event_p(0)) {
            break;
        }
    }
}

/* Initalise_text: Initalise tinygl text parameters */
static void iniatlise_text(void) {
    /* set font and text */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
}

/* Level_init_display: Text to be displayed before each level starts */
static void level_init_display(uint8_t level_counter) {
    tinygl_point_t pos = {0,0};
    // Check what level is set
    if (level_counter == 0) {
        tinygl_draw_message("L1", pos, 1);
    } else if (level_counter == 1) {
        tinygl_draw_message("L2", pos, 1);
    } else if (level_counter == 2) {
        tinygl_draw_message("L3", pos, 1);
    }
    
    /* Initalise counter to display text for a specfic time */
    uint16_t display_counter = 0;
    
    /* Pacer loop to display scrolling text */
    while (1) {
        pacer_wait();
        tinygl_update();
        button_update();
        
        display_counter++;
        
        /* If button is pressed or counter reaches
         6 seconds exit function and display maze */
        if ((button_push_event_p(0)) || (display_counter > 1000) ){
            break;
        }
        
    }
}

int main(void)
{
    /* Initialize the game */
    system_init();
    maze_display_init();
    pacer_init(500);
    button_init();
    navswitch_init();
    iniatlise_text();
    
    
    
    /* Turn on led to check game is running */
    led_init();
    
    /* Inital welcome start display */
    display_text("Maze Game! Push button to start.\0");
    tinygl_clear();
    
    for (uint8_t level_counter = 0; level_counter < 3; level_counter++) {
        
        /* Display what level player is on*/
        level_init_display(level_counter);
        tinygl_clear();
        
        /* Set the player in the bottom left corner each */
        static uint8_t size_x = 0;
        static uint8_t size_y = 6;
        Player_t player = {size_x, size_y};
        player_init(&player, size_x, size_y);
        
        bool end = 0;
       
        /* Run game */
        while (!end) {
            
            pacer_wait();
            
            /* Display the player */
            display_player(&player);
            player_move(&player);
       
            /* Display the maze*/
            maze_display_task(level_counter);
            
            tinygl_update();
            navswitch_update();
            
            /* Check if the player has reached the end point */
            end = player_reached_end(level_counter, &player);

        }
        
        /* Clear the board ready for next level */
        tinygl_update();
        tinygl_clear();
        
    }

    /* End of game, display message */
    display_text("Game Over!\n");
    tinygl_clear();
    tinygl_update();
    
    
}


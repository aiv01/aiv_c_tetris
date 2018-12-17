#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// --- GAME CONFIGURATION ---

#define HORIZONTAL_CELLS 10
#define VERTICAL_CELLS 20
#define CELL_SIZE 30
#define HALF_TETRIS_MAP 5

// --------------------------

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1
#define TETRAMINI 4

#define TETRAMINI_T tetramino_t tetramini[TETRAMINI]
#define TETRAMINO_T tetramino_t *tetramino
#define TETRIS_MAP_T tetris_map_t *tetris_map

#define CELL tetris_map->cell
#define CELL_COLOR tetris_map->cell_color_id
#define WIDTH tetris_map->width
#define HEIGHT tetris_map->height
#define MAPSIZE tetris_map->width * tetris_map->height
#define ROTATION tetris_map->tetramino_current_rot
#define SHAPE_TYPE tetris_map->tetramino_type

#define TETRAMINI_SHAPES 7

#define O_SHAPE 0
#define S_SHAPE 1
#define I_SHAPE 2
#define L_SHAPE 3
#define T_SHAPE 4
#define Z_SHAPE 5
#define J_SHAPE 6

static const int tetramino_rotations[] = { 0, 2, 2, 4, 4, 2, 4 };
static const int tetramini_positions[TETRAMINI_SHAPES][4][8] = 
{
    // 0 - O SHAPE
    { 
        { 
            // X POSITION
            0, 1, 0, 1,
            // Y POSITION
            0, 0, -1, -1
        }
    },
    // 1 - S SHAPE
    { 
        // HORIZONTAL
        { 
            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 1, 1, 0
        },
        // VERTICAL
        { 
            // X POSITION
            0, 0, 1, 1,
            // Y POSITION
            0, -1, 0, 1
        }
    },
    // 2 - I SHAPE
    { 
        // HORIZONTAL
        { 
            // X POSITION
            0, -1, 1, 2,
            // Y POSITION
            0, 0, 0, 0
        },
        // VERTICAL
        { 
            // X POSITION
            0, 0, 0, 0,
            // Y POSITION
            0, -2, -1, 1
        }
    },
    // 3 - L SHAPE
    { 
        { 
            // X POSITION
            0, -1, 1, 1,
            // Y POSITION
            0, 0, 0, 1
        },
        { 
            // X POSITION
            0, 0, 0, -1,
            // Y POSITION
            0, -1, 1, 1
        },
        { 
            // X POSITION
            0, -1, -1, 1,
            // Y POSITION
            0, 0, -1, 0
        },
        { 
            // X POSITION
            0, 0, 0, 1,
            // Y POSITION
            0, 1, -1, -1
        }
    },
    // 4 - T
    { 
        { 
            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 0, -1, 0
        },
        { 
            // X POSITION
            0, 0, 0, 1,
            // Y POSITION
            0, -1, 1, 0
        },
        { 
            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 0, 1, 0
        },
        { 
            // X POSITION
            0, 0, 0, -1,
            // Y POSITION
            0, -1, 1, 0
        }
    },
    // 5 - Z VARIANT SHAPE
    { 
        // HORIZONTAL
        { 
            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 0, 1, 1
        },
        // VERTICAL
        { 
            // X POSITION
            0, 1, 1, 0,
            // Y POSITION
            0, -1, 0, 1
        }
    },
    // 6 - J SHAPE
    { 
        { 
            // X POSITION
            0, -1, -1, 1,
            // Y POSITION
            0, 0, 1, 0
        },
        { 
            // X POSITION
            0, 0, 0, -1,
            // Y POSITION
            0, -1, 1, -1
        },
        { 
            // X POSITION
            0, -1, 1, 1,
            // Y POSITION
            0, 0, -1, 0
        },
        { 
            // X POSITION
            0, 0, 0, 1,
            // Y POSITION
            0, 1, -1, 1
        }
    }
};

struct tetramino
{
    int x;
    int y;
    int color_id;
};

struct tetris_map
{
    int width;
    int height;
    int *cell;
    int tetramino_type;
    int tetramino_current_rot;
};

typedef struct tetramino tetramino_t;
typedef struct tetris_map tetris_map_t;

void tetramino_init(TETRAMINO_T, TETRIS_MAP_T);
void tetris_map_init(TETRIS_MAP_T, int width, int height);

void tetramino_draw(TETRAMINO_T, SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetramino_group_draw(TETRAMINI_T, SDL_Renderer *renderer, int size);

void tetris_row_check_fill(TETRIS_MAP_T);
void tetris_row_destroy(TETRIS_MAP_T, int row);
void tetris_collapse_down(TETRIS_MAP_T, int at_row);

int tetramini_to_map(TETRAMINI_T, TETRIS_MAP_T);

int tetramino_move_down(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_down_check(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_down_act(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_right(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_right_check(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_right_act(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_left(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_left_check(TETRAMINO_T, TETRIS_MAP_T);
int tetramino_move_left_act(TETRAMINO_T, TETRIS_MAP_T);

int tetramino_group_rotate(TETRAMINI_T, TETRIS_MAP_T);
int tetramino_group_move_down(TETRAMINI_T, TETRIS_MAP_T);
int tetramino_group_move_right(TETRAMINI_T, TETRIS_MAP_T);
int tetramino_group_move_left(TETRAMINI_T, TETRIS_MAP_T);

void tetramino_random_shape_init(TETRAMINI_T, TETRIS_MAP_T);
void tetramino_shape_init(TETRAMINI_T, TETRIS_MAP_T, int shape);

#endif

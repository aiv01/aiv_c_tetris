#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// --- GAME CONFIGURATION ---

static const int HORIZONTAL_CELLS = 10;
static const int VERTICAL_CELLS = 20;
static const int CELL_SIZE = 30;
static const int RIGHT_MENU_SIZE = 6;

static const int TETRAMINI = 4;
static const int TETRAMINI_SHAPES = 7;
static const int MAX_ROTATIONS = 4;
static const int TETRAMINI_XY = TETRAMINI * 2;

static const int O_SHAPE = 0;
static const int S_SHAPE = 1;
static const int I_SHAPE = 2;
static const int L_SHAPE = 3;
static const int T_SHAPE = 4; 
static const int Z_SHAPE = 5;
static const int J_SHAPE = 6;

static const int TETRAMINO_OK = 0;
static const int TETRAMINO_DEAD = -1;

// --------------------------

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
#define QUEUE tetris_map->tetramino_queue
#define QUEUE_ID tetris_map->tetramino_queue_id

#define LOG_INT(x) SDL_Log("%d", x);
#define LOG_POINTER(x) SDL_Log("%p", x);

// Tetramino rotations are based on the Nintendo version
// Which is the only real Tetris™ by the way

static const int tetramino_rotations[] = { 1, 2, 2, 4, 4, 2, 4 };
static const int tetramini_positions[TETRAMINI_SHAPES][MAX_ROTATIONS][TETRAMINI_XY] = 
{
    // 0 - O SHAPE
    { 
        { 
            // 2 3
            // 0 1

            // (0, 0) (1, 0)
            // (0, 1) (1, 1)

            // X POSITION
            0, 1, 0, 1,
            // Y POSITION
            1, 1, 0, 0
        }
    },
    // 1 - S SHAPE
    { 
        { 
            //   O 3
            // 1 2

            //         (0, 0) (1, 0)
            // (-1, 1) (0, 1)

            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 1, 1, 0
        },
        { 
            // 1 
            // 0 2
            //   3

            // (0, -1)
            // (0,  0) (1, 0)
            //         (1, 1)

            // X POSITION
            0, 0, 1, 1,
            // Y POSITION
            0, -1, 0, 1
        }
    },
    // 2 - I SHAPE
    { 
        { 
            // 1 0 2 3

            // (-1, 0) (0, 0) (1, 0) (2, 0)

            // X POSITION
            0, -1, 1, 2,
            // Y POSITION
            0, 0, 0, 0
        },
        { 
            // 1
            // 2
            // 0
            // 3

            // (0, -2)
            // (0, -1)
            // (0,  0)
            // (0,  1)

            // X POSITION
            0, 0, 0, 0,
            // Y POSITION
            0, -2, -1, 1
        }
    },
    // 3 - L SHAPE
    { 
        {
            // 1 0 2
            //     3

            // (-1, 0) (0, 0) (1, 0)
            //                (1, 1)

            // X POSITION
            0, -1, 1, 1,
            // Y POSITION
            0, 0, 0, 1
        },
        { 
            //   1
            //   0
            // 3 2

            //         (0, -1)
            //         (0,  0)
            // (-1, 1) (0,  1)

            // X POSITION
            0, 0, 0, -1,
            // Y POSITION
            0, -1, 1, 1
        },
        { 
            // 2
            // 1 0 2

            // (-1, -1)
            // (-1,  0) (0, 0) (1, 0)

            // X POSITION
            0, -1, -1, 1,
            // Y POSITION
            0, 0, -1, 0
        },
        {
            // 2 3
            // 0
            // 1

            // (0, -1) (1, -1)
            // (0,  0)
            // (0,  1)

            // X POSITION
            0, 0, 0, 1,
            // Y POSITION
            0, 1, -1, -1
        }
    },
    // 4 - T SHAPE
    { 
        { 
            //   2
            // 1 0 3

            //         (0, 0)
            // (-1, 1) (0, 1) (1, 1)

            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            1, 1, 0, 1
        },
        { 
            // 1
            // 0 3
            // 2

            // (0, -1)
            // (0,  0) (1, 0)
            // (0,  1)

            // X POSITION
            0, 0, 0, 1,
            // Y POSITION
            0, -1, 1, 0
        },
        { 
            // 1 0 3
            //   2

            // (-1, 0) (0, 0) (1, 0)
            //         (0, 1)

            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 0, 1, 0
        },
        { 
            //   1
            // 3 0
            //   2

            //         (0, -1)
            // (-1, 0) (0,  0)
            //         (0,  1)

            // X POSITION
            0, 0, 0, -1,
            // Y POSITION
            0, -1, 1, 0
        }
    },
    // 5 - Z SHAPE
    { 
        { 
            // 1 0
            //   2 3

            // (-1, 0) (0, 0)
            //         (0, 1) (1, 1)

            // X POSITION
            0, -1, 0, 1,
            // Y POSITION
            0, 0, 1, 1
        },
        { 
            //   1
            // 0 2
            // 3

            //        (1, -1)
            // (0, 0) (1,  0)
            // (0, 1)

            // X POSITION
            0, 1, 1, 0,
            // Y POSITION
            0, -1, 0, 1
        }
    },
    // 6 - J SHAPE
    { 
        { 
            // 1 0 3
            // 2

            // (-1, 0) (0, 0) (1, 0)
            // (-1  1)

            // X POSITION
            0, -1, -1, 1,
            // Y POSITION
            0, 0, 1, 0
        },
        { 
            // 3 1
            //   0
            //   2
            
            // (-1, -1) (0, -1)
            //          (0,  0)
            //          (0,  1)

            // X POSITION
            0, 0, 0, -1,
            // Y POSITION
            0, -1, 1, -1
        },
        { 
            //     2
            // 1 0 3

            //                (1, -1)
            // (-1, 0) (0, 0) (1,  0)

            // X POSITION
            0, -1, 1, 1,
            // Y POSITION
            0, 0, -1, 0
        },
        { 
            // 2
            // 0
            // 1 3

            // (0, -1)
            // (0,  0)
            // (0,  1) (1, 1)

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
    int *tetramino_queue;
    int tetramino_queue_id;
};

typedef struct tetramino tetramino_t;
typedef struct tetris_map tetris_map_t;

void tetramino_init(TETRAMINO_T, TETRIS_MAP_T);
void tetris_map_init(TETRIS_MAP_T, int width, int height);
void tetramini_generate_queue(int *queue);

void tetramino_draw(TETRAMINO_T, SDL_Renderer *renderer);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer);
void tetramino_group_draw(TETRAMINI_T, SDL_Renderer *renderer);

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

int tetramino_group_rotate(TETRAMINI_T, TETRIS_MAP_T, int amount);
void tetramino_group_check_rotation_bounds(TETRAMINI_T, TETRIS_MAP_T);
int tetramino_group_check_rotation_map(TETRAMINI_T, TETRIS_MAP_T, int tetramini_positions[TETRAMINI_XY]);
int tetramino_group_move_down(TETRAMINI_T, TETRIS_MAP_T);
int tetramino_group_move_right(TETRAMINI_T, TETRIS_MAP_T);
int tetramino_group_move_left(TETRAMINI_T, TETRIS_MAP_T);

void tetramino_random_shape_init(TETRAMINI_T, TETRIS_MAP_T);
void tetramino_shape_init(TETRAMINI_T, TETRIS_MAP_T, int shape);

void tetris_queue_init(TETRIS_MAP_T);
void tetris_queue_next(TETRIS_MAP_T);
void tetris_queue_swap(TETRIS_MAP_T);

static int rand_int(int n);
void shuffle_array(int *array, int n);

#endif

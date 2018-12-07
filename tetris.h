#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1
#define TETRAMINI 4

#define TETRAMINI_R tetramino_t tetramini[TETRAMINI]
#define TETRAMINO_R tetramino_t *tetramino
#define TETRIS_MAP_R tetris_map_t *tetris_map

struct tetramino
{
    int x;
    int y;
};

struct tetris_map
{
    int width;
    int height;
    int *cell;
};

typedef struct tetramino tetramino_t;
typedef struct tetris_map tetris_map_t;

void tetramino_init(TETRAMINO_R, TETRIS_MAP_R);
void tetris_map_init(TETRIS_MAP_R, int width, int height);

void tetramino_draw(TETRAMINO_R, SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetramino_group_draw(TETRAMINI_R, SDL_Renderer *renderer, int size);

void tetris_row_check_fill(TETRIS_MAP_R);
void tetris_row_destroy(TETRIS_MAP_R, int row);

int tetramini_to_map(TETRAMINI_R, TETRIS_MAP_R);

int tetramino_move_down(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_down_check(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_down_act(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_right(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_right_check(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_right_act(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_left(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_left_check(TETRAMINO_R, TETRIS_MAP_R);
int tetramino_move_left_act(TETRAMINO_R, TETRIS_MAP_R);

int tetramino_group_move_down(TETRAMINI_R, TETRIS_MAP_R);
int tetramino_group_move_right(TETRAMINI_R, TETRIS_MAP_R);
int tetramino_group_move_left(TETRAMINI_R, TETRIS_MAP_R);

void tetramino_random_shape_init(TETRAMINI_R, TETRIS_MAP_R);
void tetramino_o_shape_init(TETRAMINI_R, TETRIS_MAP_R);
void tetramino_s_shape_init(TETRAMINI_R, TETRIS_MAP_R);
void tetramino_i_shape_init(TETRAMINI_R, TETRIS_MAP_R);
void tetramino_l_shape_init(TETRAMINI_R, TETRIS_MAP_R);
void tetramino_t_shape_init(TETRAMINI_R, TETRIS_MAP_R);

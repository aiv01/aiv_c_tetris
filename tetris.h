#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1
#define TETRAMINI 4

#define TETRAMINI_T tetramino_t tetramini[TETRAMINI]
#define TETRAMINO_T tetramino_t *tetramino
#define TETRIS_MAP_T tetris_map_t *tetris_map

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
    int *cell_color_id;
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
void tetramino_o_shape_init(TETRAMINI_T, TETRIS_MAP_T);

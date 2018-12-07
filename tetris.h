#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1
#define TETRAMINI 4

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

int tetramino_move_down(tetramino_t *tetramino, tetris_map_t *tetris_map);

int tetramino_move_right(tetramino_t *tetramino, tetris_map_t *tetris_map);
int tetramino_move_right_check(tetramino_t *tetramino, tetris_map_t *tetris_map);
int tetramino_move_right_act(tetramino_t *tetramino, tetris_map_t *tetris_map);

int tetramino_move_left(tetramino_t *tetramino, tetris_map_t *tetris_map);
int tetramino_move_left_check(tetramino_t *tetramino, tetris_map_t *tetris_map);
int tetramino_move_left_act(tetramino_t *tetramino, tetris_map_t *tetris_map);

void tetramino_init(tetramino_t *tetramino, tetris_map_t *tetris_map);

void tetris_map_init(tetris_map_t *tetris_map, int width, int height);

void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetramino_group_draw(tetramino_t tetramini[TETRAMINI], SDL_Renderer *renderer, int size);

void tetris_row_check_fill(tetris_map_t *tetris_map);
void tetris_row_destroy(tetris_map_t *tetris_map, int row);

int tetramino_move_down(tetramino_t *tetramino, tetris_map_t *tetris_map);
int tetramino_move_down_check(tetramino_t *tetramino, tetris_map_t *tetris_map);
int tetramino_move_down_act(tetramino_t *tetramino, tetris_map_t *tetris_map);

int tetramino_group_move_down(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);
int tetramino_group_move_right(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);
int tetramino_group_move_left(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);

void tetramino_cube_init(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);
void tetramino_s_shape_init(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);
void tetramino_i_shape_init(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);
void tetramino_l_shape_init(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);
void tetramino_t_shape_init(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);

int tetramini_to_map(tetramino_t tetramini[TETRAMINI], tetris_map_t *tetris_map);

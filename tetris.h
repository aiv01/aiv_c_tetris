#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1
#define TETRAMINI 4

#define TETRAMINO_GROUP_REF tetramino_t tetramini[TETRAMINI]
#define TETRAMINO_REF tetramino_t *tetramino

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

int tetramino_move_down(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramino_move_right(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_right_check(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_right_act(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramino_move_left(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_left_check(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_left_act(TETRAMINO_REF, tetris_map_t *tetris_map);

void tetramino_init(TETRAMINO_REF, tetris_map_t *tetris_map);

void tetris_map_init(tetris_map_t *tetris_map, int width, int height);

void tetramino_draw(TETRAMINO_REF, SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetramino_group_draw(TETRAMINO_GROUP_REF, SDL_Renderer *renderer, int size);

void tetris_row_check_fill(tetris_map_t *tetris_map);
void tetris_row_destroy(tetris_map_t *tetris_map, int row);

int tetramino_move_down(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_down_check(TETRAMINO_REF, tetris_map_t *tetris_map);
int tetramino_move_down_act(TETRAMINO_REF, tetris_map_t *tetris_map);

int tetramino_group_move_down(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
int tetramino_group_move_right(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
int tetramino_group_move_left(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);

void tetramino_cube_init(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
void tetramino_s_shape_init(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
void tetramino_i_shape_init(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
void tetramino_l_shape_init(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);
void tetramino_t_shape_init(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);

int tetramini_to_map(TETRAMINO_GROUP_REF, tetris_map_t *tetris_map);

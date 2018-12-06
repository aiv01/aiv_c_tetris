#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define TETRAMINO_OK 0
#define TETRAMINO_DEAD -1

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

int tetramino_move_down(struct tetramino *tetramino, struct tetris_map *tetris_map);

int tetramino_move_right(struct tetramino *tetramino, struct tetris_map *tetris_map);

int tetramino_move_left(struct tetramino *tetramino, struct tetris_map *tetris_map);

void tetramino_init(struct tetramino *tetramino, struct tetris_map *tetris_map);

void tetris_map_init(struct tetris_map *tetris_map, int width, int height);

void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetris_row_check_fill(struct tetris_map *tetris_map);
void tetris_row_destroy(struct tetris_map *tetris_map, int row);

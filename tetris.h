#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

struct tetramino
{
    int y;
};

struct tetris_map
{
    int height;
    int *cell;
};

typedef struct tetramino tetramino_t;
typedef struct tetris_map tetris_map_t;

void tetramino_move_down(struct tetramino *tetramino, struct tetris_map *tetris_map);

void tetramino_init(struct tetramino *tetramino);

void tetris_map_init(struct tetris_map *tetris_map, int height);





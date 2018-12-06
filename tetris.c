#include "tetris.h"

void tetramino_init(struct tetramino *tetramino)
{
    tetramino->y = -1;
}

int tetramino_move_down(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->y + 1 >= tetris_map->height)
    {
        tetris_map->cell[tetramino->y] = 1;
        return TETRAMINO_DEAD;
    }

    if (tetris_map->cell[tetramino->y + 1] == 0)
    {
        tetramino->y += 1;
    }
    else if (tetris_map->cell[tetramino->y])
    {
        return TETRAMINO_DEAD;
    }
    else
    {
        tetris_map->cell[tetramino->y] = 1;
    }

    return TETRAMINO_OK;
}

void tetris_map_init(struct tetris_map *tetris_map, int height)
{
    int size = sizeof(int) * height;

    tetris_map->cell = malloc(size);
    memset(tetris_map->cell, 0, size);
    tetris_map->height = height;
}
#include "tetris.h"

void tetramino_init(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

int tetramino_move_all_down(struct tetramino tetramini[4], struct tetris_map *tetris_map)
{
    // TODO split tetramino_move_down in check/move
    int i;
    // first check
    int can_move = 1;
    for (i = 0; i < 4; i++)
    {
        // check
    }

    // TODO check for DEAD
    if (!can_move)
        return TETRAMINO_OK;

    for (i = 0; i < 4; i++)
    {
        // move
    }

    return TETRAMINO_OK;
}

int tetramino_move_down(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;
    if (tetramino->y + 1 >= tetris_map->height)
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    if (tetris_map->cell[next_index] == 0)
    {
        tetramino->y += 1;
    }
    else
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    return TETRAMINO_OK;
}

int tetramino_move_right(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->x >= tetris_map->width - 1)
    {
        return TETRAMINO_OK;
    }

    int right_index = tetris_map->width * tetramino->y + (tetramino->x + 1);
    if (!tetris_map->cell[right_index])
    {
        tetramino->x++;
    }

    return TETRAMINO_OK;
}

int tetramino_move_left(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    if (tetramino->x <= 0)
    {
        return TETRAMINO_OK;       
    }

    tetramino->x--;
    
    return TETRAMINO_OK;
}

void tetris_map_init(struct tetris_map *tetris_map, int width, int height)
{
    int size = sizeof(int) * width * height;

    tetris_map->cell = malloc(size);
    memset(tetris_map->cell, 0, size);
    tetris_map->width = width;
    tetris_map->height = height;
}
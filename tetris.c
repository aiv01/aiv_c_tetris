#include "tetris.h"

void tetramino_init(struct tetramino *tetramino, struct tetris_map *tetris_map)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

void tetramino_cube_init(tetramino_t tetramini[4], struct tetris_map *tetris_map)
{
    tetramini[0].x = 0;
    tetramini[0].y = 0;

    tetramini[1].x = 1;
    tetramini[1].y = 0;

    tetramini[2].x = 0;
    tetramini[2].y = 1;

    tetramini[3].x = 1;
    tetramini[3].y = 1;
}

int tetramino_group_move_down(struct tetramino tetramini[4], struct tetris_map *tetris_map)
{
    // TODO split tetramino_move_down in check/move
    int i;
    // first check
    int can_move = 1;
    for (i = 0; i < 4; i++)
    {
        if(!tetramino_move_down_check(&tetramini[i], tetris_map))
            can_move = 0;
    }

    // TODO check for DEAD
    if (!can_move)
        return TETRAMINO_OK;

    for (i = 0; i < 4; i++)
    {
        tetramino_move_down_act(&tetramini[i], tetris_map);
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

    tetris_row_check_fill(tetris_map);

    return TETRAMINO_OK;
}

int tetramino_move_down_check(tetramino_t *tetramino, struct tetris_map *tetris_map)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    // int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= tetris_map->height)
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    return TETRAMINO_OK;
}

int tetramino_move_down_act(tetramino_t *tetramino, struct tetris_map *tetris_map)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetris_map->cell[next_index] == 0)
    {
        tetramino->y += 1;
    }
    else
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    tetris_row_check_fill(tetris_map);

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

void tetris_row_check_fill(struct tetris_map *tetris_map)
{
    int row;
    int column;

    // For each row of the Tetris map
    for (row = 0; row < tetris_map->height; row++)
    {   
        int tetramini = 0;
        for (column = 0; column < tetris_map->width; column++)
        {
            // We count how many tetramini are in the row
            if (tetris_map->cell[(row * tetris_map->width) + column] == 1)
                tetramini += 1;
        }
        // SDL_Log("row %d has %d\n tetramini", row, tetramini);
        
        if (tetramini >= tetris_map->width)
            tetris_row_destroy(tetris_map, row);
    }
}

void tetris_row_destroy(struct tetris_map *tetris_map, int row)
{
    int row_index = tetris_map->width * row;

    int i;
    for (i = row_index; i < (row_index + tetris_map->width); i++)
        tetris_map->cell[i] = 0;
}

void tetris_collapse_down(struct tetris_map *tetris_map, int at_row)
{
    // int row_index 
}

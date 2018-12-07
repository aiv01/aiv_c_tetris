#include "tetris.h"
#include <stdio.h>

void tetramino_init(TETRAMINO_R, TETRIS_MAP_R)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

void tetramino_random_shape_init(TETRAMINI_R, TETRIS_MAP_R)
{
    int random_piece = rand() % 5;

    switch (random_piece)
    {
        case 0:
            tetramino_o_shape_init(tetramini, tetris_map);
            break;
        case 1:
            tetramino_s_shape_init(tetramini, tetris_map);
            break;
        case 2:
            tetramino_i_shape_init(tetramini, tetris_map);
            break;
        case 3:
            tetramino_l_shape_init(tetramini, tetris_map);
            break;
        case 4:
            tetramino_t_shape_init(tetramini, tetris_map);
            break;
    }
}

void tetramino_o_shape_init(TETRAMINI_R, TETRIS_MAP_R)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 1;
    tetramini[0].y = 0;

    tetramini[1].x = half_screen;
    tetramini[1].y = 0;

    tetramini[2].x = half_screen - 1;
    tetramini[2].y = 1;

    tetramini[3].x = half_screen;
    tetramini[3].y = 1;
}

void tetramino_s_shape_init(TETRAMINI_R, TETRIS_MAP_R)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 1;
    tetramini[0].y = 0;

    tetramini[1].x = half_screen;
    tetramini[1].y = 0;

    tetramini[2].x = half_screen;
    tetramini[2].y = 1;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 1;
}

void tetramino_i_shape_init(TETRAMINI_R, TETRIS_MAP_R)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 2;
    tetramini[0].y = 0;

    tetramini[1].x = half_screen - 1;
    tetramini[1].y = 0;

    tetramini[2].x = half_screen;
    tetramini[2].y = 0;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 0;
}

void tetramino_l_shape_init(TETRAMINI_R, TETRIS_MAP_R)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen;
    tetramini[0].y = 0;

    tetramini[1].x = half_screen;
    tetramini[1].y = 1;

    tetramini[2].x = half_screen;
    tetramini[2].y = 2;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 2;
}

void tetramino_t_shape_init(TETRAMINI_R, TETRIS_MAP_R)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 1;
    tetramini[0].y = 1;

    tetramini[1].x = half_screen;
    tetramini[1].y = 1;

    tetramini[2].x = half_screen;
    tetramini[2].y = 0;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 1;
}

int tetramino_group_move_down(TETRAMINI_R, TETRIS_MAP_R)
{
    for (int i = 0; i < TETRAMINI; i++)
    {
        if (tetramino_move_down_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
        {
            tetramini_to_map(tetramini, tetris_map);
            return TETRAMINO_DEAD;
        }
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramino_move_down_act(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_group_move_right(TETRAMINI_R, TETRIS_MAP_R)
{
    for (int i = 0; i < TETRAMINI; i++)
    {
        if (tetramino_move_right_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
            return TETRAMINO_DEAD;
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramino_move_right_act(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_group_move_left(TETRAMINI_R, TETRIS_MAP_R)
{
    for (int i = 0; i < TETRAMINI; i++)
    {
        if (tetramino_move_left_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
            return TETRAMINO_DEAD;
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramino_move_left_act(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_move_down(TETRAMINO_R, TETRIS_MAP_R)
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

int tetramino_move_down_check(TETRAMINO_R, TETRIS_MAP_R)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= tetris_map->height)
    {
        tetris_map->cell[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    if (tetris_map->cell[next_index] == 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_down_act(TETRAMINO_R, TETRIS_MAP_R)
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

int tetramini_to_map(TETRAMINI_R, TETRIS_MAP_R)
{
    int current_index;
    int next_index;

    for (int i = 0; i < TETRAMINI; i++)
    {
        current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;
        next_index = tetris_map->width * (tetramini[i].y + 1) + tetramini[i].x;
        tetris_map->cell[current_index] = 1;
    }

    return TETRAMINO_DEAD;
}

int tetramino_move_right(TETRAMINO_R, TETRIS_MAP_R)
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

int tetramino_move_right_check(TETRAMINO_R, TETRIS_MAP_R)
{
    if (tetramino->x >= tetris_map->width - 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_right_act(TETRAMINO_R, TETRIS_MAP_R)
{
    int right_index = tetris_map->width * tetramino->y + (tetramino->x + 1);
    if (!tetris_map->cell[right_index])
    {
        tetramino->x++;
    }

    return TETRAMINO_OK;
}

int tetramino_move_left(TETRAMINO_R, TETRIS_MAP_R)
{
    if (tetramino->x <= 0)
    {
        return TETRAMINO_OK;
    }

    tetramino->x--;

    return TETRAMINO_OK;
}

int tetramino_move_left_check(TETRAMINO_R, TETRIS_MAP_R)
{
    if (tetramino->x <= 0)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_left_act(TETRAMINO_R, TETRIS_MAP_R)
{
    tetramino->x--;
    return TETRAMINO_OK;
}

void tetris_map_init(TETRIS_MAP_R, int width, int height)
{
    int size = sizeof(int) * width * height;

    tetris_map->cell = malloc(size);
    memset(tetris_map->cell, 0, size);
    tetris_map->width = width;
    tetris_map->height = height;
}

void tetris_row_check_fill(TETRIS_MAP_R)
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

void tetris_row_destroy(TETRIS_MAP_R, int row)
{
    int row_index = tetris_map->width * row;

    int i;
    for (i = row_index; i < (row_index + tetris_map->width); i++)
        tetris_map->cell[i] = 0;
}

void tetris_collapse_down(TETRIS_MAP_R, int at_row)
{
    
}

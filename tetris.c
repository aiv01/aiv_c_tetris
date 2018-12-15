#include "tetris.h"
#include <stdio.h>

void tetramino_init(TETRAMINO_T, TETRIS_MAP_T)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

void tetramino_random_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    // 0 - O - OK
    // 1 - S - MMH
    // 2 - I - OK
    // 3 - L - OK
    // 4 - T - OK

    int random = rand() % TETRAMINI_SHAPES;

    SHAPE_TYPE = 5;
    ROTATION = 0;

    tetramino_shape_init(tetramini, tetris_map, SHAPE_TYPE);
}

void tetramino_shape_init(TETRAMINI_T, TETRIS_MAP_T, int shape)
{
    int half_screen = tetris_map->width / 2;
    
    for (int i = 0; i < TETRAMINI; i++)
    {
        tetramini[i].x = -1 + tetramini_positions[shape][ROTATION][i] + half_screen;
        tetramini[i].y = +1 + tetramini_positions[shape][ROTATION][i+4];
        tetramini[i].color_id = SHAPE_TYPE + 1;
    }
}

int tetramino_group_rotate(TETRAMINI_T, TETRIS_MAP_T)
{
    if (ROTATION >= tetramino_rotations[SHAPE_TYPE] - 1)
        ROTATION = 0;
    else
        ROTATION++;

    int previous_x = tetramini[0].x;
    int previous_y = tetramini[0].y;
    

    for (int i = 0; i < 4; i++)
    {
        tetramini[i].x = previous_x + (int)tetramini_positions[SHAPE_TYPE][ROTATION][i];
        tetramini[i].y = previous_y + (int)tetramini_positions[SHAPE_TYPE][ROTATION][i + 4];
    }
}

int tetramino_group_move_down(TETRAMINI_T, TETRIS_MAP_T)
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

int tetramino_group_move_right(TETRAMINI_T, TETRIS_MAP_T)
{
    int current_index;

    for (int i = 0; i < TETRAMINI; i++)
    {
        if (tetramino_move_right_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
            return TETRAMINO_DEAD;

        current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;

        if (CELL[current_index + 1] >= 1)
            return TETRAMINO_OK;
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramino_move_right_act(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_group_move_left(TETRAMINI_T, TETRIS_MAP_T)
{
    int current_index;

    for (int i = 0; i < TETRAMINI; i++)
    {
        if (tetramino_move_left_check(&tetramini[i], tetris_map) == TETRAMINO_DEAD)
            return TETRAMINO_DEAD;

        current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;

        if (CELL[current_index - 1] >= 1)
            return TETRAMINO_OK;
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramino_move_left_act(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_move_down(TETRAMINO_T, TETRIS_MAP_T)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= tetris_map->height)
    {
        CELL[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    if (CELL[next_index] == 0)
    {
        tetramino->y += 1;
    }
    else
    {
        CELL[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    tetris_row_check_fill(tetris_map);

    return TETRAMINO_OK;
}

int tetramino_move_down_check(TETRAMINO_T, TETRIS_MAP_T)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= tetris_map->height)
    {
        CELL[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    if (CELL[next_index] >= 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_down_act(TETRAMINO_T, TETRIS_MAP_T)
{
    int current_index = tetris_map->width * tetramino->y + tetramino->x;
    int next_index = tetris_map->width * (tetramino->y + 1) + tetramino->x;

    if (CELL[next_index] == 0)
    {
        tetramino->y += 1;
    }
    else
    {
        CELL[current_index] = 1;
        return TETRAMINO_DEAD;
    }

    tetris_row_check_fill(tetris_map);

    return TETRAMINO_OK;
}

int tetramini_to_map(TETRAMINI_T, TETRIS_MAP_T)
{
    int current_index;
    int next_index;

    for (int i = 0; i < TETRAMINI; i++)
    {
        current_index = tetris_map->width * tetramini[i].y + tetramini[i].x;
        next_index = tetris_map->width * (tetramini[i].y + 1) + tetramini[i].x;
        CELL[current_index] = tetramini[i].color_id;
    }

    return TETRAMINO_DEAD;
}

int tetramino_move_right(TETRAMINO_T, TETRIS_MAP_T)
{
    if (tetramino->x >= tetris_map->width - 1)
    {
        return TETRAMINO_OK;
    }

    int right_index = tetris_map->width * tetramino->y + (tetramino->x + 1);
    if (!CELL[right_index])
    {
        tetramino->x++;
    }

    return TETRAMINO_OK;
}

int tetramino_move_right_check(TETRAMINO_T, TETRIS_MAP_T)
{
    if (tetramino->x >= tetris_map->width - 1)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_right_act(TETRAMINO_T, TETRIS_MAP_T)
{
    tetramino->x++;
    return TETRAMINO_OK;
}

int tetramino_move_left(TETRAMINO_T, TETRIS_MAP_T)
{
    if (tetramino->x <= 0)
    {
        return TETRAMINO_OK;
    }

    tetramino->x--;

    return TETRAMINO_OK;
}

int tetramino_move_left_check(TETRAMINO_T, TETRIS_MAP_T)
{
    if (tetramino->x <= 0)
        return TETRAMINO_DEAD;

    return TETRAMINO_OK;
}

int tetramino_move_left_act(TETRAMINO_T, TETRIS_MAP_T)
{
    tetramino->x--;
    return TETRAMINO_OK;
}

void tetris_map_init(TETRIS_MAP_T, int width, int height)
{
    int size = sizeof(int) * width * height;

    CELL = malloc(size);
    memset(CELL, 0, size);

    tetris_map->width = width;
    tetris_map->height = height;
}

void tetris_row_check_fill(TETRIS_MAP_T)
{
    int row;
    int column;

    // For each row of the Tetris map
    for (row = HEIGHT; row >= 0; row--)
    {
        int tetramini = 0;
        for (column = 0; column < tetris_map->width; column++)
        {
            // We count how many tetramini are in the row
            if (CELL[(row * tetris_map->width) + column] >= 1)
                tetramini += 1;
        }

        if (tetramini >= tetris_map->width)
            tetris_row_destroy(tetris_map, row);
    }
}

void tetris_row_destroy(TETRIS_MAP_T, int row)
{
    // Move down all the cells
    memmove
    (
        CELL + WIDTH, 
        CELL, 
        sizeof(int) * (WIDTH * row)
    );
    memset(CELL + WIDTH, 0, sizeof(int) * WIDTH);
}

#include "tetris.h"
#include <stdio.h>

#define CELL tetris_map->cell
#define CELL_COLOR tetris_map->cell_color_id
#define WIDTH tetris_map->width
#define HEIGHT tetris_map->height
#define MAPSIZE tetris_map->width * tetris_map->height

void tetramino_init(TETRAMINO_T, TETRIS_MAP_T)
{
    tetramino->x = tetris_map->width / 2;
    tetramino->y = -1;
}

void tetramino_random_shape_init(TETRAMINI_T, TETRIS_MAP_T)
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

    // tetramino_o_shape_init(tetramini, tetris_map);
}

void tetramino_o_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 1;
    tetramini[0].y = 0;
    tetramini[0].color_id = 0;

    tetramini[1].x = half_screen;
    tetramini[1].y = 0;
    tetramini[1].color_id = 0;

    tetramini[2].x = half_screen - 1;
    tetramini[2].y = 1;
    tetramini[2].color_id = 0;

    tetramini[3].x = half_screen;
    tetramini[3].y = 1;
    tetramini[3].color_id = 0;
}

void tetramino_s_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 1;
    tetramini[0].y = 0;
    tetramini[0].color_id = 1;

    tetramini[1].x = half_screen;
    tetramini[1].y = 0;
    tetramini[1].color_id = 1;

    tetramini[2].x = half_screen;
    tetramini[2].y = 1;
    tetramini[2].color_id = 1;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 1;
    tetramini[3].color_id = 1;
}

void tetramino_i_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 2;
    tetramini[0].y = 0;
    tetramini[0].color_id = 2;

    tetramini[1].x = half_screen - 1;
    tetramini[1].y = 0;
    tetramini[1].color_id = 2;

    tetramini[2].x = half_screen;
    tetramini[2].y = 0;
    tetramini[2].color_id = 2;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 0;
    tetramini[3].color_id = 2;
}

void tetramino_l_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen;
    tetramini[0].y = 0;
    tetramini[0].color_id = 3;

    tetramini[1].x = half_screen;
    tetramini[1].y = 1;
    tetramini[1].color_id = 3;

    tetramini[2].x = half_screen;
    tetramini[2].y = 2;
    tetramini[2].color_id = 3;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 2;
    tetramini[3].color_id = 3;
}

void tetramino_t_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    int half_screen = tetris_map->width / 2;

    tetramini[0].x = half_screen - 1;
    tetramini[0].y = 1;
    tetramini[0].color_id = 4;

    tetramini[1].x = half_screen;
    tetramini[1].y = 1;
    tetramini[1].color_id = 4;

    tetramini[2].x = half_screen;
    tetramini[2].y = 0;
    tetramini[2].color_id = 4;

    tetramini[3].x = half_screen + 1;
    tetramini[3].y = 1;
    tetramini[3].color_id = 4;
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

        if (CELL[current_index + 1] == 1)
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

        if (CELL[current_index - 1] == 1)
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

    if (CELL[next_index] == 1)
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
        CELL[current_index] = 1;
        CELL_COLOR[current_index] = tetramini[i].color_id;
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

    CELL_COLOR = malloc(size);
    memset(CELL_COLOR, 0, size);

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
            if (CELL[(row * tetris_map->width) + column] == 1)
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
    // Move down all the color cells
    memmove
    (
        CELL_COLOR + WIDTH, 
        CELL_COLOR, 
        sizeof(int) * (WIDTH * row)
    );
    memset(CELL_COLOR + WIDTH, 0, sizeof(int) * WIDTH);
}

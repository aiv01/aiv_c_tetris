#include "tetris.h"
#include <stdio.h>

void tetramino_init(TETRAMINO_T, TETRIS_MAP_T)
{
    tetramino->x = WIDTH / 2;
    tetramino->y = -1;
}

void tetramino_random_shape_init(TETRAMINI_T, TETRIS_MAP_T)
{
    SHAPE_TYPE = T_SHAPE;

    ROTATION = 0;

    tetramino_shape_init(tetramini, tetris_map, SHAPE_TYPE);

    tetris_queue_next(tetris_map);
}

void tetramino_shape_init(TETRAMINI_T, TETRIS_MAP_T, int shape)
{
    for (int i = 0; i < TETRAMINI; i++)
    {
        tetramini[i].x = -1 + tetramini_positions[shape][ROTATION][i] + WIDTH / 2;
        tetramini[i].y = +1 + tetramini_positions[shape][ROTATION][i + 4];
        tetramini[i].color_id = SHAPE_TYPE + 1;
    }
}

int tetramino_group_rotate(TETRAMINI_T, TETRIS_MAP_T)
{
    ROTATION++;
    ROTATION %= tetramino_rotations[SHAPE_TYPE];

    if (tetramino_group_check_rotation_map(tetramini, tetris_map, (int *)tetramini_positions[SHAPE_TYPE][ROTATION]) == TETRAMINO_DEAD)
    {
        ROTATION--;
        return 0;
    }

    int previous_x = tetramini[0].x;
    int previous_y = tetramini[0].y;

    for (int i = 0; i < 4; i++)
    {
        tetramini[i].x = previous_x + (int)tetramini_positions[SHAPE_TYPE][ROTATION][i];
        tetramini[i].y = previous_y + (int)tetramini_positions[SHAPE_TYPE][ROTATION][i + 4];
    }

    tetramino_group_check_rotation_bounds(tetramini, tetris_map);

    return 1;
}

int tetramino_group_check_rotation_map(TETRAMINI_T, TETRIS_MAP_T, int tetramini_positions[TETRAMINI_XY])
{
    int current_row;
    int current_column;
    int current_index;

    for (int i = 0; i < TETRAMINI; i++)
    {
        current_row = tetramini[i].x;
        current_column = tetramini[i].y;

        current_row += tetramini_positions[i];
        current_column += tetramini_positions[i + 4];

        current_index = WIDTH * current_column + current_row;

        if (CELL[current_index] > 0)
            return TETRAMINO_DEAD;
    }

    return TETRAMINO_OK;
}

void tetramino_group_check_rotation_bounds(TETRAMINI_T, TETRIS_MAP_T)
{
    int horizontal_sweep = 0;

    for (int i = 0; i < TETRAMINI; i++)
    {
        if (tetramini[i].x < 0)
            horizontal_sweep++;

        if (tetramini[i].x >= WIDTH)
            horizontal_sweep--;
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramini[i].x += horizontal_sweep;
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

        current_index = WIDTH * tetramini[i].y + tetramini[i].x;

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

        current_index = WIDTH * tetramini[i].y + tetramini[i].x;

        if (CELL[current_index - 1] >= 1)
            return TETRAMINO_OK;
    }

    for (int i = 0; i < TETRAMINI; i++)
        tetramino_move_left_act(&tetramini[i], tetris_map);

    return TETRAMINO_OK;
}

int tetramino_move_down(TETRAMINO_T, TETRIS_MAP_T)
{
    int current_index = WIDTH * tetramino->y + tetramino->x;
    int next_index = WIDTH * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= HEIGHT)
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
    int current_index = WIDTH * tetramino->y + tetramino->x;
    int next_index = WIDTH * (tetramino->y + 1) + tetramino->x;

    if (tetramino->y + 1 >= HEIGHT)
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
    int current_index = WIDTH * tetramino->y + tetramino->x;
    int next_index = WIDTH * (tetramino->y + 1) + tetramino->x;

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
        current_index = WIDTH * tetramini[i].y + tetramini[i].x;
        next_index = WIDTH * (tetramini[i].y + 1) + tetramini[i].x;
        CELL[current_index] = tetramini[i].color_id;
    }

    return TETRAMINO_DEAD;
}

int tetramino_move_right(TETRAMINO_T, TETRIS_MAP_T)
{
    if (tetramino->x >= WIDTH - 1)
    {
        return TETRAMINO_OK;
    }

    int right_index = WIDTH * tetramino->y + (tetramino->x + 1);
    if (!CELL[right_index])
    {
        tetramino->x++;
    }

    return TETRAMINO_OK;
}

int tetramino_move_right_check(TETRAMINO_T, TETRIS_MAP_T)
{
    if (tetramino->x >= WIDTH - 1)
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

    WIDTH = width;
    HEIGHT = height;
    QUEUE_ID = 0;

    tetris_queue_init(tetris_map);
}

void tetris_queue_init(TETRIS_MAP_T)
{
    // We're going to make two queues
    int queue_size = sizeof(int) * TETRAMINI_SHAPES * 2;

    QUEUE = malloc(queue_size);
    memset(QUEUE, 0, queue_size);

    // Each queue has each shape type
    for (int i = 0; i < TETRAMINI_SHAPES * 2; i++)
        QUEUE[i] = i % TETRAMINI_SHAPES;

    // I shuffle the first queue
    shuffle_array(QUEUE, TETRAMINI_SHAPES);
    // Then the second one
    shuffle_array(QUEUE + TETRAMINI_SHAPES, TETRAMINI_SHAPES);

    // Why? Because with this system I can show previews for the next shapes
    // And at the same time make an infinite queue that has all the pieces
    // How cool is that?
}

void tetris_queue_next(TETRIS_MAP_T)
{   
    QUEUE_ID++;

    // If I get the eight piece in the queue
    // I swap the second queue with the first
    // And move to the second index
    // (Needs extensive testing)
    if (QUEUE_ID > TETRAMINI_SHAPES)
    {
        tetris_queue_swap(tetris_map);
        QUEUE_ID = 0;
    }
}

void tetris_queue_swap(TETRIS_MAP_T)
{
    // I copy the contents of the second queue to the first one
    memcpy(
        QUEUE + TETRAMINI_SHAPES,
        QUEUE,
        sizeof(int) * TETRAMINI_SHAPES);
    // Then I shuffle the second one
    shuffle_array(QUEUE + TETRAMINI_SHAPES, TETRAMINI_SHAPES);
    // In this way I used all the elements of the second queue
    // To make a new queue with all the pieces
}

static int rand_int(int n)
{
    int limit = RAND_MAX - RAND_MAX % n;
    int rnd;

    do
    {
        srand(time(NULL));
        rnd = rand();
    } while (rnd >= limit);

    return rnd % n;
}

void shuffle_array(int *array, int n)
{
    int i, j, tmp;

    for (i = n - 1; i > 0; i--)
    {
        j = rand_int(i + 1);
        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;
    }
}

void tetris_row_check_fill(TETRIS_MAP_T)
{
    int row;
    int column;

    // For each row of the Tetris map
    for (row = HEIGHT; row >= 0; row--)
    {
        int tetramini = 0;
        for (column = 0; column < WIDTH; column++)
        {
            // We count how many tetramini are in the row
            if (CELL[(row * WIDTH) + column] >= 1)
                tetramini += 1;
        }

        if (tetramini >= WIDTH)
            tetris_row_destroy(tetris_map, row);
    }
}

void tetris_row_destroy(TETRIS_MAP_T, int row)
{
    // Move down all the cells
    memmove(
        CELL + WIDTH,
        CELL,
        sizeof(int) * (WIDTH * row));
    memset(CELL + WIDTH, 0, sizeof(int) * WIDTH);
}

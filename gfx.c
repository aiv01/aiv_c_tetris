#include "gfx.h"
#include "tetris.h"

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, int color)
{
    // Blocks colors ranges from 1-6
    // And colors ranges from 0-5 so...
    color--;

    // Innter shape
    SDL_SetRenderDrawColor(renderer, T_COLOR[color].r, T_COLOR[color].g, T_COLOR[color].b, 255);
    SDL_RenderFillRect(renderer, rect);

    // Outer border
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, rect);

    // Light shade
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, rect->x + 1, rect->y + 1, rect->x - 2 + rect->w, rect->y + 1);
    SDL_RenderDrawLine(renderer, rect->x - 2 + rect->w, rect->y + 1, rect->x - 2 + rect->w, rect->y - 2 + rect->h);
}

void field_draw(tetris_map_t *tetris_map, SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = CELL_SIZE * HEIGHT;
    rect.w = CELL_SIZE * WIDTH;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);

    rect.x = CELL_SIZE * WIDTH;
    rect.y = 0;
    rect.h = CELL_SIZE * HEIGHT;
    rect.w = CELL_SIZE * RIGHT_MENU_SIZE;

    SDL_SetRenderDrawColor(renderer, 33, 33, 33, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void tetramino_draw(TETRAMINO_T, SDL_Renderer *renderer)
{
    SDL_Rect rect;
    rect.x = tetramino->x * CELL_SIZE;
    rect.y = tetramino->y * CELL_SIZE;
    rect.h = CELL_SIZE;
    rect.w = CELL_SIZE;
    _draw_rect_internal(renderer, &rect, tetramino->color_id);
}

void tetramino_group_draw(TETRAMINI_T, SDL_Renderer *renderer)
{
    for (int i = 0; i < 4; i++)
        tetramino_draw(&tetramini[i], renderer);
}

void tetris_map_draw(TETRIS_MAP_T, SDL_Renderer *renderer)
{
    field_draw(tetris_map, renderer);

    int y, x;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            int index = WIDTH * y + x;
            if (tetris_map->cell[index] != 0)
            {
                SDL_Rect rect;
                rect.x = x * CELL_SIZE;
                rect.y = y * CELL_SIZE;
                rect.h = CELL_SIZE;
                rect.w = CELL_SIZE;
                _draw_rect_internal(renderer, &rect, tetris_map->cell[index]);
            }
        }
    }
}

void draw_next_pieces(TETRIS_MAP_T, SDL_Renderer *renderer)
{
    for (int i = 0; i < 5; i++)
    {
        draw_piece_preview(tetris_map, renderer, i);
    }
}

void draw_piece_preview(TETRIS_MAP_T, SDL_Renderer *renderer, int index)
{
    int start_x = (HORIZONTAL_CELLS + 2) * CELL_SIZE;
    int start_y = CELL_SIZE + CELL_SIZE * (4 * index);

    for (int i = 0; i < TETRAMINI; i++)
    {
        int shape = QUEUE[index + QUEUE_ID];
        int cell_x = (tetramini_positions[shape][0][i] * CELL_SIZE);
        int cell_y = (tetramini_positions[shape][0][i + 4] * CELL_SIZE);

        SDL_Rect rect;
        rect.x = start_x + cell_x;
        rect.y = start_y + cell_y;
        rect.h = CELL_SIZE;
        rect.w = CELL_SIZE;
        _draw_rect_internal(renderer, &rect, shape + 1);
    }
}

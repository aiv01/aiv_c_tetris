#include "tetris.h"

const SDL_Color T_COLOR[] = 
{
    { 255, 127, 127 },
    { 127, 255, 127 },
    { 127, 127, 255 },
    { 255, 255, 127 },
    { 127, 255, 255 },
};

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, int color)
{
    SDL_SetRenderDrawColor(renderer, T_COLOR[color].r, T_COLOR[color].g, T_COLOR[color].b, 255);
    SDL_RenderFillRect(renderer, rect);
}

void field_draw(tetris_map_t *map, SDL_Renderer *renderer, int size)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = size * map->height;
    rect.w = size * map->width;

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size)
{
    SDL_Rect rect;
    rect.x = tetramino->x * size;
    rect.y = tetramino->y * size;
    rect.h = size;
    rect.w = size;
    _draw_rect_internal(renderer, &rect, tetramino->color_id);
}

void tetramino_group_draw(tetramino_t tetramini[4], SDL_Renderer *renderer, int size)
{
    for (int i = 0; i < 4; i++)
    {
        tetramino_draw(&tetramini[i], renderer, size);
    }
}

void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size)
{
    field_draw(map, renderer, size);

    int y, x;
    for (y = 0; y < map->height; y++)
    {
        for (x = 0; x < map->width; x++)
        {
            int index = map->width * y + x;
            if (map->cell[index] != 0)
            {
                SDL_Rect rect;
                rect.x = x * size;
                rect.y = y * size;
                rect.h = size;
                rect.w = size;
                _draw_rect_internal(renderer, &rect, map->cell_color_id[index]);
            }
        }
    }
}

#ifndef _GFX_H_
#define _GFX_H_

#include "tetris.h"
#include <SDL2/SDL.h>

const SDL_Color T_COLOR[] = 
{
    { 255, 127, 127 },
    { 127, 255, 127 },
    { 127, 127, 255 },
    { 255, 255, 127 },
    { 255, 127, 255 },
    { 127, 255, 255 },
    { 127, 127, 127 } // MMH
};

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, int color);
void field_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);
void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size);
void tetramino_group_draw(tetramino_t tetramini[4], SDL_Renderer *renderer, int size);
void tetris_map_draw(tetris_map_t *map, SDL_Renderer *renderer, int size);

#endif

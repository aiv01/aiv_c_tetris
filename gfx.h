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
void field_draw(tetris_map_t *tetris_map, SDL_Renderer *renderer);
void tetramino_draw(TETRAMINO_T, SDL_Renderer *renderer);
void tetris_map_draw(TETRIS_MAP_T, SDL_Renderer *renderer);
void draw_next_pieces(TETRIS_MAP_T, SDL_Renderer *renderer);
void draw_piece_preview(TETRIS_MAP_T, SDL_Renderer *renderer, int index);

#endif

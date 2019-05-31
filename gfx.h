#ifndef _GFX_H_
#define _GFX_H_

#include <SDL2/SDL.h>
#include "tetris.h"

const SDL_Color T_COLOR[] =
    {
        {255, 226, 0},  // O
        {0, 187, 50},   // S
        {0, 174, 231},  // I
        {255, 145, 0},  // L
        {159, 23, 144}, // T
        {255, 0, 36},   // Z
        {0, 90, 162}    // J
};

static void _draw_rect_internal(SDL_Renderer *renderer, SDL_Rect *rect, int color);
void field_draw(tetris_map_t *tetris_map, SDL_Renderer *renderer);
void tetramino_draw(TETRAMINO_T, SDL_Renderer *renderer);
void tetris_map_draw(TETRIS_MAP_T, SDL_Renderer *renderer);
void draw_next_pieces(TETRIS_MAP_T, SDL_Renderer *renderer);
void draw_piece_preview(TETRIS_MAP_T, SDL_Renderer *renderer, int index);

#endif

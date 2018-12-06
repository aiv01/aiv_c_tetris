#include "tetris.h"

void tetramino_draw(tetramino_t *tetramino, SDL_Renderer *renderer, int size)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = tetramino->y * size;
    rect.h = size;
    rect.w = size;

    SDL_RenderDrawRect(renderer, &rect);
}
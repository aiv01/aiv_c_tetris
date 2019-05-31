#include "sfx.h"

static const char *MY_COOL_MP3 = "music.mp3";

int music_play()
{
    int result = 0;
    int flags = MIX_INIT_MP3;

    if (SDL_Init(SDL_INIT_AUDIO) == -1)
    {
        SDL_Log("Failed to init SDL\n");
        return -1;
    }

    if (flags != (result = Mix_Init(flags)))
    {
        SDL_Log("Could not initialize mixer (result: %d).\n", result);
        SDL_Log("Mix_Init: %s\n", Mix_GetError());
        return -1;
    }

    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS(MY_COOL_MP3);
    Mix_PlayMusic(music, 1);

    return 0;
}
#include "sfx.h"

#define FREQ 44100;

static Uint8 *audio_pos;
static Uint32 audio_len;

static int volume = 64;
static int pitch_delta = 0;

void my_audio_callback(void *userdata, Uint8 *stream, int sample_length)
{
    SDL_memset(stream, 0, sample_length);

    if (audio_len == 0)
        return;

    if (sample_length > audio_len)
        sample_length = audio_len;

    SDL_MixAudio(stream, audio_pos, sample_length, volume);

    audio_pos += sample_length + pitch_delta;
    audio_len -= sample_length;
}

Uint8 *music_play()
{
    if (SDL_Init(SDL_INIT_AUDIO))
    {
        SDL_Log("Init error: %s", SDL_GetError());
        return NULL;
    }

    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;

    if (SDL_LoadWAV("music.wav", &wav_spec, &wav_buffer, &wav_length) == NULL)
    {
        SDL_Log("Could not open music.wav: %s\n", SDL_GetError());
        return NULL;
    }

    wav_spec.callback = my_audio_callback;
    wav_spec.userdata = NULL;

    audio_pos = wav_buffer;
    audio_len = wav_length;

    if (SDL_OpenAudio(&wav_spec, NULL) < 0)
    {
        SDL_Log("Couldn't open audio: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_PauseAudio(0);

    return wav_buffer;
}
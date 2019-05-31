#ifndef _SFX_H_
#define _SFX_H_

#include <SDL2/SDL.h>

void my_audio_callback(void *userdata, Uint8 *stream, int sample_length);
int music_play(Uint8 *wav_buffer);

#endif
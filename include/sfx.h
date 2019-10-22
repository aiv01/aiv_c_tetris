#ifndef _SFX_H_
#define _SFX_H_

#include <SDL2/SDL.h>

void my_audio_callback(void *userdata, Uint8 *stream, int sample_length);
Uint8 *music_play();

#endif
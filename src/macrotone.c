#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

#include "types.h"


uint32 const AMPLITUDE = 28000;
uint32 const SAMPLE_RATE = 44100;
real64 const A_HZ = 440.0f;


typedef struct AudioState {
  uint32 idx_last_sample;
  real64 pitch;
} AudioState;


void update_audio_state(AudioState *audio_state) {
  audio_state->idx_last_sample++;
  audio_state->pitch += 0.001f;
}


uint16 make_audio_sample(AudioState *audio_state) {
  real64 sample_time = (real64)(audio_state->idx_last_sample) / (real64)SAMPLE_RATE;
  uint16 sample = (uint16)(AMPLITUDE * sin(2.0f * M_PI * audio_state->pitch * sample_time));
  return sample;
}


void fill_audio_buffer(void *userdata, unsigned char *raw_buffer, int n_bytes) {
  // We are using AUDIO_S16SYS, so we have two bytes per sample.
  // Therefore, we want to address two bytes at a time.
  AudioState *audio_state = (AudioState*)userdata;
  uint16 *buffer = (uint16*)raw_buffer;
  uint32 n_samples_required = n_bytes / 2; // 2 bytes per sample for AUDIO_S16SYS
  for (uint32 idx_sample = 0; idx_sample < n_samples_required; idx_sample++) {
    update_audio_state(audio_state);
    buffer[idx_sample] = make_audio_sample(audio_state);
  }
}


void destroy_sdl_audio() {
  SDL_CloseAudio();
}


bool32 init_sdl_audio(SDL_AudioSpec target_spec) {
  if (SDL_Init(SDL_INIT_AUDIO) != 0) {
    SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
    return false;
  }

  SDL_AudioSpec actual_spec;
  if (SDL_OpenAudio(&target_spec, &actual_spec) != 0) {
    SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to open audio: %s", SDL_GetError());
    return false;
  }

  if (target_spec.format != actual_spec.format) {
    SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Failed to get the desired AudioSpec");
    destroy_sdl_audio();
    return false;
  }

  return true;
}


int main(int argc, char *argv[]) {
  AudioState audio_state = {
    .idx_last_sample = 0,
    .pitch = A_HZ / 2.0f,
  };
  SDL_AudioSpec target_spec = {
    .freq = SAMPLE_RATE,
    .format = AUDIO_S16SYS,
    .channels = 1,
    .samples = 2048,
    .callback = fill_audio_buffer,
    .userdata = &audio_state,
  };
  if (!init_sdl_audio(target_spec)) {
    goto cleanup_end;
  }

  SDL_PauseAudio(0);
  SDL_Delay(2000);
  SDL_PauseAudio(1);

  destroy_sdl_audio();
cleanup_end:
  return EXIT_SUCCESS;
}

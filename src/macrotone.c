#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>

#include "types.h"
#include "audio.h"


void run_main_loop(bool32 *should_stop, AudioState *audio_state) {
  SDL_Delay(1000);
  audio_play_note(audio_state, 220.0f, 2.0f);
  SDL_Delay(5000);
}


int main(int argc, char *argv[]) {
  bool32 should_stop = false;
  AudioState audio_state = {
    .idx_last_sample = 0,
    .pitch = AUDIO_A_HZ,
    .duration_remaining = 0.0f,
  };

  SDL_AudioSpec target_spec = {
    .freq = AUDIO_SAMPLE_RATE,
    .format = AUDIO_S16SYS,
    .channels = 1,
    .samples = 2048,
    .callback = audio_fill_buffer,
    .userdata = &audio_state,
  };
  if (!audio_init(target_spec)) {
    goto cleanup_end;
  }
  SDL_PauseAudio(0);

  while (!should_stop) {
    run_main_loop(&should_stop, &audio_state);
  }

  audio_destroy();
cleanup_end:
  return EXIT_SUCCESS;
}

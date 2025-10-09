#include "audio.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

void ren_audio_init(size_t count, const char* audio_init_buffer_in [count], Sound output_sounds[count]){
  if(ma_engine_init(NULL, &engine) != MA_SUCCESS){
    fprintf(stderr, "could'nt initialize miniaudio audio engine!\n");
  };

  for (uint32_t i = 0; i < count; i++) {
    if(ma_sound_init_from_file(&engine, audio_init_buffer_in[i], 0, NULL, NULL, &output_sounds[i]) != MA_SUCCESS){
      fprintf(stderr, "failed to initialize audio!\n");
      fprintf(stderr, "File: %s\n", audio_init_buffer_in[i]);
      fprintf(stderr, "make sure all the paths are correct!\n");
    };
  }

  printf("initialized all sounds! moving on\n");
};


// used to init one single audio, mostly for testing, ren_audio_init is better handled.
void ren_audio_init_one_sound_debug(const char* sound_path , Sound* output_sounds){
  if(ma_engine_init(NULL, &engine) != MA_SUCCESS){
    fprintf(stderr, "could'nt initialize miniaudio audio engine!\n");
  };

  if(ma_sound_init_from_file(&engine, sound_path, 0, NULL, NULL, output_sounds) != MA_SUCCESS){};

  printf("initialized all one sounds (%s)! moving on\n", sound_path);
};

void ren_audio_play(Sound* sound, int flags){
  if (flags == REN_AUDIO_LOOP) {
    ma_sound_set_looping(sound, MA_TRUE);
  }
  if(ma_sound_start(sound) != MA_SUCCESS){
    fprintf(stderr, "failed to play audio\n");
  };
};

// should only basically be used on dynamically loaded audio files
// or if you want to play the same sound at the same time
// otherwise, preload everything the init function
void ren_audio_play_engine(const char* filename){
  if (ma_engine_play_sound(&engine , filename, NULL) != MA_SUCCESS){
    fprintf(stderr, "failed to play audio using the engine\n");
    fprintf(stderr, "File: %s\n", filename);
  };
}

void ren_audio_play_volume(Sound* sound, int flags, float volume){
  ma_sound_set_volume(sound, volume);

  if (flags == REN_AUDIO_LOOP) {
    ma_sound_set_looping(sound, MA_TRUE);
  }

  if(ma_sound_start(sound) != MA_SUCCESS){
    fprintf(stderr, "failed to play audio\n");
  };
}

void ren_audio_terminate(size_t count, Sound output_sounds[count]){

  for (uint32_t i = 0; i < count; i++) {
    ma_sound_uninit(&output_sounds[i]);
  }

  ma_engine_uninit(&engine);
};

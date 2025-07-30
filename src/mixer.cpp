// Copyright (c) 2025 Sylar129. All rights reserved

#include "mixer.h"

namespace spaceshooter{

Mixer::Mixer(){
  SDL_AudioSpec audio_spec{SDL_AUDIO_U8, 2, 44100};
  mixer_ =
      MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &audio_spec);
  if (!mixer_) {
    SDL_Log("MIX_CreateMixerDevice Error: %s\n", SDL_GetError());
  }
}

Mixer::~Mixer() { 
  for (auto& audio: audios_){
    MIX_DestroyAudio(audio.second);
  }
  MIX_DestroyMixer(mixer_); }

void Mixer::LoadAudio(const std::string& file_path, const std::string& tag) {
  auto audio = MIX_LoadAudio(mixer_, file_path.c_str(), true);
  if (!audio) {
    SDL_Log("MIX_LoadAudio Error: %s\n", SDL_GetError());
    return;
  }

  audios_[tag] = audio;
}

void Mixer::PlayAudio(const std::string& tag) const{
  if (!audios_.contains(tag)){
    SDL_Log("no audio(%s) Error: %s\n", tag.c_str(), SDL_GetError());
    return;
  }
  MIX_PlayAudio(mixer_, audios_.at(tag));
}

}

// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <map>
#include <string>

#include "SDL3_mixer/SDL_mixer.h"

namespace spaceshooter {

class Mixer {
 public:
  Mixer();
  ~Mixer();

  void LoadAudio(const std::string& file_path, const std::string& tag);

  void PlayAudio(const std::string& tag) const;

 private:
  MIX_Mixer* mixer_;
  std::map<std::string, MIX_Audio*> audios_;
};

}  // namespace spaceshooter
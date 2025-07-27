// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "SDL_render.h"

namespace spaceshooter {

struct Texture {
  explicit Texture(const std::string& file_path);
  ~Texture();

  // shoule use a vector, but there's no type yet
  SDL_FPoint GetSize() const;
  SDL_Texture* texture = nullptr;
};

}  // namespace spaceshooter

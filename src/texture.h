// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>

#include "SDL_render.h"

namespace spaceshooter {

struct Texture {
  explicit Texture(const std::string& file_path);
  ~Texture();
  SDL_Texture* texture = nullptr;
  float width;
  float height;
};

}  // namespace spaceshooter

// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <SDL.h>

namespace spaceshooter {

struct Player {
  SDL_Texture* texture = nullptr;
  SDL_FPoint poisition{};
  int width{};
  int height{};
};

}  // namespace spaceshooter

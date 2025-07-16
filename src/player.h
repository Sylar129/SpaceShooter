// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>

namespace spaceshooter {

class Player {
 public:
  Player();
  ~Player();

  void Render();

 private:
   SDL_Texture *texture_ = nullptr;
   SDL_Rect rect_{};
};

}  // namespace spaceshooter

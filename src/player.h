// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "SDL_events.h"
#include "SDL_rect.h"
#include "SDL_render.h"

namespace spaceshooter {

class Player {
 public:
  Player();
  ~Player();

  void HandleEvent(SDL_Event* event);
  void Update();
  void Render();

 private:
  SDL_Texture* texture_ = nullptr;
  SDL_FPoint position_;
  float width_;
  float height_;
  float speed_;
};

}  // namespace spaceshooter

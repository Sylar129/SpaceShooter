// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <SDL.h>

namespace spaceshooter {

class Scene {
 public:
  virtual void Init() = 0;
  virtual void HandleEvent(SDL_Event* event) = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void Clean() = 0;
};

}  // namespace spaceshooter

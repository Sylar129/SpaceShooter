// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "SDL3/SDL_events.h"

namespace spaceshooter {

class Scene {
 public:
  virtual ~Scene() = default;

  virtual void Init() = 0;
  virtual void HandleEvent(SDL_Event* event) = 0;
  virtual void Update(Uint64 delta_time) = 0;
  virtual void Render() = 0;
  virtual void Clean() = 0;
};

}  // namespace spaceshooter

// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "player.h"
#include "scene.h"

namespace spaceshooter {

class SceneMain : public Scene {
 public:
  SceneMain() = default;
  ~SceneMain() override = default;

  void Init() override;
  void HandleEvent(SDL_Event* event) override;
  void Update(Uint32 delta_time) override;
  void Render() override;
  void Clean() override;

 private:
  Player player_;
};

}  // namespace spaceshooter

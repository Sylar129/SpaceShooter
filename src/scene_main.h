// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "player.h"
#include "scene.h"
namespace spaceshooter {

class SceneMain : public Scene {
 public:
  virtual void Init() override;
  virtual void HandleEvent(SDL_Event* event) override;
  virtual void Update() override;
  virtual void Render() override;
  virtual void Clean() override;

 private:
  Player player_;
};

}  // namespace spaceshooter

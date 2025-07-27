// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "player.h"
#include "scene.h"
#include "texture.h"

namespace spaceshooter {

struct Enemy {
  SDL_FPoint position;
  float speed;
};

class SceneMain : public Scene {
 public:
  SceneMain();
  ~SceneMain() override = default;

  void Init() override;
  void HandleEvent(SDL_Event* event) override;
  void Update(Uint32 delta_time) override;
  void Render() override;
  void Clean() override;

 private:
  void UpdateEnemy(Uint32 delta_time);
  void SpawnEnemy();
  Player player_;

  Texture enemy_texture_;
  std::list<Enemy> enemies_;
};

}  // namespace spaceshooter

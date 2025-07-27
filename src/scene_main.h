// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include "player.h"
#include "scene.h"
#include "texture.h"

namespace spaceshooter {

struct Enemy {
  SDL_FPoint position;
  float speed;
  Uint32 last_shoot_time;
  Uint32 shoot_cooldown;
};

struct EnemyProjectile {
  SDL_FPoint position;
  SDL_FPoint direction;
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
  void UpdateEnemyProjectiles(Uint32 delta_time);

  void RenderEnemy();
  void RenderEnemyProjectile();

  Player player_;

  Texture enemy_texture_;
  Texture enemy_projectile_texture_;
  std::list<Enemy> enemies_;
  std::list<EnemyProjectile> enemy_projectiles_;
};

}  // namespace spaceshooter

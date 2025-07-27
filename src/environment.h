// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <list>

#include "SDL_rect.h"
#include "texture.h"

namespace spaceshooter {

class Player;

struct Enemy {
  int health = 1;
  SDL_FPoint size;
  SDL_FPoint position;
  float speed;
  Uint32 last_shoot_time;
  Uint32 shoot_cooldown;

  SDL_FRect GetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

struct EnemyProjectile {
  SDL_FPoint size;
  SDL_FPoint position;
  SDL_FPoint direction;
  float speed;

  SDL_FRect GetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

struct Explosion {
  SDL_FPoint size;
  SDL_FPoint position;
  int total_frame;
  int current_frame = 0;
  int fps = 10;
  Uint32 start_time;

  SDL_Rect GetSourceRect() const {
    return SDL_Rect{static_cast<int>(current_frame * size.x), 0,
                    static_cast<int>(size.x), static_cast<int>(size.y)};
  }

  SDL_FRect GetTargetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

class Environment {
 public:
  Environment(const Environment&) = delete;
  Environment& operator=(const Environment&) = delete;
  ~Environment() = default;

  static Environment& Get() {
    static Environment environment;
    return environment;
  }

  void SetTargetPlayer(Player* player);
  void SpawnEnemy();
  std::list<Enemy>& GetEnemies() { return enemies_; }

  void Update(Uint32 delta_time);
  void Render();

 private:
  Environment();

  void UpdateEnemy(Uint32 delta_time);
  void UpdateEnemyProjectiles(Uint32 delta_time);

  void RenderEnemy();
  void RenderEnemyProjectile();

  void UpdateExplosion();
  void RenderExplosion();

  Player* target_player_;

  Texture enemy_texture_;
  Texture enemy_projectile_texture_;
  std::list<Enemy> enemies_;
  std::list<EnemyProjectile> enemy_projectiles_;

  Texture explosion_texture_;
  std::list<Explosion> explosions_;
};

}  // namespace spaceshooter

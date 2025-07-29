// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <list>
#include <string>

#include "SDL3/SDL_rect.h"

namespace spaceshooter {

class Player;

struct Enemy {
  std::string texture_path;
  int health = 1;
  SDL_FPoint size;
  SDL_FPoint position;
  float speed;
  Uint64 last_shoot_time;
  Uint64 shoot_cooldown;

  SDL_FRect GetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

struct EnemyProjectile {
  std::string texture_path;
  SDL_FPoint size;
  SDL_FPoint position;
  SDL_FPoint direction;
  float speed;

  SDL_FRect GetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

struct Explosion {
  std::string texture_path;
  SDL_FPoint size;
  SDL_FPoint position;
  int total_frame;
  int current_frame = 0;
  int fps = 10;
  Uint64 start_time;

  SDL_FRect GetSourceRect() const {
    return SDL_FRect{current_frame * size.x, 0, size.x, size.y};
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

  void Update(Uint64 delta_time);
  void Render();

 private:
  Environment();

  void UpdateEnemy(Uint64 delta_time);
  void UpdateEnemyProjectiles(Uint64 delta_time);

  void RenderEnemy();
  void RenderEnemyProjectile();

  void UpdateExplosion();
  void RenderExplosion();

  Player* target_player_;

  std::list<Enemy> enemies_;
  std::list<EnemyProjectile> enemy_projectiles_;

  std::list<Explosion> explosions_;
};

}  // namespace spaceshooter

// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <list>
#include <string>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

namespace spaceshooter {

struct Projectile {
  std::string texture_path;
  SDL_FPoint size;
  SDL_FPoint position;
  float speed;

  SDL_FRect GetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

class Player {
 public:
  Player();
  ~Player();

  void HandleEvent(SDL_Event* event);
  void Update(Uint64 delta_time);
  void Render();

  // return center
  SDL_FPoint GetPosition() const;
  SDL_FRect GetRect() const;

  void TakeDamage(int damage);
  bool IsAlive() const { return is_alive; }

 private:
  void Shoot();
  void UpdateProjectiles(Uint64 delta_time);

  std::string texture_path_;
  int health_ = 5;
  bool is_alive;
  SDL_FPoint size_;
  SDL_FPoint position_;
  float speed_;
  Uint64 last_shoot_time_;
  Uint64 shoot_cooldown_;

  std::list<Projectile> projectiles_;
};

}  // namespace spaceshooter

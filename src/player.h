// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <list>

#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "texture.h"

namespace spaceshooter {

struct Projectile {
  SDL_FPoint size;
  SDL_FPoint position;
  float speed;

  SDL_FRect GetRect() const {
    return SDL_FRect{position.x, position.y, size.x, size.y};
  }
};

struct Item;

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
  int GetHealth() const { return health_; }
  int GetMaxHealth() const { return 50; }
  bool IsAlive() const { return health_ > 0; }

  void GetItem(const Item& item);

 private:
  void Shoot();
  void UpdateProjectiles(Uint64 delta_time);

  Texture ship_texture_;
  int health_ = 50;
  SDL_FPoint size_;
  SDL_FPoint position_;
  float speed_;
  Uint64 last_shoot_time_;
  Uint64 shoot_cooldown_;

  Texture projectile_texture_;
  std::list<Projectile> projectiles_;
};

}  // namespace spaceshooter

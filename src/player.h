// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <list>

#include "SDL_events.h"
#include "SDL_rect.h"
#include "SDL_render.h"
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

class Player {
 public:
  Player();
  ~Player();

  void HandleEvent(SDL_Event* event);
  void Update(Uint32 delta_time);
  void Render();

  // return center
  SDL_FPoint GetPosition() const;
  SDL_FRect GetRect() const;

 private:
  void Shoot();
  void UpdateProjectiles(Uint32 delta_time);

  Texture ship_texture_;
  SDL_FPoint size_;
  SDL_FPoint position_;
  float speed_;
  Uint32 last_shoot_time_;
  Uint32 shoot_cooldown_;

  Texture projectile_texture_;
  std::list<Projectile> projectiles_;
};

}  // namespace spaceshooter

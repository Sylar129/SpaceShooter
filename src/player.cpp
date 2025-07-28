// Copyright (c) 2025 Sylar129. All rights reserved

#include "player.h"

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "environment.h"
#include "game.h"

namespace spaceshooter {

Player::Player()
    : ship_texture_("assets/image/SpaceShip.png"),
      projectile_texture_("assets/image/bullet.png") {
  constexpr float kScale = 0.25;
  size_ = ship_texture_.GetSize();
  size_.x *= kScale;
  size_.y *= kScale;

  position_.x = Game::Get().GetWindowWidth() / 2 - size_.x / 2;
  position_.y = Game::Get().GetWindowHeight() - size_.y;

  speed_ = 0.5;
  last_shoot_time_ = 0;
  shoot_cooldown_ = 500;
  is_alive = true;
}

Player::~Player() {}

void Player::HandleEvent(SDL_Event* event) {}

void Player::Update(Uint64 delta_time) {
  if (!is_alive) {
    return;
  }
  auto key_states = SDL_GetKeyboardState(nullptr);
  auto distance = delta_time * speed_;
  if (key_states[SDL_SCANCODE_A]) {
    position_.x -= distance;
  }
  if (key_states[SDL_SCANCODE_D]) {
    position_.x += distance;
  }
  if (key_states[SDL_SCANCODE_W]) {
    position_.y -= distance;
  }
  if (key_states[SDL_SCANCODE_S]) {
    position_.y += distance;
  }

  if (position_.x < 0) {
    position_.x = 0;
  }

  if (position_.x > Game::Get().GetWindowWidth() - size_.x) {
    position_.x = Game::Get().GetWindowWidth() - size_.x;
  }

  if (position_.y < 0) {
    position_.y = 0;
  }

  if (position_.y > Game::Get().GetWindowHeight() - size_.y) {
    position_.y = Game::Get().GetWindowHeight() - size_.y;
  }

  UpdateProjectiles(delta_time);

  if (key_states[SDL_SCANCODE_J]) {
    Shoot();
  }
}

void Player::Render() {
  SDL_FRect player_rect = GetRect();
  SDL_RenderTexture(Game::Get().GetRenderer(), ship_texture_.texture, nullptr,
                    &player_rect);

  for (const Projectile& projectile : projectiles_) {
    SDL_FRect projectile_rect = projectile.GetRect();
    SDL_RenderTexture(Game::Get().GetRenderer(), projectile_texture_.texture,
                      nullptr, &projectile_rect);
  }
}

SDL_FPoint Player::GetPosition() const {
  return {position_.x + 0.5f * size_.x, position_.y + 0.5f * size_.y};
}

SDL_FRect Player::GetRect() const {
  return SDL_FRect{position_.x, position_.y, size_.x, size_.y};
}

void Player::TakeDamage(int damage) {
  health_ -= damage;
  if (health_ <= 0) {
    is_alive = false;
    // Game::Get().StopRunning();
  }
}

void Player::Shoot() {
  constexpr float kProjectileSpeed = 0.3f;
  if (SDL_GetTicks() - last_shoot_time_ > shoot_cooldown_) {
    Projectile projectile;
    projectile.size = projectile_texture_.GetSize();
    projectile.speed = kProjectileSpeed;
    projectile.position = SDL_FPoint{
        position_.x + 0.5f * size_.x - 0.5f * projectile_texture_.GetSize().x,
        position_.y};

    projectiles_.push_back(projectile);
    last_shoot_time_ = SDL_GetTicks();
  }
}

void Player::UpdateProjectiles(Uint64 delta_time) {
  auto& enemies = Environment::Get().GetEnemies();

  for (auto it = projectiles_.begin(); it != projectiles_.end();) {
    auto& projectile = *it;
    auto distance = delta_time * projectile.speed;
    projectile.position.y -= distance;
    if (projectile.position.y < -projectile.size.y) {
      it = projectiles_.erase(it);
      continue;
    }
    bool hitted = false;
    auto projectile_rect = projectile.GetRect();
    for (auto& enemy : enemies) {
      auto enemy_rect = enemy.GetRect();
      if (SDL_HasRectIntersectionFloat(&projectile_rect, &enemy_rect)) {
        enemy.health--;
        hitted = true;
        continue;
      }
    }
    if (hitted) {
      it = projectiles_.erase(it);
      continue;
    }

    it++;
  }
}

}  // namespace spaceshooter

// Copyright (c) 2025 Sylar129. All rights reserved

#include "player.h"

#include "SDL_image.h"
#include "SDL_keyboard.h"
#include "SDL_rect.h"
#include "SDL_scancode.h"
#include "game.h"

namespace spaceshooter {

Player::Player()
    : ship_texture_("assets/image/SpaceShip.png"),
      projectile_texture_("assets/image/bullet.png") {
  constexpr float kScale = 0.25;
  ship_texture_.width *= kScale;
  ship_texture_.height *= kScale;

  position_.x = Game::Get().GetWindowWidth() / 2 - ship_texture_.width / 2;
  position_.y = Game::Get().GetWindowHeight() - ship_texture_.height;

  speed_ = 0.5;
  last_shoot_time_ = 0;
  shoot_cooldown_ = 500;
}

Player::~Player() {}

void Player::HandleEvent(SDL_Event* event) {}

void Player::Update(Uint32 delta_time) {
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

  if (position_.x > Game::Get().GetWindowWidth() - ship_texture_.width) {
    position_.x = Game::Get().GetWindowWidth() - ship_texture_.width;
  }

  if (position_.y < 0) {
    position_.y = 0;
  }

  if (position_.y > Game::Get().GetWindowHeight() - ship_texture_.height) {
    position_.y = Game::Get().GetWindowHeight() - ship_texture_.height;
  }

  UpdateProjectiles(delta_time);

  if (key_states[SDL_SCANCODE_J]) {
    Shoot();
  }
}

void Player::Render() {
  SDL_FRect player_rect{position_.x, position_.y, ship_texture_.width,
                        ship_texture_.height};
  SDL_RenderCopyF(Game::Get().GetRenderer(), ship_texture_.texture, nullptr,
                  &player_rect);

  for (const Projectile& projectile : projectiles_) {
    SDL_FRect projectile_rect{projectile.position.x, projectile.position.y,
                              projectile_texture_.width,
                              projectile_texture_.height};
    SDL_RenderCopyF(Game::Get().GetRenderer(), projectile_texture_.texture,
                    nullptr, &projectile_rect);
  }
}

SDL_FPoint Player::getPosition() const {
  return {position_.x + 0.5f * ship_texture_.width,
          position_.y + 0.5f * ship_texture_.height};
}

void Player::Shoot() {
  constexpr float kProjectileSpeed = 0.3;
  if (SDL_GetTicks() - last_shoot_time_ > shoot_cooldown_) {
    Projectile new_projectile;
    new_projectile.speed = kProjectileSpeed;
    new_projectile.position =
        SDL_FPoint{position_.x + 0.5f * ship_texture_.width -
                       0.5f * projectile_texture_.width,
                   position_.y};

    projectiles_.push_back(new_projectile);
    last_shoot_time_ = SDL_GetTicks();
  }
}

void Player::UpdateProjectiles(Uint32 delta_time) {
  for (auto it = projectiles_.begin(); it != projectiles_.end();) {
    auto& projectile = *it;
    auto distance = delta_time * projectile.speed;
    projectile.position.y -= distance;
    if (projectile.position.y < -projectile_texture_.height) {
      it = projectiles_.erase(it);
    } else {
      it++;
    }
  }
}

}  // namespace spaceshooter

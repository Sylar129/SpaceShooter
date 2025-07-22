// Copyright (c) 2025 Sylar129. All rights reserved

#include "player.h"

#include "SDL_image.h"
#include "SDL_keyboard.h"
#include "SDL_rect.h"
#include "SDL_scancode.h"
#include "game.h"

namespace spaceshooter {

Player::Player() {
  constexpr float kScale = 0.25;
  texture_ =
      IMG_LoadTexture(Game::Get().GetRenderer(), "assets/image/SpaceShip.png");
  int w, h;
  SDL_QueryTexture(texture_, nullptr, nullptr, &w, &h);
  width_ = w * kScale;
  height_ = h * kScale;

  position_.x = Game::Get().GetWindowWidth() / 2 - width_ / 2;
  position_.y = Game::Get().GetWindowHeight() - height_;

  speed_ = 1;
}

Player::~Player() { SDL_DestroyTexture(texture_); }

void Player::HandleEvent(SDL_Event *event) {}

void Player::Update() {
  auto key_states = SDL_GetKeyboardState(nullptr);
  if (key_states[SDL_SCANCODE_A]) {
    position_.x -= speed_;
  }
  if (key_states[SDL_SCANCODE_D]) {
    position_.x += speed_;
  }
  if (key_states[SDL_SCANCODE_W]) {
    position_.y -= speed_;
  }
  if (key_states[SDL_SCANCODE_S]) {
    position_.y += speed_;
  }

  if (position_.x < 0) {
    position_.x = 0;
  }

  if (position_.x > Game::Get().GetWindowWidth() - width_) {
    position_.x = Game::Get().GetWindowWidth() - width_;
  }

  if (position_.y < 0) {
    position_.y = 0;
  }

  if (position_.y > Game::Get().GetWindowHeight() - height_) {
    position_.y = Game::Get().GetWindowHeight() - height_;
  }
}

void Player::Render() {
  SDL_FRect player_rect{position_.x, position_.y, width_, height_};
  SDL_RenderCopyF(Game::Get().GetRenderer(), texture_, nullptr, &player_rect);
}

}  // namespace spaceshooter

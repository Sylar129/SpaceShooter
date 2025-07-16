// Copyright (c) 2025 Sylar129. All rights reserved

#include "player.h"

#include <SDL_image.h>

#include "game.h"

namespace spaceshooter {

Player::Player() {
  constexpr float kScale = 0.25;
  texture_ =
      IMG_LoadTexture(Game::Get().GetRenderer(), "assets/image/SpaceShip.png");
  SDL_QueryTexture(texture_, nullptr, nullptr, &rect_.w, &rect_.h);
  rect_.w *= kScale;
  rect_.h *= kScale;

  rect_.x = Game::Get().GetWindowWidth() / 2 - rect_.w / 2;
  rect_.y = Game::Get().GetWindowHeight() - rect_.h;
}

Player::~Player() { SDL_DestroyTexture(texture_); }

void Player::Render() {
  SDL_RenderCopy(Game::Get().GetRenderer(), texture_, nullptr, &rect_);
}

}  // namespace spaceshooter

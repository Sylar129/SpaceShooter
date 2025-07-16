// Copyright (c) 2025 Sylar129. All rights reserved

#include "player.h"

#include <SDL_image.h>

#include "game.h"

namespace spaceshooter {

Player::Player() {
  constexpr float kScale = 0.25;
  texture =
      IMG_LoadTexture(Game::Get().GetRenderer(), "assets/image/SpaceShip.png");
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
  width *= kScale;
  height *= kScale;

  poisition.x = Game::Get().GetWindowWidth() / 2 - width / 2;
  poisition.y = Game::Get().GetWindowHeight() - height;
}

Player::~Player() { SDL_DestroyTexture(texture); }

void Player::Render() {
  SDL_Rect player_rect = {poisition.x, poisition.y, width, height};
  SDL_RenderCopy(Game::Get().GetRenderer(), texture, nullptr, &player_rect);
}

}  // namespace spaceshooter

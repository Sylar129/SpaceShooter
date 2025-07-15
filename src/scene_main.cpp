// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include <SDL_image.h>

#include "game.h"

namespace spaceshooter {

void SceneMain::Init() {
  constexpr float kScale = 0.25;
  player_.texture =
      IMG_LoadTexture(Game::Get().GetRenderer(), "assets/image/SpaceShip.png");
  SDL_QueryTexture(player_.texture, nullptr, nullptr, &player_.width,
                   &player_.height);
  player_.width *= kScale;
  player_.height *= kScale;

  player_.poisition.x = Game::Get().GetWindowWidth() / 2 - player_.width / 2;
  player_.poisition.y = Game::Get().GetWindowHeight() - player_.height;
}

void SceneMain ::HandleEvent(SDL_Event* event) {}

void SceneMain ::Update() {}

void SceneMain ::Render() {
  SDL_Rect player_rect = {player_.poisition.x, player_.poisition.y,
                          player_.width, player_.height};
  SDL_RenderCopy(Game::Get().GetRenderer(), player_.texture, nullptr,
                 &player_rect);
}

void SceneMain ::Clean() { SDL_DestroyTexture(player_.texture); }

}  // namespace spaceshooter

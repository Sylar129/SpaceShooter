// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include "environment.h"
#include "game.h"

namespace spaceshooter {

SceneMain::SceneMain()
    : health_texture_("assets/image/Health UI Black.png"),
      near_stars_("assets/image/Stars-A.png"),
      far_stars_("assets/image/Stars-B.png") {
  Environment::Get().SetTargetPlayer(&player_);
}

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) { player_.HandleEvent(event); }

void SceneMain::Update(Uint64 delta_time) {
  player_.Update(delta_time);

  Environment::Get().Update(delta_time);

  Environment::Get().SpawnEnemy();
}

void SceneMain::Render() {
  RenderBackgound();

  player_.Render();

  Environment::Get().Render();
  RenderUi();
}

void SceneMain::Clean() {}

void SceneMain::RenderUi() const {
  int current_health = player_.GetHealth();
  SDL_FRect start_rect{10, 10, health_texture_.GetSize().x,
                       health_texture_.GetSize().y};
  for (int i = 10; i <= player_.GetMaxHealth(); i += 10) {
    if (i < current_health) {
      SDL_SetTextureAlphaModFloat(health_texture_.texture, 1);
    } else if (i < current_health + 10) {
      SDL_SetTextureAlphaModFloat(health_texture_.texture,
                                  (current_health + 10 - i) * 0.1);
    } else {
      SDL_SetTextureAlphaModFloat(health_texture_.texture, 0);
    }
    SDL_RenderTexture(Game::Get().GetRenderer(), health_texture_.texture,
                      nullptr, &start_rect);
    start_rect.x += 10 + health_texture_.GetSize().x;
  }
}

void SceneMain::RenderBackgound() const {
  // draw near
  SDL_FPoint near_size = near_stars_.GetSize();

  for (int i = 0; i < Game::Get().GetWindowWidth(); i += near_size.y) {
    SDL_FRect rect{i, 0, near_size.x, near_size.y};
    SDL_RenderTexture(Game::Get().GetRenderer(), near_stars_.texture, nullptr,
                      &rect);
  }

  // draw far

  SDL_FPoint far_size = far_stars_.GetSize();
  for (int i = 0; i < Game::Get().GetWindowWidth(); i += far_size.y) {
    SDL_FRect rect{i, 0, far_size.x, far_size.y};
    SDL_RenderTexture(Game::Get().GetRenderer(), far_stars_.texture, nullptr,
                      &rect);
  }
}

}  // namespace spaceshooter

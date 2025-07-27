// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include <random>

#include "SDL_log.h"
#include "game.h"

namespace spaceshooter {

namespace {
float getRandomFloat() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dis(0, 1);
  return dis(gen);
}
}  // namespace

SceneMain::SceneMain() : enemy_texture_("assets/image/insect-1.png") {
  enemy_texture_.width *= 0.25;
  enemy_texture_.height *= 0.25;
}

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) { player_.HandleEvent(event); }

void SceneMain::Update(Uint32 delta_time) {
  player_.Update(delta_time);
  UpdateEnemy(delta_time);

  SpawnEnemy();
}

void SceneMain::Render() {
  player_.Render();

  for (const auto& enemy : enemies_) {
    SDL_FRect rect{enemy.position.x, enemy.position.y, enemy_texture_.width,
                   enemy_texture_.height};
    SDL_RenderCopyF(Game::Get().GetRenderer(), enemy_texture_.texture, nullptr,
                    &rect);
  }
}

void SceneMain::Clean() {}

void SceneMain::UpdateEnemy(Uint32 delta_time) {
  for (auto it = enemies_.begin(); it != enemies_.end();) {
    auto& enemy = *it;
    auto distance = delta_time * enemy.speed;
    enemy.position.y += distance;
    if (enemy.position.y > Game::Get().GetWindowHeight()) {
      it = enemies_.erase(it);
    } else {
      it++;
    }
  }
}

void SceneMain::SpawnEnemy() {
  if (getRandomFloat() > 0.1) {
    return;
  }

  Enemy enemy;
  enemy.position.x = getRandomFloat() * Game::Get().GetWindowWidth();
  enemy.position.y = 0;
  enemy.speed = 0.2;
  enemies_.push_back(enemy);
}

}  // namespace spaceshooter

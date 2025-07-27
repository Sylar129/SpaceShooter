// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include <random>

#include "SDL_log.h"
#include "SDL_timer.h"
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

SceneMain::SceneMain()
    : enemy_texture_("assets/image/insect-1.png"),
      enemy_projectile_texture_("assets/image/laser-1.png") {
  enemy_texture_.width *= 0.25;
  enemy_texture_.height *= 0.25;

  enemy_projectile_texture_.width *= 0.25;
  enemy_projectile_texture_.height *= 0.25;
}

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) { player_.HandleEvent(event); }

void SceneMain::Update(Uint32 delta_time) {
  player_.Update(delta_time);

  UpdateEnemyProjectiles(delta_time);

  UpdateEnemy(delta_time);

  SpawnEnemy();
}

void SceneMain::Render() {
  player_.Render();

  RenderEnemy();
  RenderEnemyProjectile();
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
      bool hit_from_back = enemy.position.y > player_.getPosition().y;
      if (SDL_GetTicks() - enemy.last_shoot_time > enemy.shoot_cooldown &&
          !hit_from_back) {
        EnemyProjectile projectile;
        projectile.speed = 0.3;
        projectile.position = enemy.position;

        auto direction = SDL_FPoint{player_.getPosition().x - enemy.position.x,
                                    player_.getPosition().y - enemy.position.y};
        auto temp =
            std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= temp;
        direction.y /= temp;

        projectile.direction = direction;

        enemy_projectiles_.push_back(projectile);
        enemy.last_shoot_time = SDL_GetTicks();
      }

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
  enemy.shoot_cooldown = 1000;
  enemy.last_shoot_time = 0;
  enemies_.push_back(enemy);
}

void SceneMain::UpdateEnemyProjectiles(Uint32 delta_time) {
  for (auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end();) {
    auto& enemy = *it;
    auto distance = delta_time * enemy.speed;
    enemy.position.x += distance * enemy.direction.x;
    enemy.position.y += distance * enemy.direction.y;
    if (enemy.position.y > Game::Get().GetWindowHeight()) {
      it = enemy_projectiles_.erase(it);
    } else {
      it++;
    }
  }
}

void SceneMain::RenderEnemy() {
  for (const auto& enemy : enemies_) {
    SDL_FRect rect{enemy.position.x, enemy.position.y, enemy_texture_.width,
                   enemy_texture_.height};
    SDL_RenderCopyF(Game::Get().GetRenderer(), enemy_texture_.texture, nullptr,
                    &rect);
  }
}

void SceneMain::RenderEnemyProjectile() {
  for (const auto& projectile : enemy_projectiles_) {
    SDL_FRect rect{projectile.position.x, projectile.position.y,
                   enemy_projectile_texture_.width,
                   enemy_projectile_texture_.height};
    double angle = std::atan2(projectile.direction.y, projectile.direction.x) *
                       180 / M_PI -
                   90;
    SDL_RenderCopyExF(Game::Get().GetRenderer(),
                      enemy_projectile_texture_.texture, nullptr, &rect, angle,
                      nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
  }
}

}  // namespace spaceshooter

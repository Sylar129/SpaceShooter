// Copyright (c) 2025 Sylar129. All rights reserved

#include "environment.h"

#include <cmath>
#include <random>

#include "SDL_timer.h"
#include "game.h"
#include "player.h"

namespace spaceshooter {

namespace {
float getRandomFloat() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dis(0, 1);
  return dis(gen);
}
}  // namespace

Environment::Environment()
    : enemy_texture_("assets/image/insect-1.png"),
      enemy_projectile_texture_("assets/image/laser-1.png") {}

void Environment::SpawnEnemy(Player* player) {
  if (getRandomFloat() > 0.1) {
    return;
  }

  Enemy enemy;
  enemy.target_player = player;

  enemy.size = enemy_texture_.GetSize();
  enemy.size.x *= 0.25;
  enemy.size.y *= 0.25;

  enemy.position.x = getRandomFloat() * Game::Get().GetWindowWidth();
  enemy.position.y = 0;
  enemy.speed = 0.2;
  enemy.shoot_cooldown = 1000;
  enemy.last_shoot_time = 0;
  enemies_.push_back(enemy);
}

void Environment::Update(Uint32 delta_time) {
  UpdateEnemyProjectiles(delta_time);

  UpdateEnemy(delta_time);
}

void Environment::Render() {
  RenderEnemy();
  RenderEnemyProjectile();
}

void Environment::UpdateEnemy(Uint32 delta_time) {
  for (auto it = enemies_.begin(); it != enemies_.end();) {
    auto& enemy = *it;
    auto distance = delta_time * enemy.speed;
    enemy.position.y += distance;
    if (enemy.position.y > Game::Get().GetWindowHeight() || enemy.health <= 0) {
      it = enemies_.erase(it);
    } else {
      if (SDL_GetTicks() - enemy.last_shoot_time > enemy.shoot_cooldown) {
        EnemyProjectile projectile;
        projectile.size = enemy_projectile_texture_.GetSize();
        projectile.size.x *= 0.25;
        projectile.size.y *= 0.25;
        projectile.speed = 0.3;
        projectile.position = enemy.position;

        auto direction =
            SDL_FPoint{enemy.target_player->GetPosition().x - enemy.position.x,
                       enemy.target_player->GetPosition().y - enemy.position.y};
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

void Environment::UpdateEnemyProjectiles(Uint32 delta_time) {
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

void Environment::RenderEnemy() {
  for (const auto& enemy : enemies_) {
    SDL_FRect rect = enemy.GetRect();
    SDL_RenderCopyF(Game::Get().GetRenderer(), enemy_texture_.texture, nullptr,
                    &rect);
  }
}

void Environment::RenderEnemyProjectile() {
  for (const auto& projectile : enemy_projectiles_) {
    SDL_FRect rect = projectile.GetRect();
    double angle = std::atan2(projectile.direction.y, projectile.direction.x) *
                       180 / M_PI -
                   90;
    SDL_RenderCopyExF(Game::Get().GetRenderer(),
                      enemy_projectile_texture_.texture, nullptr, &rect, angle,
                      nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
  }
}
}  // namespace spaceshooter

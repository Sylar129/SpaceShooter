// Copyright (c) 2025 Sylar129. All rights reserved

#include "environment.h"

#include <random>

#include "SDL3/SDL_timer.h"
#include "game.h"
#include "player.h"

namespace spaceshooter {

namespace {
constexpr float kPi = 3.1415926f;

float getRandomFloat() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<float> dis(0, 1);
  return dis(gen);
}
}  // namespace

Environment::Environment()
    : enemy_texture_("assets/image/insect-1.png"),
      enemy_projectile_texture_("assets/image/laser-1.png"),
      explosion_texture_("assets/effect/explosion.png"),
      item_life_("assets/image/bonus_life.png") {}

void Environment::SetTargetPlayer(Player* player) { target_player_ = player; }

void Environment::SpawnEnemy() {
  if (getRandomFloat() > 0.02 || !target_player_->IsAlive()) {
    return;
  }

  Enemy enemy;
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

void Environment::Update(Uint64 delta_time) {
  if (!target_player_->IsAlive()) {
    return;
  }
  UpdateEnemyProjectiles(delta_time);

  UpdateEnemy(delta_time);

  UpdateExplosion();

  UpdateItems(delta_time);
}

void Environment::Render() {
  RenderItems();
  RenderExplosion();
  RenderEnemy();
  RenderEnemyProjectile();
}

void Environment::UpdateEnemy(Uint64 delta_time) {
  auto current_time = SDL_GetTicks();
  auto player_rect = target_player_->GetRect();
  for (auto it = enemies_.begin(); it != enemies_.end();) {
    auto& enemy = *it;
    auto distance = delta_time * enemy.speed;
    enemy.position.y += distance;
    if (enemy.position.y > Game::Get().GetWindowHeight()) {
      it = enemies_.erase(it);
    } else if (enemy.health <= 0) {
      Explosion explosion;
      explosion.size = explosion_texture_.GetSize();
      explosion.total_frame = explosion.size.x / explosion.size.y;
      explosion.size.x = explosion.size.y;

      explosion.start_time = current_time;
      explosion.position = SDL_FPoint{
          enemy.position.x + 0.5f * enemy.size.x - 0.5f * explosion.size.x,
          enemy.position.y + 0.5f * enemy.size.y - 0.5f * explosion.size.y};
      Game::Get().GetMixer().PlayAudio("enemy_explode");

      explosions_.push_back(explosion);

      if (getRandomFloat() > 0.5) {
        DropItem(enemy);
      }

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
            SDL_FPoint{target_player_->GetPosition().x - enemy.position.x,
                       target_player_->GetPosition().y - enemy.position.y};
        auto temp =
            std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= temp;
        direction.y /= temp;

        projectile.direction = direction;

        Game::Get().GetMixer().PlayAudio("enemy_shoot");

        enemy_projectiles_.push_back(projectile);
        enemy.last_shoot_time = SDL_GetTicks();
      }

      auto projectile_rect = enemy.GetRect();
      if (SDL_HasRectIntersectionFloat(&projectile_rect, &player_rect)) {
        target_player_->TakeDamage(1);
        it = enemies_.erase(it);
        continue;
      }

      it++;
    }
  }
}

void Environment::UpdateEnemyProjectiles(Uint64 delta_time) {
  auto player_rect = target_player_->GetRect();
  for (auto it = enemy_projectiles_.begin(); it != enemy_projectiles_.end();) {
    auto& projectile = *it;
    auto distance = delta_time * projectile.speed;
    projectile.position.x += distance * projectile.direction.x;
    projectile.position.y += distance * projectile.direction.y;
    if (projectile.position.y > Game::Get().GetWindowHeight()) {
      it = enemy_projectiles_.erase(it);
      continue;
    }
    auto projectile_rect = projectile.GetRect();
    if (SDL_HasRectIntersectionFloat(&projectile_rect, &player_rect)) {
      target_player_->TakeDamage(1);
      it = enemy_projectiles_.erase(it);
      continue;
    }

    it++;
  }
}

void Environment::RenderEnemy() {
  for (const auto& enemy : enemies_) {
    SDL_FRect rect = enemy.GetRect();
    SDL_RenderTexture(Game::Get().GetRenderer(), enemy_texture_.texture,
                      nullptr, &rect);
  }
}

void Environment::RenderEnemyProjectile() {
  for (const auto& projectile : enemy_projectiles_) {
    SDL_FRect rect = projectile.GetRect();
    double angle =
        std::atan2(projectile.direction.y, projectile.direction.x) * 180 / kPi -
        90;
    SDL_RenderTextureRotated(Game::Get().GetRenderer(),
                             enemy_projectile_texture_.texture, nullptr, &rect,
                             angle, nullptr, SDL_FlipMode::SDL_FLIP_NONE);
  }
}

void Environment::UpdateExplosion() {
  Uint64 current_time = SDL_GetTicks();
  for (auto it = explosions_.begin(); it != explosions_.end();) {
    auto& explosion = *it;
    explosion.current_frame =
        (current_time - explosion.start_time) * explosion.fps / 1000;
    if (explosion.current_frame >= explosion.total_frame) {
      it = explosions_.erase(it);
    } else {
      ++it;
    }
  }
}

void Environment::RenderExplosion() {
  for (const auto& explosion : explosions_) {
    SDL_FRect src_rect = explosion.GetSourceRect();
    SDL_FRect dst_rect = explosion.GetTargetRect();
    SDL_RenderTexture(Game::Get().GetRenderer(), explosion_texture_.texture,
                      &src_rect, &dst_rect);
  }
}

void Environment::DropItem(const Enemy& enemy) {
  Item item;
  item.size = item_life_.GetSize();
  item.size.x *= 0.25;
  item.size.y *= 0.25;
  item.type = Item::Type::kLife;
  item.position.x = enemy.position.x + enemy.size.x * 0.5f - item.size.x * 0.5f;
  item.position.y = enemy.position.y + enemy.size.y * 0.5f - item.size.y * 0.5f;

  float angle = getRandomFloat() * 2 * kPi;
  item.direction.x = std::cos(angle);
  item.direction.y = std::sin(angle);

  item.speed = 0.1;

  items_.push_back(item);
}

void Environment::UpdateItems(Uint32 delta_time) {
  auto player_rect = target_player_->GetRect();

  for (auto it = items_.begin(); it != items_.end();) {
    auto& item = *it;
    auto item_rect = item.GetRect();
    if (Game::Get().IsOutsideWindow(item_rect) && item.rebound_time == 0) {
      it = items_.erase(it);
    } else if (SDL_HasRectIntersectionFloat(&player_rect, &item_rect)) {
      target_player_->GetItem(item);
      Game::Get().GetMixer().PlayAudio("get_item");
      it = items_.erase(it);
    } else {
      if (item.position.x < 0 ||
          item.position.x > Game::Get().GetWindowWidth() - item.size.x) {
        item.rebound_time--;
        item.direction.x = -item.direction.x;
      }
      if (item.position.y < 0 ||
          item.position.y > Game::Get().GetWindowWidth() - item.size.y) {
        item.rebound_time--;
        item.direction.y = -item.direction.y;
      }
      auto distance = item.speed * delta_time;

      item.position.x += distance * item.direction.x;
      item.position.y += distance * item.direction.y;

      ++it;
    }
  }
}

void Environment::RenderItems() {
  for (const auto& item : items_) {
    SDL_FRect rect = item.GetRect();
    SDL_RenderTexture(Game::Get().GetRenderer(), item_life_.texture, nullptr,
                      &rect);
  }
}

}  // namespace spaceshooter

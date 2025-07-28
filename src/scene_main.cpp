// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include "environment.h"
#include "game.h"

namespace spaceshooter {

SceneMain::SceneMain() { Environment::Get().SetTargetPlayer(&player_); }

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) { player_.HandleEvent(event); }

void SceneMain::Update(Uint64 delta_time) {
  player_.Update(delta_time);

  Environment::Get().Update(delta_time);

  Environment::Get().SpawnEnemy();
}

void SceneMain::Render() {
  player_.Render();

  Environment::Get().Render();
}

void SceneMain::Clean() {}

}  // namespace spaceshooter

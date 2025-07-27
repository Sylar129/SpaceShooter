// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include <random>

#include "environment.h"
#include "game.h"

namespace spaceshooter {

SceneMain::SceneMain() {}

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) { player_.HandleEvent(event); }

void SceneMain::Update(Uint32 delta_time) {
  player_.Update(delta_time);

  Environment::Get().Update(delta_time);

  Environment::Get().SpawnEnemy(&player_);
}

void SceneMain::Render() {
  player_.Render();

  Environment::Get().Render();
}

void SceneMain::Clean() {}

}  // namespace spaceshooter

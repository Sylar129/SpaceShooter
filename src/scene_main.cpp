// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

#include <SDL_image.h>

#include "game.h"

namespace spaceshooter {

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) {}

void SceneMain::Update() {}

void SceneMain::Render() { player_.Render(); }

void SceneMain::Clean() {}

}  // namespace spaceshooter

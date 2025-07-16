// Copyright (c) 2025 Sylar129. All rights reserved

#include "scene_main.h"

namespace spaceshooter {

void SceneMain::Init() {}

void SceneMain::HandleEvent(SDL_Event* event) { player_.HandleEvent(event); }

void SceneMain::Update() { player_.Update(); }

void SceneMain::Render() { player_.Render(); }

void SceneMain::Clean() {}

}  // namespace spaceshooter

// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>

#include "scene.h"

namespace spaceshooter {

class Game {
 public:
  Game(int width,int height);
  ~Game();

  void Init();
  void Run();
  void Clean();
  void ChangeScene(std::shared_ptr<Scene> scene);

 private:
  void HandleEvent();
  void Update();
  void Render();

  bool is_running_;
  std::shared_ptr<Scene> current_scene_;
  SDL_Window* window_;
  int window_width_;
  int window_height_;
  SDL_Renderer* renderer_;
};

}  // namespace spaceshooter

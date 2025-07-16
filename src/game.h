// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <memory>

#include "SDL_render.h"
#include "SDL_video.h"
#include "scene.h"

namespace spaceshooter {

class Game {
 public:
  Game(const Game&) = delete;
  Game& operator=(const Game&) = delete;
  ~Game();

  static Game& Get() {
    static Game game(600, 800);
    return game;
  }

  void Init();
  void Run();
  void Clean();
  void ChangeScene(std::shared_ptr<Scene> scene);

  SDL_Window* GetWindow() const { return window_; }
  SDL_Renderer* GetRenderer() const { return renderer_; }
  int GetWindowWidth() const { return window_width_; }
  int GetWindowHeight() const { return window_height_; }

 private:
  Game(int width, int height);
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

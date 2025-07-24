// Copyright (c) 2025 Sylar129. All rights reserved

#include "game.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_log.h"
#include "SDL_stdinc.h"
#include "SDL_timer.h"
#include "scene_main.h"

namespace spaceshooter {

Game::Game(int width, int height)
    : is_running_(false), window_width_(width), window_height_(height) {}

Game::~Game() {}

void Game::Init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
    return;
  }

  window_ = SDL_CreateWindow("SpaceShooter", SDL_WINDOWPOS_CENTERED,
                             SDL_WINDOWPOS_CENTERED, window_width_,
                             window_height_, SDL_WINDOW_SHOWN);
  if (!window_) {
    SDL_Log("SDL_CreateWindow Error: %s\n", SDL_GetError());
    return;
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer_) {
    SDL_Log("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return;
  }

  constexpr int kImgInitFlag = IMG_INIT_PNG;
  if (IMG_Init(kImgInitFlag) != kImgInitFlag) {
    SDL_Log("IMG_Init Error: %s\n", IMG_GetError());
    return;
  }

  is_running_ = true;
  current_scene_ = std::make_shared<SceneMain>();
  current_scene_->Init();
}

void Game::Run() {
  constexpr bool kEnableConstantFps = true;
  constexpr Uint32 kFps = 60;
  constexpr Uint32 kFrameTime = 1000 / kFps;

  Uint32 delta_time = 0;
  while (is_running_) {
    Uint32 start_time = SDL_GetTicks();
    HandleEvent();
    Update(delta_time);
    Render();
    delta_time = SDL_GetTicks() - start_time;
    // SDL_Log("delta time: %d", delta_time);
    if constexpr (kEnableConstantFps) {
      if (delta_time < kFrameTime) {
        SDL_Delay(kFrameTime - delta_time);
        delta_time = kFrameTime;
      } else {
        SDL_LogWarn(0, "large frame time: %d", delta_time);
      }
    }
  }
}

void Game::Clean() {
  IMG_Quit();

  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Game::ChangeScene(std::shared_ptr<Scene> scene) {
  if (!scene) {
    return;
  }
  current_scene_->Clean();

  current_scene_ = scene;
  current_scene_->Init();
}

void Game::HandleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      is_running_ = false;
    }
    current_scene_->HandleEvent(&event);
  }
}

void Game::Update(Uint32 delta_time) { current_scene_->Update(delta_time); }

void Game::Render() {
  SDL_RenderClear(renderer_);
  current_scene_->Render();
  SDL_RenderPresent(renderer_);
}

}  // namespace spaceshooter

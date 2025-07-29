// Copyright (c) 2025 Sylar129. All rights reserved

#include "game.h"

#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "scene_main.h"

namespace spaceshooter {

Game::Game(int width, int height)
    : is_running_(false), window_width_(width), window_height_(height) {}

Game::~Game() {}

void Game::Init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("SDL_Init Error: %s\n", SDL_GetError());
    return;
  }

  if (!SDL_CreateWindowAndRenderer("SpaceShooter", window_width_,
                                   window_height_, SDL_WINDOW_RESIZABLE,
                                   &window_, &renderer_)) {
    SDL_Log("SDL_CreateWindowAndRenderer Error: %s\n", SDL_GetError());
    return;
  }

  asset_store_ = std::make_unique<AssetStore>(renderer_);
  asset_store_->LoadTexture("assets/image/insect-1.png");
  asset_store_->LoadTexture("assets/image/laser-1.png");
  asset_store_->LoadTexture("assets/effect/explosion.png");

  is_running_ = true;
  current_scene_ = std::make_shared<SceneMain>();
  current_scene_->Init();
}

void Game::Run() {
  constexpr bool kEnableConstantFps = true;
  constexpr Uint64 kFps = 60;
  constexpr Uint64 kFrameTime = 1000 / kFps;

  Uint64 delta_time = 0;
  while (is_running_) {
    Uint64 start_time = SDL_GetTicks();
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

AssetStore& Game::GetAssetStore() const { return *asset_store_; }

void Game::HandleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      is_running_ = false;
    }
    current_scene_->HandleEvent(&event);
  }
}

void Game::Update(Uint64 delta_time) { current_scene_->Update(delta_time); }

void Game::Render() {
  SDL_RenderClear(renderer_);
  current_scene_->Render();
  SDL_RenderPresent(renderer_);
}

}  // namespace spaceshooter

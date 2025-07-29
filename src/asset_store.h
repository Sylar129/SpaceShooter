// Copyright (c) 2025 Sylar129. All rights reserved

#pragma once

#include <string>
#include <unordered_map>

#include "SDL3/SDL_render.h"

namespace spaceshooter {
class AssetStore {
 public:
  AssetStore(SDL_Renderer* renderer);
  ~AssetStore();

  void LoadTexture(const std::string& file_path);

  SDL_Texture* GetTexture(const std::string& file_path) const;

  void Clean();

 private:
  SDL_Renderer* renderer_;
  std::unordered_map<std::string, SDL_Texture*> textures_;
};
}  // namespace spaceshooter

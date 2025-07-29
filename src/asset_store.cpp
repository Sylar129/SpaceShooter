// Copyright (c) 2025 Sylar129. All rights reserved

#include "asset_store.h"

#include "SDL3_image/SDL_image.h"

namespace spaceshooter {

AssetStore::AssetStore(SDL_Renderer* renderer) : renderer_(renderer) {}

AssetStore::~AssetStore() { Clean(); }

void AssetStore::LoadTexture(const std::string& file_path) {
  auto texture = IMG_LoadTexture(renderer_, file_path.c_str());
  if (!texture) {
    SDL_LogWarn(0, "Create texture(%s) failed!", file_path.c_str());
    return;
  }
  textures_.emplace(file_path, texture);
}

SDL_Texture* AssetStore::GetTexture(const std::string& file_path) const {
  return textures_.at(file_path);
}

void AssetStore::Clean(){
  for (const auto& kv : textures_) {
    SDL_DestroyTexture(kv.second);
  }
  textures_.clear();
}

}  // namespace spaceshooter

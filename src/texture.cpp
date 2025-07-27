// Copyright (c) 2025 Sylar129. All rights reserved

#include "texture.h"

#include "SDL_image.h"
#include "game.h"

namespace spaceshooter {

Texture::Texture(const std::string& file_path)
    : texture(IMG_LoadTexture(Game::Get().GetRenderer(), file_path.c_str())) {
  if (!texture) {
    SDL_LogWarn(0, "Create texture(%s) failed!", file_path.c_str());
  }
}

Texture::~Texture() { SDL_DestroyTexture(texture); }

SDL_FPoint Texture::GetSize() const {
  SDL_FPoint size;
  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  size.x = w;
  size.y = h;
  return size;
}

}  // namespace spaceshooter

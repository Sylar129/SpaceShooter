// Copyright (c) 2025 Sylar129. All rights reserved

#include "texture.h"

#include "SDL_image.h"
#include "game.h"

namespace spaceshooter {

Texture::Texture(const std::string& file_path)
    : texture(IMG_LoadTexture(Game::Get().GetRenderer(), file_path.c_str())) {
  if (!texture) {
    SDL_LogWarn(0, "Create texture(%s) failed!", file_path.c_str());
    return;
  }

  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  width = w;
  height = h;
}

Texture ::~Texture() { SDL_DestroyTexture(texture); }

}  // namespace spaceshooter

// Copyright (c) 2025 Sylar129. All rights reserved

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <iostream>

int main(int, char**) {
  // init
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "SDL_Init Error" << SDL_GetError() << std::endl;
    return -1;
  }

  // set up
  constexpr SDL_Rect kWindowRect = {800, 600, 800, 600};
  SDL_Window* window =
      SDL_CreateWindow("Hello world!", kWindowRect.x, kWindowRect.y,
                       kWindowRect.w, kWindowRect.h, SDL_WINDOW_SHOWN);
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  constexpr int kImgInitFlag = IMG_INIT_JPG | IMG_INIT_PNG;
  if (IMG_Init(kImgInitFlag) != kImgInitFlag) {
    std::cerr << "IMG_Init Error" << IMG_GetError() << std::endl;
    return -1;
  }

  constexpr int kMixInitFlag = MIX_INIT_OGG;
  if (Mix_Init(kMixInitFlag) != kMixInitFlag) {
    std::cerr << "IMG_Init Error" << Mix_GetError() << std::endl;
    return -1;
  }

  if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                    MIX_DEFAULT_CHANNELS, MIX_MAX_VOLUME) != 0) {
    std::cerr << "Mix_OpenAudio Error" << Mix_GetError() << std::endl;
    return -1;
  }

  Mix_Music* music =
      Mix_LoadMUS("assets/music/03_Racing_Through_Asteroids_Loop.ogg");
  Mix_PlayMusic(music, -1);

  if (TTF_Init() != 0) {
    std::cerr << "TTF_Init Error" << TTF_GetError() << std::endl;
    return -1;
  }
  TTF_Font* font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 16);
  SDL_Color color{255, 255, 255, 255};
  SDL_Surface* surface = TTF_RenderUTF8_Solid(font, "hello SDL!", color);
  SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, surface);

  // load picture
  SDL_Texture* texture =
      IMG_LoadTexture(renderer, "assets/image/bonus_life.png");

  // render loop
  while (true) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    // text
    SDL_Rect text_rect = {300, 300, surface->w, surface->h};
    SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect);

    SDL_RenderPresent(renderer);
  }

  // clean up
  // font
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(text_texture);
  TTF_CloseFont(font);
  TTF_Quit();

  // music
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  Mix_Quit();

  // image
  SDL_DestroyTexture(texture);
  IMG_Quit();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  return 0;
}

// Copyright (c) 2025 Sylar129. All rights reserved

#include <iostream>

#include "game.h"

int main(int, char**) {
  spaceshooter::Game& game = spaceshooter::Game::Get();

  game.Init();
  game.Run();
  game.Clean();

  return 0;
}

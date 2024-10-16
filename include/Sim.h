#pragma once

#include "Elements.h"
#include <SDL2/SDL.h>

inline const int FPS = 60;
inline const int D_DELTA = 1000 / FPS;

class Sim {
  SDL_Window *window;
  SDL_Renderer *renderer;

  bool running = true;

  CellularMatrix matrix;
  B_TYPE type;
  int mouseX, mouseY;
  int mouseState;

public:
  void init();
  void handleEvents();
  void update();
  void render();
  void run();
};

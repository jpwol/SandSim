#pragma once

#include "ParticleSystem.h"
#include "Renderer.h"

using Brush = ParticleType;

class Sim {
 public:
  Sim(int _width, int _height)
      : width(_width),
        height(_height),
        renderer(_width, _height),
        particleSystem(_width, _height) {}
  void run();

 private:
  ParticleSystem particleSystem;
  Renderer renderer;
  Brush brush = Brush::Sand;
  void handleInput(SDL_Event& e);

  int width, height;
  bool running = true;
  int mouseX, mouseY;

  bool updating = true;
};

#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "Particle.h"

class Renderer {
 public:
  Renderer(int width, int height);
  ~Renderer();

  void clear();
  void renderParticles(const std::vector<Particle>& particles, uint8_t size);
  void present();

 private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
};

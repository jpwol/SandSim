#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include "Particle.h"
#include "ParticleSystem.h"

class Renderer {
 public:
  Renderer(int width, int height);
  ~Renderer();

  void clear();
  void renderParticles(const ParticleSystem& ps);
  void present();

 private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
};

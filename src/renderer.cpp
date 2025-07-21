#include "Renderer.h"

#include <iostream>

Renderer::Renderer(int width, int height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Error: SDL could not initialize: " << SDL_GetError()
              << std::endl;
  }

  window = SDL_CreateWindow("SandSim", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, width, height, 0);
  if (window == NULL) {
    std::cerr << "Error: Window could not be created: " << SDL_GetError()
              << std::endl;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    std::cerr << "Error: Renderer could not be created: " << SDL_GetError()
              << std::endl;
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255);
  SDL_RenderClear(renderer);
}

void Renderer::renderParticles(const ParticleSystem& ps) {
  // change magic numbers to variable values!!!
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           ps.gridWidth, ps.gridHeight);
  uint32_t* pixels;
  int pitch;
  SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch);
  memset(pixels, 0xFF121212, ps.gridWidth * ps.gridHeight * sizeof(uint32_t));

  for (const auto& p : ps.getParticles()) {
    int cellX = p.x / ps.particleSize;
    int cellY = p.y / ps.particleSize;
    switch (p.type) {
      case ParticleType::Sand:
        pixels[cellY * ps.gridWidth + cellX] = sandColors[p.colorVariantIndex];
        break;
      case ParticleType::Water:
        pixels[cellY * ps.gridWidth + cellX] = waterColors[p.colorVariantIndex];
        break;
      case ParticleType::Stone:
        pixels[cellY * ps.gridWidth + cellX] = stoneColors[p.colorVariantIndex];
        break;
      default:
        break;
    }
  }
  SDL_UnlockTexture(texture);
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_DestroyTexture(texture);
}

void Renderer::present() { SDL_RenderPresent(renderer); }

SDL_Window* Renderer::getWindow() { return window; }

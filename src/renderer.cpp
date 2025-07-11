#include "Renderer.h"

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>

#include <iostream>

#include "ParticleSystem.h"

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

void Renderer::renderParticles(const std::vector<Particle>& particles,
                               uint8_t size) {
  // change magic numbers to variable values!!!
  SDL_Texture* texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STREAMING, 1280 / 2, 720 / 2);
  uint32_t* pixels;
  int pitch;
  SDL_LockTexture(texture, nullptr, (void**)&pixels, &pitch);
  memset(pixels, 0xFF121212, (1280 / 2) * (720 / 2) * sizeof(uint32_t));

  for (auto& p : particles) {
    int cellX = p.x / 2;
    int cellY = p.y / 2;
    pixels[cellY * (1280 / 2) + cellX] = p.color;
  }
  SDL_UnlockTexture(texture);
  SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  SDL_DestroyTexture(texture);
  // for (const auto& p : particles) {
  //   uint8_t r = (p.color >> 24) & 0xFF;
  //   uint8_t g = (p.color >> 16) & 0xFF;
  //   uint8_t b = (p.color >> 8) & 0xFF;
  //   uint8_t a = p.color & 0xFF;

  // SDL_SetRenderDrawColor(renderer, r, g, b, a);
  // SDL_Rect rect{p.x, p.y, size, size};
  // SDL_RenderFillRect(renderer, &rect);
  // }
}

void Renderer::present() { SDL_RenderPresent(renderer); }

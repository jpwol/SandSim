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
  SDL_Window* getWindow();

 private:
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;

  static constexpr int numVariants = 16;

  std::array<uint32_t, numVariants> sandColors = {
      0xA89563FF, 0xB0996AFF, 0xA18D59FF, 0xAF9266FF, 0xAA8F5EFF, 0xB59B6EFF,
      0xA88B5BFF, 0xAC915FFF, 0xB3976BFF, 0xA78E5DFF, 0xB29A6AFF, 0xA99260FF,
      0xB4976AFF, 0xA98F5FFF, 0xB19668FF, 0xAA9060FF,
  };

  std::array<uint32_t, numVariants> waterColors = {
      0x1E90FFFF, 0x00BFFFFF, 0x87CEFAFF, 0x4682B4FF, 0x5F9EA0FF, 0x6495EDFF,
      0x4169E1FF, 0x00CED1FF, 0x40E0D0FF, 0x1CA9C9FF, 0x007BA7FF, 0x6CA6CDFF,
      0x468499FF, 0x2E8B57FF, 0x104E8BFF, 0x0E4D92FF,
  };
  std::array<uint32_t, numVariants> stoneColors = {
      0x6A6A6AFF, 0x5E5E5EFF, 0x787878FF, 0x4F4F4FFF, 0x696969FF, 0x606060FF,
      0x707070FF, 0x505050FF, 0x808080FF, 0x585858FF, 0x686868FF, 0x747474FF,
      0x444444FF, 0x7A7A7AFF, 0x666666FF, 0x5A5A5AFF,
  };
};

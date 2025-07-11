#pragma once

#include <cstdint>
#include <cstdlib>

enum class ParticleType { None, Sand, Water, Stone };

struct Particle {
  int x, y;
  ParticleType type;
  uint32_t color;
  int colorVariantIndex = rand() % 16;

  bool active = true;
};

#pragma once

#include <cstdint>

enum class ParticleType { None, Sand, Water, Stone };

struct Particle {
  int x, y;
  ParticleType type;
  uint32_t color;

  bool active = true;
  float velocity = 1.0;
};

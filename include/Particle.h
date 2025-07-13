#pragma once

#include <cstdint>
#include <cstdlib>

enum class ParticleType { None, Sand, Water, Stone };

struct Particle {
  int x, y;
  ParticleType type;
  int colorVariantIndex = rand() % 16;

  bool active = true;
  bool queued = false;
};

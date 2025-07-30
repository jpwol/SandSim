#pragma once

#include <cstdint>
#include <cstdlib>

#include "Util.h"

enum class ParticleType { None, Sand, Water, Stone };

struct Particle {
  int x, y;
  ParticleType type;
  Vec2 vel;
  int colorVariantIndex = rand() % 16;

  bool active = true;
  bool queued = false;
};

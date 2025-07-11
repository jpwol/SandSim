#pragma once
#include <array>
#include <vector>

#include "Particle.h"

class ParticleSystem {
 public:
  ParticleSystem(int _width, int _height)
      : width(_width),
        height(_height),
        gridWidth(_width / particleSize),
        gridHeight(_height / particleSize) {
    particles.reserve(gridWidth * gridHeight);
    grid.resize(gridWidth * gridHeight, nullptr);
  }
  void addParticle(int x, int y, ParticleType type, uint32_t color);
  void update();
  const std::vector<Particle>& getParticles() const;
  unsigned int getParticleCount();
  unsigned int getCapacity();

  static constexpr uint8_t particleSize = 2;

  // private:
  int width, height;
  int gridWidth, gridHeight;
  std::vector<Particle> particles;
  std::vector<Particle*> grid;
  std::vector<Particle*> activeParticles;
};

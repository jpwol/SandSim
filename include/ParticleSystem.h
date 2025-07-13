#pragma once
#include <array>
#include <vector>

#include "Particle.h"
#include "Util.h"

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
  void addParticle(int x, int y, ParticleType type);
  void update();
  const std::vector<Particle>& getParticles() const;
  unsigned int getParticleCount();
  unsigned int getCapacity();

  static constexpr uint8_t particleSize = 2;

  // private:
  int width, height;
  int gridWidth, gridHeight;
  float sandFriction = 0.3f;
  std::vector<Particle> particles;
  std::vector<Particle*> grid;
  std::vector<Particle*> activeParticles;
  std::vector<Particle*> queuedParticles;

  void updateSand(Particle* p);
  void reactivateNeighbors(Particle* p);

  static constexpr int numVariants = 16;

  std::array<uint32_t, numVariants> sandColors = {
      0xA89563FF, 0xB0996AFF, 0xA18D59FF, 0xAF9266FF, 0xAA8F5EFF, 0xB59B6EFF,
      0xA88B5BFF, 0xAC915FFF, 0xB3976BFF, 0xA78E5DFF, 0xB29A6AFF, 0xA99260FF,
      0xB4976AFF, 0xA98F5FFF, 0xB19668FF, 0xAA9060FF,
  };
};

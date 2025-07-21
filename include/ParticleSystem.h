#pragma once
#include <SDL2/SDL.h>

#include <array>
#include <vector>

#include "GridHelper.h"
#include "Particle.h"
#include "Util.h"

class ParticleSystem {
 public:
  ParticleSystem(int _width, int _height)
      : width(_width),
        height(_height),
        gridWidth(_width / particleSize),
        gridHeight(_height / particleSize),
        grid(gridWidth, gridHeight, particleSize) {
    particles.reserve(gridWidth * gridHeight);
  }

  const int gridWidth, gridHeight;

  void addParticle(int x, int y, ParticleType type);
  void update();
  const std::vector<Particle>& getParticles() const;
  unsigned int getParticleCount();

  static constexpr uint8_t particleSize = 2;

  void moveParticle(int x1, int y1, int x2, int y2);

 private:
  int width, height;
  float sandFriction = 0.2f;
  GridHelper grid;
  std::vector<Particle> particles;
  std::vector<Particle*> activeParticles;
  std::vector<Particle*> queuedParticles;

  void updateSand(Particle* p);
  void updateWater(Particle* p);
  void updateStone(Particle* p);
  void reactivateNeighbors(Particle* p);
};

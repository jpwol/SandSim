#pragma once
#include <vector>

#include "Particle.h"

class GridHelper {
 public:
  GridHelper(int _width, int _height, int _particleSize)
      : gridWidth(_width), gridHeight(_height), particleSize(_particleSize) {
    grid.resize(_width * _height, nullptr);
  }

  // returns true if cell (cellX, cellY) contains a particle, false otherwise
  bool queryGrid(int cellX, int cellY);

  // Returns a pointer to particle at (cellX, cellY)
  Particle* getParticle(int cellX, int cellY);

  // Places the last particle added to the particles vector into the grid at
  // the corresponding cell coordinates
  void placeParticle(int cellX, int cellY, std::vector<Particle>& vec);

  // moves a particle from cell (x1, y1) to cell (x2, y2) in the grid
  void moveParticle(int x1, int y1, int x2, int y2);
  void swapParticle(int x1, int y1, int x2, int y2);
  ParticleType getTypeAtCell(int cellX, int cellY);

 private:
  int particleSize;
  int gridWidth, gridHeight;
  std::vector<Particle*> grid;
};

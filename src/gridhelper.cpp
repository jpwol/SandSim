#include "GridHelper.h"

// Returns true if a particle exists at (cellX, cellY), false otherwise
bool GridHelper::queryGrid(int cellX, int cellY) {
  if (grid[cellY * gridWidth + cellX] == nullptr) return true;

  return false;
}

Particle* GridHelper::getParticle(int cellX, int cellY) {
  return grid[cellY * gridWidth + cellX];
}

void GridHelper::placeParticle(int cellX, int cellY,
                               std::vector<Particle>& vec) {
  grid[cellY * gridWidth + cellX] = &vec.back();
}

void GridHelper::moveParticle(int x1, int y1, int x2, int y2) {
  grid[y2 * gridWidth + x2] = grid[y1 * gridWidth + x1];
  grid[y1 * gridWidth + x1] = nullptr;
}

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
  Particle* p = grid[y1 * gridWidth + x1];
  grid[y2 * gridWidth + x2] = grid[y1 * gridWidth + x1];
  grid[y1 * gridWidth + x1] = nullptr;
  grid[y2 * gridWidth + x2]->x += (x2 - x1) * particleSize;
  grid[y2 * gridWidth + x2]->y += (y2 - y1) * particleSize;
}

void GridHelper::swapParticle(int x1, int y1, int x2, int y2) {
  Particle* p1 = grid[y1 * gridWidth + x1];
  Particle* p2 = grid[y2 * gridWidth + x2];
  grid[y2 * gridWidth + x2] = p1;
  grid[y1 * gridWidth + x1] = p2;

  p1->x += (x2 - x1) * particleSize;
  p1->y += (y2 - y1) * particleSize;

  p2->x += (x1 - x2) * particleSize;
  p2->y += (y1 - y2) * particleSize;
}

ParticleType GridHelper::getTypeAtCell(int cellX, int cellY) {
  return grid[cellY * gridWidth + cellX]->type;
}

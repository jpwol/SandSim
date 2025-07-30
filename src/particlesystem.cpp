#include "ParticleSystem.h"

#include <iostream>

void ParticleSystem::addParticle(int x, int y, ParticleType type) {
  int cellX = x / particleSize;
  int cellY = y / particleSize;
  if (grid.queryGrid(cellX, cellY)) {
    particles.emplace_back(Particle{x, y, type});
    grid.placeParticle(cellX, cellY, particles);
    activeParticles.push_back(&particles.back());
  } else {
    return;
  }
}

void ParticleSystem::update() {
  for (auto& p : activeParticles) {
    switch (p->type) {
      case ParticleType::Sand:
        updateSand(p);
        break;
      case ParticleType::Water:
        updateWater(p);
        break;
      case ParticleType::Stone:
        updateStone(p);
        break;
      default:
        break;
    }
  }
  for (auto& p : queuedParticles) {
    activeParticles.push_back(p);
    p->queued = false;
  }
  queuedParticles.clear();
  std::erase_if(activeParticles, [](Particle* p) { return !p->active; });
}

void ParticleSystem::updateSand(Particle* p) {
  int cellX = p->x / particleSize;
  int cellY = p->y / particleSize;
  if (cellY + 1 < gridHeight) {
    if (grid.queryGrid(cellX, cellY + 1)) {
      p->y += particleSize;

      grid.moveParticle(cellX, cellY, cellX, cellY + 1);

      reactivateNeighbors(p);

      return;
    }
    if (grid.getTypeAtCell(cellX, cellY + 1) == ParticleType::Water) {
      Particle* p2 = grid.getParticle(cellX, cellY + 1);
      grid.swapParticle(cellX, cellY, cellX, cellY + 1);
      p->y += particleSize;
      p2->y -= particleSize;

      reactivateNeighbors(p);
      return;
    }
    if (cellX - 1 >= 0 && grid.queryGrid(cellX - 1, cellY + 1)) {
      if (randomFloat() <= sandFriction) return;
      p->x -= particleSize;
      p->y += particleSize;

      grid.moveParticle(cellX, cellY, cellX - 1, cellY + 1);

      reactivateNeighbors(p);

      return;
    }
    if (cellX + 1 <= gridWidth - 1 && grid.queryGrid(cellX + 1, cellY + 1)) {
      if (randomFloat() <= sandFriction) return;
      p->x += particleSize;
      p->y += particleSize;

      grid.moveParticle(cellX, cellY, cellX + 1, cellY + 1);

      reactivateNeighbors(p);

      return;
    }

    p->active = false;
    return;
  } else {
    if (p->active && p->y + particleSize >= height) {
      p->y = height - particleSize;
      p->active = false;
    }
  }
}

void ParticleSystem::updateWater(Particle* p) {
  int cellX = p->x / particleSize;
  int cellY = p->y / particleSize;

  if (cellY + 1 < gridHeight) {
    if (grid.queryGrid(cellX, cellY + 1)) {
      p->y += particleSize;
      grid.moveParticle(cellX, cellY, cellX, cellY + 1);

      reactivateNeighbors(p);
      return;
    }
    if (cellX - 1 >= 0 && grid.queryGrid(cellX - 1, cellY)) {
      p->x -= particleSize;
      grid.moveParticle(cellX, cellY, cellX - 1, cellY);
      reactivateNeighbors(p);
      return;
    }
    if (cellX + 1 <= gridWidth - 1 && grid.queryGrid(cellX + 1, cellY)) {
      p->x += particleSize;
      grid.moveParticle(cellX, cellY, cellX + 1, cellY);
      reactivateNeighbors(p);
      return;
    }

    p->active = false;
    return;
  } else {
    if (p->active && p->y + particleSize >= height) {
      p->y = height - particleSize;
      p->active = false;
    }
  }
}

void ParticleSystem::updateStone(Particle* p) { p->active = false; }

void ParticleSystem::reactivateNeighbors(Particle* p) {
  int cellX = p->x / particleSize;
  int cellY = p->y / particleSize;

  for (int y = 0; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (y == 0 && x == 0) continue;
      if (cellY - y < 0 || cellY + y >= gridHeight || cellX - x < 0 ||
          cellX + x >= gridWidth)
        continue;

      Particle* u = grid.getParticle(cellX + x, cellY + y);
      if (u != nullptr) {
        if (u->active == false && u->queued == false) {
          u->active = true;
          u->queued = true;
          queuedParticles.push_back(u);
        }
      }
    }
  }
}

const std::vector<Particle>& ParticleSystem::getParticles() const {
  return particles;
}

unsigned int ParticleSystem::getParticleCount() { return particles.size(); }

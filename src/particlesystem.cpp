#include "ParticleSystem.h"

void ParticleSystem::addParticle(int x, int y, ParticleType type) {
  int cellX = x / particleSize;
  int cellY = y / particleSize;
  if (grid[cellY * gridWidth + cellX] == nullptr) {
    particles.push_back({x, y, type});
    grid[cellY * gridWidth + cellX] = &particles.back();
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
    Particle* _this = grid[cellY * gridWidth + cellX];
    Particle* a = grid[(cellY + 1) * gridWidth + cellX];        // one down
    Particle* b = grid[(cellY + 1) * gridWidth + (cellX - 1)];  // one left
    Particle* c = grid[(cellY + 1) * gridWidth + (cellX + 1)];  // one right

    if (a == nullptr) {
      p->y += particleSize;

      grid[(cellY + 1) * gridWidth + cellX] = grid[cellY * gridWidth + cellX];
      grid[cellY * gridWidth + cellX] = nullptr;

      reactivateNeighbors(p);

      return;
    }
    if (b == nullptr) {
      if (randomFloat() <= sandFriction) return;
      p->x -= particleSize;
      p->y += particleSize;

      grid[(cellY + 1) * gridWidth + (cellX - 1)] =
          grid[cellY * gridWidth + cellX];
      grid[cellY * gridWidth + cellX] = nullptr;

      reactivateNeighbors(p);

      return;
    }
    if (c == nullptr) {
      if (randomFloat() <= sandFriction) return;
      p->x += particleSize;
      p->y += particleSize;

      grid[(cellY + 1) * gridWidth + (cellX + 1)] =
          grid[cellY * gridWidth + cellX];
      grid[cellY * gridWidth + cellX] = nullptr;

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

void ParticleSystem::reactivateNeighbors(Particle* p) {
  int cellX = p->x / particleSize;
  int cellY = p->y / particleSize;

  for (int y = 0; y <= 1; y++) {
    for (int x = -1; x <= 1; x++) {
      if (y == 0 && x == 0) continue;
      if (cellY + y >= gridHeight) continue;

      Particle* u = grid[(cellY + y) * gridWidth + (cellX + x)];
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

unsigned int ParticleSystem::getCapacity() { return particles.capacity(); }

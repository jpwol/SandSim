#include "ParticleSystem.h"

void ParticleSystem::addParticle(int x, int y, ParticleType type,
                                 uint32_t color) {
  int cellX = x / particleSize;
  int cellY = y / particleSize;
  particles.push_back({x, y, type, color});
  grid[cellY * gridWidth + cellX] = &particles.back();
  activeParticles.push_back(&particles.back());
}

void ParticleSystem::update() {
  for (auto& p : activeParticles) {
    int cellX = p->x / particleSize;
    int cellY = p->y / particleSize;
    if (p->type == ParticleType::Sand) {
      if (p->active && cellY + 1 < gridHeight) {
        Particle* a = grid[(cellY + 1) * gridWidth + cellX];
        Particle* b = grid[(cellY + 1) * gridWidth + (cellX - 1)];
        Particle* c = grid[(cellY + 1) * gridWidth + (cellX + 1)];
        if (a == nullptr || a->active) {
          p->y += particleSize;

          grid[(cellY + 1) * gridWidth + cellX] =
              grid[cellY * gridWidth + cellX];
          grid[cellY * gridWidth + cellX] = nullptr;
        } else if (b == nullptr || b->active) {
          p->y += particleSize;
          p->x -= particleSize;

          grid[(cellY + 1) * gridWidth + (cellX - 1)] =
              grid[cellY * gridWidth + cellX];
          grid[cellY * gridWidth + cellX] = nullptr;
        } else if (c == nullptr || c->active) {
          p->y += particleSize;
          p->x += particleSize;

          grid[(cellY + 1) * gridWidth + (cellX + 1)] =
              grid[cellY * gridWidth + cellX];
          grid[cellY * gridWidth + cellX] = nullptr;
        } else {
          // p->velocity = 0;
          p->active = false;
        }
      } else {
        if (p->active && p->y + particleSize >= height) {
          // p->velocity = 0;
          p->y = height - particleSize;
          p->active = false;
        }
      }
    }
  }

  std::erase_if(activeParticles, [](Particle* p) { return !p->active; });
}

const std::vector<Particle>& ParticleSystem::getParticles() const {
  return particles;
}

unsigned int ParticleSystem::getParticleCount() { return particles.size(); }

unsigned int ParticleSystem::getCapacity() { return particles.capacity(); }

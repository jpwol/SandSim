#include "Sim.h"

#include <chrono>
#include <iostream>

void Sim::handleInput(SDL_Event& e) {
  while (SDL_PollEvent(&e)) {
    switch (e.type) {
      case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
          case SDLK_ESCAPE:
            running = false;
            break;
          case SDLK_SPACE:
            updating = !updating;
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
  unsigned int mouseState = SDL_GetMouseState(&mouseX, &mouseY);
  switch (mouseState) {
    case 0:
      break;
    case 1:
      particleSystem.addParticle(
          mouseX - (mouseX % particleSystem.particleSize),
          mouseY - (mouseY % particleSystem.particleSize), ParticleType::Sand,
          0xFFFFFFFF);
      break;
    case 3:
    case 4:
      break;
    default:
      break;
  }
}

void Sim::run() {
  SDL_Event e;

  while (running) {
    particleSystem.addParticle(width / 2, 1, ParticleType::Sand, 0xa39464FF);
    auto frameStart = std::chrono::high_resolution_clock::now();
    handleInput(e);

    auto updateStart = std::chrono::high_resolution_clock::now();
    if (updating) particleSystem.update();
    auto updateEnd = std::chrono::high_resolution_clock::now();

    renderer.clear();
    auto renderStart = std::chrono::high_resolution_clock::now();
    renderer.renderParticles(particleSystem.getParticles(),
                             particleSystem.particleSize);
    renderer.present();
    auto renderEnd = std::chrono::high_resolution_clock::now();

    // SDL_Delay(16);  // crude framecap, fix with deltatime
    auto frameEnd = std::chrono::high_resolution_clock::now();

    auto updateTime = std::chrono::duration_cast<std::chrono::microseconds>(
        updateEnd - updateStart);
    auto renderTime = std::chrono::duration_cast<std::chrono::microseconds>(
        renderEnd - renderStart);
    auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(
        frameEnd - frameStart);
    std::cout << "Update: " << updateTime << " us | Render: " << renderTime
              << " us | Total: " << frameTime << " us | "
              << particleSystem.activeParticles.size() << " active particles | "
              << particleSystem.particles.size() << " total particles\n";
  }
}

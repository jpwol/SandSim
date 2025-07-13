#include "Sim.h"

#include <chrono>
#include <iomanip>
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
          mouseY - (mouseY % particleSystem.particleSize), ParticleType::Sand);
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
    auto frameStart = std::chrono::high_resolution_clock::now();
    handleInput(e);

    auto updateStart = std::chrono::high_resolution_clock::now();
    // if (updating) {
    //   particleSystem.addParticle(width / 2, 1, ParticleType::Sand,
    //   0xa39464FF);
    // }
    particleSystem.update();
    auto updateEnd = std::chrono::high_resolution_clock::now();

    renderer.clear();
    auto renderStart = std::chrono::high_resolution_clock::now();
    renderer.renderParticles(particleSystem);
    renderer.present();
    auto renderEnd = std::chrono::high_resolution_clock::now();

    // SDL_Delay(16);  // crude framecap, fix with deltatime
    auto frameEnd = std::chrono::high_resolution_clock::now();

    auto updateTime = std::chrono::duration_cast<std::chrono::microseconds>(
        updateEnd - updateStart);
    auto renderTime = std::chrono::duration_cast<std::chrono::microseconds>(
        renderEnd - renderStart);
    auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(
                         frameEnd - frameStart)
                         .count();
    int fps = 1'000'000.0 / frameTime;
    std::cout << "Update: " << std::setw(6) << updateTime
              << " | Render: " << std::setw(6) << renderTime
              << " | Total: " << std::setw(4) << frameTime << "us | "
              << "FPS: " << std::setw(4) << fps << " | " << std::setw(6)
              << particleSystem.activeParticles.size() << " active particles | "
              << std::setw(6) << particleSystem.particles.size()
              << " total particles\n";
  }
}

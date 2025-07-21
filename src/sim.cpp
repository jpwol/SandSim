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
          case SDLK_1:
            brush = Brush::Sand;
            break;
          case SDLK_2:
            brush = Brush::Water;
            break;
          case SDLK_3:
            brush = Brush::Stone;
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
      if (mouseX >= 0 && mouseX < width && mouseY >= 0 && mouseY < height)
        particleSystem.addParticle(
            mouseX - (mouseX % particleSystem.particleSize),
            mouseY - (mouseY % particleSystem.particleSize), brush);
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

  int step = 0;
  while (running) {
    auto frameStart = std::chrono::high_resolution_clock::now();
    handleInput(e);

    auto updateStart = std::chrono::high_resolution_clock::now();
    particleSystem.update();
    auto updateEnd = std::chrono::high_resolution_clock::now();

    step++;

    renderer.clear();
    auto renderStart = std::chrono::high_resolution_clock::now();
    renderer.renderParticles(particleSystem);
    renderer.present();
    auto renderEnd = std::chrono::high_resolution_clock::now();

    // SDL_Delay(32);  // crude framecap, fix with deltatime
    auto frameEnd = std::chrono::high_resolution_clock::now();

    auto updateTime = std::chrono::duration_cast<std::chrono::microseconds>(
        updateEnd - updateStart);
    auto renderTime = std::chrono::duration_cast<std::chrono::microseconds>(
        renderEnd - renderStart);
    auto frameTime = std::chrono::duration_cast<std::chrono::microseconds>(
                         frameEnd - frameStart)
                         .count();
    int fps = 1'000'000.0 / frameTime;

    if (step == 1000) {
      step = 0;

      std::cout << "Update: " << std::setw(6) << updateTime
                << " | Render: " << std::setw(6) << renderTime
                << " | Total: " << std::setw(4) << frameTime << "us | "
                << "FPS: " << std::setw(4) << fps << " | " << std::setw(6)
                << std::setw(6) << particleSystem.getParticleCount()
                << " total particles\n";
    }
  }
}

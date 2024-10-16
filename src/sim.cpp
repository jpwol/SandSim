#include "Sim.h"

void Sim::init() {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    window = SDL_CreateWindow("Sand Sim", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (window == NULL) {
      std::cout << "Error: Window could not be created. " << SDL_GetError()
                << '\n';
      return;
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL) {
      std::cout << "Error: Renderer could not be created. " << SDL_GetError()
                << '\n';
      return;
    }
  } else {
    std::cout << "Error: SDL failed to initialize. " << SDL_GetError() << '\n';
    return;
  }
}

void Sim::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
      case SDLK_SPACE:
        matrix.clearMatrix();
        break;
      case SDLK_1:
        type = B_SAND;
        break;
      case SDLK_2:
        type = B_WATER;
        break;
      case SDLK_3:
        type = B_STONE;
        break;
      default:
        break;
      }
    default:
      break;
    }
  }
}

void Sim::update() {
  mouseState = SDL_GetMouseState(&mouseX, &mouseY);
  // std::cout << mouseX/matrix.particleSize << ", " <<
  // mouseY/matrix.particleSize << "\n";
  if (mouseState == 1) {
    matrix.drawParticles(mouseX, mouseY, type);
  } else if (mouseState == 2) {
    matrix.drawSingleParticle(mouseX, mouseY, type);
  } else if (mouseState == 4) {
    matrix.eraseParticles(mouseX, mouseY);
  }
  for (auto &row : matrix.matrix) {
    for (auto &particle : row) {
      if (particle != nullptr)
        particle->update(matrix);
    }
  }
}

void Sim::render() {
  SDL_SetRenderDrawColor(renderer, 18, 18, 18, 255);
  SDL_RenderClear(renderer);
  for (int x = 0; x < matrix.worldWidth; x++) {
    for (int y = 0; y < matrix.worldHeight; y++) {
      if (matrix.matrix[x][y] != nullptr) {
        SDL_SetRenderDrawColor(renderer, matrix.matrix[x][y]->r,
                               matrix.matrix[x][y]->g, matrix.matrix[x][y]->b,
                               255);
        SDL_Rect rect;
        rect = {x * matrix.particleSize, y * matrix.particleSize,
                matrix.particleSize, matrix.particleSize};
        SDL_RenderFillRect(renderer, &rect);
        matrix.matrix[x][y]->updated_this_frame = false;
      }
    }
  }
  SDL_RenderPresent(renderer);
}

void Sim::run() {
  init();
  while (running) {
    int startLoop = SDL_GetTicks();
    handleEvents();
    update();
    render();

    int delta = SDL_GetTicks() - startLoop;
    // int p_delta = delta;
    if (delta < D_DELTA) {
      delta = D_DELTA - delta;
      SDL_Delay(delta);
    }
    // printf("%d\n", p_delta);
  }
  SDL_Quit();
}

#include "CellularMatrix.h"
#include "Elements.h"

void CellularMatrix::drawParticles(int mouseX, int mouseY, B_TYPE type) {
  if (mouseX >= 0 && mouseX < windowWidth && mouseY >= 0 &&
      mouseY < windowHeight) {
    for (int x = -2; x <= 2; x++) {
      for (int y = -2; y <= 2; y++) {
        int mX = mouseX / particleSize + x;
        int mY = mouseY / particleSize + y;
        if (mX >= 0 && mX < worldWidth && mY >= 0 && mY < worldHeight) {
          if (matrix[mX][mY] == nullptr) {
            switch (type) {
            case B_SAND:
              matrix[mX][mY] = new Sand(mX * particleSize, mY * particleSize);
              break;
            case B_WATER:
              matrix[mX][mY] = new Water(mX * particleSize, mY * particleSize);
              break;
            case B_STONE:
              matrix[mX][mY] = new Stone(mX * particleSize, mY * particleSize);
              break;
            default:
              break;
            }
          }
        }
      }
    }
  }
}

void CellularMatrix::drawSingleParticle(int mouseX, int mouseY, B_TYPE type) {
  if (mouseX >= 0 && mouseX < windowWidth && mouseY >= 0 &&
      mouseY < windowHeight) {
    int mX = mouseX / particleSize;
    int mY = mouseY / particleSize;
    if (matrix[mX][mY] == nullptr) {
      switch (type) {
      case B_SAND:
        matrix[mX][mY] = new Sand(mX * particleSize, mY * particleSize);
        break;
      case B_WATER:
        matrix[mX][mY] = new Water(mX * particleSize, mY * particleSize);
        break;
      case B_STONE:
        matrix[mX][mY] = new Stone(mX * particleSize, mY * particleSize);
        break;
      default:
        break;
      }
    }
  }
}

void CellularMatrix::eraseParticles(int mouseX, int mouseY) {
  if (mouseX >= 0 && mouseX < windowWidth && mouseY >= 0 &&
      mouseY < windowHeight) {
    for (int x = -1; x <= 1; x++) {
      for (int y = -1; y <= 1; y++) {
        int mX = mouseX / particleSize + x;
        int mY = mouseY / particleSize + y;
        if (mX >= 0 && mX < worldWidth && mY >= 0 && mY < worldHeight) {
          delete matrix[mX][mY];
          matrix[mX][mY] = nullptr;
        }
      }
    }
  }
}

void CellularMatrix::moveTo(Particle *cell, int matrixX, int matrixY) {
  if (matrixX >= 0 && matrixX < worldWidth) {
    matrix[matrixX][matrixY] = cell;
    matrix[cell->matrix_x][cell->matrix_y] = nullptr;
    cell->matrix_x += (matrixX - cell->matrix_x);
    cell->matrix_y += (matrixY - cell->matrix_y);
    cell->pixel_x += (matrixX * particleSize - cell->pixel_x);
    cell->pixel_y += (matrixY * particleSize - cell->pixel_y);
  }
}

P_TYPE CellularMatrix::getTypeAtCell(int x, int y) {
  if (matrix[x][y] == nullptr)
    return EMPTY;
  else
    return matrix[x][y]->type;
}

Particle *CellularMatrix::getElementAtCell(int x, int y) {
  return matrix[x][y];
}

void CellularMatrix::clearMatrix() {
  for (auto &row : matrix) {
    for (auto &particle : row) {
      if (particle != nullptr) {
        delete particle;
        particle = nullptr;
      }
    }
  }
}

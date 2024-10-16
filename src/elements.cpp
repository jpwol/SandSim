#include "Elements.h"

void Sand::update(CellularMatrix &matrix) {
  if (!updated_this_frame) {
    if (matrix_y + 1 < matrix.worldHeight) {
      int lastEmpty = matrix_y;
      if (matrix.getTypeAtCell(matrix_x, matrix_y + 1) == EMPTY) {
        vel.second += 0.5f;
        for (int y = 1; y <= vel.second; y++) {
          if (matrix_y + y < matrix.worldHeight) {
            if (matrix.getTypeAtCell(matrix_x, matrix_y + y) == EMPTY) {
              lastEmpty = matrix_y + y;
            } else if (matrix.getTypeAtCell(matrix_x, matrix_y + y) == SOLID) {
              float absY = std::max(std::abs(vel.second) / 2.0f, 1.0f);
              vel.first = (vel.first < 0) ? -absY : absY;
              vel.second = 0.f;
              break;
            }
          }
        }
        if (lastEmpty != matrix_y) {
          matrix.moveTo(matrix.getElementAtCell(matrix_x, matrix_y), matrix_x,
                        lastEmpty);
        }
      } else if (vel.first != 0 && matrix_x - 1 > 0 &&
                 matrix_x + 1 < matrix.worldWidth) {
        lastEmpty = matrix_x;
        if (vel.first < 0) {
          for (int x = 0; x >= vel.first; x--) {
            if (matrix.getTypeAtCell(matrix_x + x, matrix_y) == EMPTY)
              lastEmpty = matrix_x + x;
          }
          vel.first++;
        } else if (vel.first > 0) {
          for (int x = 0; x <= vel.first; x++) {
            if (matrix.getTypeAtCell(matrix_x + x, matrix_y) == EMPTY)
              lastEmpty = matrix_x + x;
          }
          vel.first--;
        }
        if (lastEmpty != matrix_x)
          matrix.moveTo(matrix.getElementAtCell(matrix_x, matrix_y), lastEmpty,
                        matrix_y);
      }
    }
  }
  updated_this_frame = true;
}

void Water::update(CellularMatrix &matrix) {
  if (!updated_this_frame) {
    if (matrix_y + 1 < matrix.worldHeight) {
    }
  }
}

void Stone::update(CellularMatrix &matrix) {}

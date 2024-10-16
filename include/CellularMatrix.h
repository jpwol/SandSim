#pragma once

class Particle;
enum P_TYPE { EMPTY, SOLID, LIQUID };

enum B_TYPE { B_ERASER, B_SAND, B_WATER, B_STONE };

// Wrapper for sim grid matrix.
class CellularMatrix {
public:
  static const int particleSize = 4;

  static const int windowWidth = 1280;
  static const int windowHeight = 720;

  static const int worldWidth = windowWidth / particleSize;
  static const int worldHeight = windowHeight / particleSize;

  Particle *matrix[worldWidth][worldHeight] = {nullptr};

  P_TYPE getTypeAtCell(int x, int y);
  Particle *getElementAtCell(int x, int y);
  void drawParticles(int mouseX, int mouseY, B_TYPE type);
  void drawSingleParticle(int mouseX, int mouseY, B_TYPE type);
  void eraseParticles(int mouseX, int mouseY);
  void moveTo(Particle *cell, int matrixX, int matrixY);
  void clearMatrix();
};

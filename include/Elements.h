#pragma once
#include <vector>
#include <iostream>
#include <random>
#include "CellularMatrix.h"

using vec2 = std::pair<int, int>;
using vec2f = std::pair<float, float>;

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::uniform_int_distribution<int> distSand(-15, 15);
inline std::uniform_int_distribution<int> distWater(-15, 15);
inline std::uniform_int_distribution<int> distStone(-30, 0);

class Particle{
    public:
        int pixel_x, pixel_y;
        int matrix_x, matrix_y;
        int lastX = 0, lastY = 0;
        int particleSize = CellularMatrix::particleSize;
        bool isFreeFalling = true;
        P_TYPE type;
        int r, g, b;
        bool updated_this_frame = false;

        Particle(P_TYPE _type) : type(_type){}
        virtual void update(CellularMatrix& matrix) = 0;
        virtual ~Particle() = default;
};

//first base-archetype
class Solid : public Particle{
    public:
        Solid() : Particle(SOLID){}
        virtual void update(CellularMatrix& matrix) = 0;
};

//sub archetype
class MovableSolid : public Solid{
    public:
        MovableSolid() : Solid(){}
        vec2f vel;
        int stiffness;
        virtual void update(CellularMatrix& matrix) = 0;
};

//derived types for MoveableSolid
class Sand : public MovableSolid{
    public:
        Sand();
        Sand(int _x, int _y) : MovableSolid(){
            pixel_x = _x - (_x % particleSize);
            pixel_y = _y - (_y % particleSize);
            matrix_x = pixel_x / particleSize;
            matrix_y = pixel_y / particleSize;
            stiffness = 30;

            r = 168 + distSand(gen);
            g = 145 + distSand(gen);
            b = 99 + distSand(gen);

            vel.first = (rand()%2 == 0) ? -0.1f : 0.1f, vel.second = 1;
        }
        ~Sand() override = default;
        void update(CellularMatrix& matrix) override;
};

//sub archetype
class ImmovableSolid : public Solid{
    public:
        ImmovableSolid() : Solid(){}

        virtual void update(CellularMatrix& matrix) = 0;
};

//derived types for ImmovableSolid
class Stone : public ImmovableSolid{
    public:
        Stone();
        Stone(int _x, int _y) : ImmovableSolid(){
            pixel_x = _x - (_x % particleSize);
            pixel_y = _y - (_y % particleSize);
            matrix_x = pixel_x / particleSize;
            matrix_y = pixel_y / particleSize;

            int randValue = distStone(gen);
            r = 90 + randValue;
            g = 90 + randValue;
            b = 90 + randValue;
        }
        void update(CellularMatrix& matrix);
};

//second base-archetype
class Liquid : public Particle{
    public:
        Liquid() : Particle(LIQUID){}
        virtual void update(CellularMatrix& matrix) = 0;
};

//derived types for liquid
class Water : public Liquid{
    public:
        Water();
        Water(int _x, int _y){
            pixel_x = _x - (_x % particleSize);
            pixel_y = _y - (_y % particleSize);
            matrix_x = pixel_x / particleSize;
            matrix_y = pixel_y / particleSize;

            r = 31 + distWater(gen);
            g = 142 + distWater(gen);
            b = 240 + distWater(gen);
        }
        ~Water() override = default;
    
        void update(CellularMatrix& matrix) override;
};
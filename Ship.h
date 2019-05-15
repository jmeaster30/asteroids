#ifndef __ENTITY_H__
#define __ENTITY_H__

#define _USE_MATH_DEFINES

#include <cmath>
#include <string>
#include <SDL2/SDL.h>
#include <vector>

#include "InputManager.h"
#include "Renderer.h"
#include "Bullet.h"

class Ship
{
  public:
    Ship(double x, double y, int width, int height);
    ~Ship();

    void update();
    void render();

  private:
    //input manager
    InputManager* im;

    int width;
    int height;

    //motion variables
    double posx;
    double posy;
    double velx;
    double vely;
    double accx;
    double accy;
    double angle;//in radians

    std::vector<Bullet*> bullets;

    //rendering variables
    SDL_Point nose;
    SDL_Point lwing;
    SDL_Point rwing;
};

#endif

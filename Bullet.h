#ifndef __BULLET_H__
#define __BULLET_H__

#include <SDL2/SDL.h>
#include "Renderer.h"

class Bullet
{
public:
  Bullet(double x, double y, double vx, double vy, double a);
  ~Bullet();

  void update();
  void render();
private:
  double posx;
  double posy;
  double velx;
  double vely;

  double angle;

  //int width;
  //int height;

  //SDL_Point top;
  //SDL_Point left;
  //SDL_Point right;
  //SDL_Point bottom;

};

#endif

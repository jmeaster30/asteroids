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

  double getX();
  double getY();

private:
  double posx;
  double posy;
  double velx;
  double vely;

  double angle;
};

#endif

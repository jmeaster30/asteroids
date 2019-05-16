#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#define _USE_MATH_DEFINES

#include <cstdlib>
#include <iostream>

#include <cmath>
#include <vector>
#include <utility>

#include "Bullet.h"

class Asteroid
{
public:
  Asteroid(double x, double y, double vx, double vy, double rad);
  ~Asteroid();

  void update(std::vector<Bullet*>* bullets, std::vector<Asteroid*>* asteroids);
  void render();

  double getX();
  double getY();
  double getRadius();

  bool getDead();

private:

  bool dead;

  double posx;
  double posy;

  double velx;
  double vely;

  double radius;

  std::vector<std::pair<double, double>> points;

};

#endif

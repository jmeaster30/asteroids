#include "Bullet.h"

//SDL_Point turn(double posx, double posy, double centerx, double centery, double a);
//{
//  SDL_Point newpoint;
//  int tx = posx - centerx;
//  int ty = posy - centery;
//  newpoint.x = (int)((tx * cos(a)) - (ty * sin(a)) + centerx);
//  newpoint.y = (int)((tx * sin(a)) + (ty * cos(a)) + centery);
//  return newpoint;
//}

Bullet::Bullet(double x, double y, double vx, double vy, double a)
{
  //width = 3;
  //height = 5;

  posx = x;
  posy = y;
  velx = vx;
  vely = vy;

  angle = a;

  //top = {
  //  (int)(posx),
  //  (int)(posy - (height / 2))
  //};

  //left = {
  //  (int)(posx - (width / 2)),
  //  (int)(posy)
  //};

  //right = {
  //  (int)(posx + (width / 2)),
  //  (int)(posy)
  //};

  //bottom = {
  //  (int)(posx),
  //  (int)(posy + (height / 2))
  //};

  //top = turn(top.x, top.y, posx, posy, angle);
  //left = turn(left.x, left.y, posx, posy, angle);
  //right = turn(right.x, right.y, posx, posy, angle);
  //bottom = turn(bottom.x, bottom.y, posx, posy, angle);
}

void Bullet::update()
{
  posx += velx;
  posy += vely;

  //screen wrap
  int border = 10;
  Renderer* r = Renderer::getInstance();

  if(posx < -border)
    posx = r->getWidth() + border;
  else if(posx > r->getWidth() + border)
    posx = -border;

  if(posy < -border)
    posy = r->getHeight() + border;
  else if(posy > r->getHeight() + border)
    posy = -border;

  //top.x = (int)(posx);
  //top.y = (int)(posy - (height / 2));

  //left.x = (int)(posx - (width / 2));
  //left.y = (int)(posy);

  //right.x = (int)(posx + (width / 2));
  //right.y = (int)(posy);

  //bottom.x = (int)(posx);
  //bottom.y = (int)(posy + (height / 2));

  //top = turn(top.x, top.y, posx, posy, angle);
  //left = turn(left.x, left.y, posx, posy, angle);
  //right = turn(right.x, right.y, posx, posy, angle);
  //bottom = turn(bottom.x, bottom.y, posx, posy, angle);
}

void Bullet::render()
{
  SDL_Renderer* r = Renderer::getInstance()->getRenderer();
  SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
  //SDL_RenderDrawLine(r, top.x, top.y, left.x, left.y);
  //SDL_RenderDrawLine(r, left.x, left.y, bottom.x, bottom.y);
  //SDL_RenderDrawLine(r, bottom.x, bottom.y, right.x, right.y);
  //SDL_RenderDrawLine(r, right.x, right.y, top.x, top.y);
  SDL_RenderDrawPoint(r, (int)posx, (int)posy);
}

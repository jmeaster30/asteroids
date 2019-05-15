#include "Bullet.h"

SDL_Point turn(double posx, double posy, double centerx, double centery, double a);

Bullet::Bullet(double x, double y, double vx, double vy, double a)
{
  posx = x;
  posy = y;
  velx = vx;
  vely = vy;

  angle = a;

}

double Bullet::getX()
{
  return posx;
}

double Bullet::getY()
{
  return posy;
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

}

void Bullet::render()
{
  SDL_Renderer* r = Renderer::getInstance()->getRenderer();
  SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
  SDL_RenderDrawPoint(r, (int)posx, (int)posy);
  SDL_Point ahead = turn(posx, posy - 1, posx, posy, angle);
  SDL_Point behind = turn(posx, posy + 1, posx, posy, angle);
  SDL_RenderDrawPoint(r, ahead.x, ahead.y);
  SDL_RenderDrawPoint(r, behind.x, behind.y);
}

#include "Asteroid.h"

Asteroid::Asteroid(double x, double y, double vx, double vy, double rad)
{
  posx = x;
  posy = y;
  velx = vx;
  vely = vy;
  radius = rad;

  for(int a = 0; a < 10; a++)
  {
    double angle = a * (2 * M_PI / 10);
    double rad = radius + ((rand() % 9) - 4);
    points.push_back(std::make_pair(angle, rad));
  }

  dead = false;
}

double Asteroid::getX()
{
  return posx;
}

double Asteroid::getY()
{
  return posy;
}

double Asteroid::getRadius()
{
  return radius;
}

bool Asteroid::getDead()
{
  return dead;
}

void Asteroid::update(std::vector<Bullet*>* bullets, std::vector<Asteroid*>* asteroids)
{
  posx += velx;
  posy += vely;

  //screen wrap
  int border = radius * 2;
  Renderer* r = Renderer::getInstance();

  if(posx < -border)
    posx = r->getWidth() + border;
  else if(posx > r->getWidth() + border)
    posx = -border;

  if(posy < -border)
    posy = r->getHeight() + border;
  else if(posy > r->getHeight() + border)
    posy = -border;

  for(std::vector<Bullet*>::iterator it = bullets->begin(); it != bullets->end(); ++it)
  {
    double bx = (*it)->getX();
    double by = (*it)->getY();
    double dx = posx - bx;
    double dy = posy - by;
    if((dx * dx + dy * dy) <= radius * radius)
    {
      if(radius > 15)
      {
        int nr = radius / 2;
        int nx = posx + ((rand() % 5) - 2);
        int ny = posy + ((rand() % 5) - 2);
        int nv = (rand() % 2) + 1;
        double na = (rand() % 360) * (M_PI / 180);
        asteroids->push_back(new Asteroid(nx, ny, nv * cos(na), nv * sin(na), nr));
        nx = posx + ((rand() % 5) - 2);
        ny = posy + ((rand() % 5) - 2);
        nv = (rand() % 2) + 1;
        na = (rand() % 360) * (M_PI / 180);
        asteroids->push_back(new Asteroid(nx, ny, nv * cos(na), nv * sin(na), nr));
      }
      bullets->erase(it);
      dead = true;
      break;
    }
  }
}

void Asteroid::render()
{
  SDL_Renderer* r = Renderer::getInstance()->getRenderer();
  std::pair<double, double> start = *(points.begin());
  int lastx = -1;
  int lasty = -1;
  bool first = true;
  SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
  for(std::vector<std::pair<double, double>>::iterator it = points.begin(); it != points.end(); ++it)
  {
    int px = posx + ((*it).second * cos((*it).first));
    int py = posy + ((*it).second * sin((*it).first));
    if(!first)
    {
      //draw
      //std::cout << "draw the line" << std::endl;
      SDL_RenderDrawLine(r, px, py, lastx, lasty);
    }
    first = false;
    lastx = px;
    lasty = py;
  }
  int fx = posx + (start.second * cos(start.first));
  int fy = posy + (start.second * sin(start.first));
  SDL_RenderDrawLine(r, lastx, lasty, fx, fy);
}

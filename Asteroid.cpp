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
    double rad = radius;// - (2 * rand());
    points.push_back(std::make_pair(angle, rad));
  }

  std::cout << "Asteroid Created!! " << points.size() << std::endl;
}

bool Asteroid::update(std::vector<Bullet*> bullets, std::vector<Asteroid*> asteroids)
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

  for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
  {
    double bx = (*it)->getX();
    double by = (*it)->getY();
    double dx = posx - bx;
    double dy = posy - by;
    if((dx * dx + dy * dy) <= radius * radius)
    {
      if(radius > 5)
      {
        asteroids.push_back(new Asteroid(posx + ((radius / 2) * rand()),
                                         posy + ((radius / 2) * rand()),
                                         velx * 2,
                                         vely * 2,
                                         radius / 2));
        asteroids.push_back(new Asteroid(posx - ((radius / 2) * rand()),
                                         posy - ((radius / 2) * rand()),
                                         velx * 2,
                                         vely * 2,
                                         radius / 2));
      }
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

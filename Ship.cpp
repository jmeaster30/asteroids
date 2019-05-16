#include "Ship.h"

Ship::Ship(double x, double y, int w, int h)
{
  im = InputManager::getInstance();

  angle = 0;
  width = w;
  height = h;

  posx = x;
  posy = y;

  velx = 0;
  vely = 0;

  nose = {
    (int)(posx),
    (int)(posy - (h / 2))
  };

  lwing = {
    (int)(posx - (w / 2)),
    (int)(posy + (h / 2))
  };

  rwing = {
    (int)(posx + (w / 2)),
    (int)(posy + (h / 2))
  };

  dead = false;
}

bool Ship::getDead()
{
  return dead;
}

std::vector<Bullet*>* Ship::getBullets()
{
  return &bullets;
}

SDL_Point turn(double posx, double posy, double centerx, double centery, double a)
{
  SDL_Point newpoint;
  int tx = posx - centerx;
  int ty = posy - centery;
  newpoint.x = (int)((tx * cos(a)) - (ty * sin(a)) + centerx);
  newpoint.y = (int)((tx * sin(a)) + (ty * cos(a)) + centery);
  return newpoint;
}

void Ship::update(std::vector<Asteroid*>* asteroids)
{
  double turnSpeed = 0.08;
  double thrust = 0.5;
  double drag = 0.99;

  //motion
  if(im->getKeyState(SDL_SCANCODE_UP) >= PRESSED)
  {
    accx = cos(angle - M_PI_2);
    accy = sin(angle - M_PI_2);
  }
  else
  {
    accx = 0;
    accy = 0;
  }
  velx += thrust * accx;
  vely += thrust * accy;
  velx *= drag;
  vely *= drag;
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

  //collision
  for(std::vector<Asteroid*>::iterator it = asteroids->begin(); it != asteroids->end(); ++it)
  {
    double dx = posx - (*it)->getX();
    double dy = posy - (*it)->getY();
    double rad = (*it)->getRadius();
    if((dx * dx + dy * dy) <  rad * rad)
    {
      dead = true;
      break;
    }
  }

  //calculate other points
  nose.x = posx;
  nose.y = posy - (height / 2);

  lwing.x = posx - (width / 2);
  lwing.y = posy + (height / 2);

  rwing.x = posx + (width / 2);
  rwing.y = posy + (height / 2);

  if(im->getKeyState(SDL_SCANCODE_LEFT) >= PRESSED && im->getKeyState(SDL_SCANCODE_RIGHT) == NOTPRESSED)
  {
    angle -= turnSpeed;
  }
  if(im->getKeyState(SDL_SCANCODE_RIGHT) >= PRESSED && im->getKeyState(SDL_SCANCODE_LEFT) == NOTPRESSED)
  {
    angle += turnSpeed;
  }

  //turn
  nose = turn(nose.x, nose.y, posx, posy, angle);
  lwing = turn(lwing.x, lwing.y, posx, posy, angle);
  rwing = turn(rwing.x, rwing.y, posx, posy, angle);

  //shooting
  for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
  {
    (*it)->update();
  }

  double bulletspd = 2;
  int bulletLimit = 5;
  if(im->getKeyState(SDL_SCANCODE_SPACE) == RELEASED && bullets.size() < 5)
  {
    bullets.push_back(new Bullet((double)nose.x,
                                 (double)nose.y,
                                 bulletspd * cos(angle - M_PI_2) + velx,
                                 bulletspd * sin(angle - M_PI_2) + vely,
                                 angle));
    //std::cout << "Bullet shot: " << bullets.size() << std::endl;
  }
}

void Ship::render()
{
  SDL_Renderer* r = Renderer::getInstance()->getRenderer();
  SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(r, nose.x, nose.y, lwing.x, lwing.y);
  SDL_RenderDrawLine(r, lwing.x, lwing.y, rwing.x, rwing.y);
  SDL_RenderDrawLine(r, rwing.x, rwing.y, nose.x, nose.y);
  for(std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it)
  {
    (*it)->render();
  }
}

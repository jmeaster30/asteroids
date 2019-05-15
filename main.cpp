#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include <ctime>
#include <cstdlib>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

#include "Renderer.h"
#include "InputManager.h"
#include "Ship.h"
#include "Asteroid.h"

//read in window config file
int win_width = 800;
int win_height = 600;
std::string win_title = "Asteroids";
double fps = 60.0;

int frames = 0;
int updates = 0;
int close_request = 0;

int main(int argc, char** argv)
{
  srand(time(0));

  if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
  {
    printf("ERROR %s: SDL Initialization Failed!", SDL_GetError());
    return -1;
  }
  //create the window
  SDL_Window* window = SDL_CreateWindow(win_title.c_str(),
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        win_width, win_height, 0);
  if(!window)
  {
    printf("ERROR %s: SDL Window Creation Failed!", SDL_GetError());
    SDL_Quit();
    return -1;
  }

  //create the renderer
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(!renderer)
  {
    printf("ERROR %s: SDL Renderer Creation Failed!", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  Renderer::init(renderer, win_width, win_height);
  InputManager* im = InputManager::getInstance();

  //timing variables
  std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now(); /*nano time*/
  double ns = 1000000000.0 / fps;
  double delta = 0;
  std::chrono::steady_clock::time_point timer = std::chrono::steady_clock::now(); /*milli time*/

  //game variables
  Ship* player = new Ship(win_width / 2, win_height / 2, 17, 17);
  std::vector<Asteroid*> asteroids;

  //game loop
  while(!close_request)
  {
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now(); /*nano time*/
    delta += (now - lastTime).count() / ns;
    lastTime = now;
    while(delta >= 1)
    {
      //get inputs
      im->pollEvents();
      if(im->quitEvent()) close_request = 1;

      //update objects
      player->update();
      for(std::vector<Asteroid*>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
      {
        bool shot = (*it)->update(player->getBullets(), asteroids);
      }

      updates++;
      delta--;
    }
    //render all the objects
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(renderer);

    player->render();
    for(std::vector<Asteroid*>::iterator it = asteroids.begin(); it != asteroids.end(); ++it)
    {
      (*it)->render();
    }

    frames++;
    SDL_RenderPresent(renderer);

    if((std::chrono::steady_clock::now() - timer).count() > 1000)
    {
      timer = timer + std::chrono::milliseconds(1000);//add 1000 milliseconds
      std::cout << updates << " ups, " << frames << " fps" << std::endl;
      updates = 0;
      frames = 0;
    }
  }

  im->clean();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

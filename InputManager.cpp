#include "InputManager.h"

InputManager* InputManager::instance_inputmanager = nullptr;

InputManager::InputManager()
{
  std::cout << "InputManager Created!" << std::endl;
}

void InputManager::pollEvents()
{
  //find mouse location
  mousebuttons = SDL_GetMouseState(&(mouseloc.first), &(mouseloc.second));
  //turn all the 3 values into 0 values
  for(kmiter = keymap.begin(); kmiter != keymap.end(); ++kmiter)
  {
    if(kmiter->second == 3) kmiter->second = 0;
  }
  SDL_Event event;
  while(SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_KEYDOWN:
        kmiter = keymap.find(event.key.keysym.scancode);
        if(kmiter == keymap.end())
        {
          keymap.insert({event.key.keysym.scancode, 1});
        }
        else
        {
          kmiter->second = 2;
        }
        break;
      case SDL_KEYUP:
        kmiter = keymap.find(event.key.keysym.scancode);
        if(kmiter == keymap.end())
        {
          //shouldnt happen
          keymap.insert({event.key.keysym.scancode, 3});
        }
        else
        {
          if(kmiter->second == 2 || kmiter->second == 1)
            kmiter->second = 3;
          else
            kmiter->second = 0;
        }
        break;
    }
  }
}

int InputManager::getKeyState(Uint32 id)
{
  kmiter = keymap.find(id);
  if(kmiter == keymap.end())
    return 0;
  return kmiter->second;
}

std::pair<int, int> InputManager::getMouseLoc()
{
  return mouseloc;
}

Uint32 InputManager::getMouseButtons()
{
  return mousebuttons;
}

bool InputManager::quitEvent()
{
  return quit;
}

int InputManager::clean()
{
  keymap.clear();
  return 0;
}

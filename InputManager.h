#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <string>
#include <iostream>
#include <utility>
#include <iterator>
#include <unordered_map>

#include <SDL2/SDL.h>

enum keystate
{
  NOTPRESSED,
  PRESSED,
  HOLD,
  RELEASED
};

class InputManager
{
  public:
    static InputManager* getInstance()
    {
      return (!instance_inputmanager) ?
            instance_inputmanager = new InputManager() :
            instance_inputmanager;
    }

    void pollEvents();

    //0 key is not pressed
    //1 key just got pressed
    //2 key is being held
    //3 key just got released
    int getKeyState(Uint32 key);
    std::pair<int, int> getMouseLoc();
    Uint32 getMouseButtons();
    bool quitEvent();

    int clean();

  private:
    InputManager();
    ~InputManager();
    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);

    bool quit = false;

    Uint32 mousebuttons;
    std::pair<int, int> mouseloc;

    std::unordered_map<Uint32, int> keymap;
    std::unordered_map<Uint32, int>::iterator kmiter;

    static InputManager* instance_inputmanager;
};

#endif

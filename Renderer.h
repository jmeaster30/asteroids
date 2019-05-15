#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SDL2/SDL.h>

class Renderer
{
public:
  static Renderer* getInstance(){ return inst_renderer; }
  static Renderer* init(SDL_Renderer* r, int w, int h)
  {
    inst_renderer = new Renderer();
    inst_renderer->renderer = r;
    inst_renderer->width = w;
    inst_renderer->height = h;
    return inst_renderer;
  }

  SDL_Renderer* getRenderer();
  int getWidth();
  int getHeight();

private:
  Renderer();
  ~Renderer();

  SDL_Renderer* renderer;
  int width;
  int height;

  static Renderer* inst_renderer;
};

#endif

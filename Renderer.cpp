#include "Renderer.h"

Renderer* Renderer::inst_renderer = nullptr;

Renderer::Renderer(){}

SDL_Renderer* Renderer::getRenderer()
{
  return renderer;
}

int Renderer::getWidth()
{
  return width;
}

int Renderer::getHeight()
{
  return height;
}

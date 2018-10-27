#pragma once

#include <SDL2/SDL.h>
#include <memory>

class WindowedApplication {
  std::unique_ptr<SDL_Window> window;
 public:
  WindowedApplication();
  ~WindowedApplication();
};

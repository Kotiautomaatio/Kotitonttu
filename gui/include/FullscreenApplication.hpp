#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <Color.hpp>
#include <chrono>
struct SDLWindowDestroyer
{
  void operator()(SDL_Window* w) const
  {
    SDL_DestroyWindow(w);
  }
};
class FullscreenApplication {
  std::unique_ptr<SDL_Window, SDLWindowDestroyer> m_window = nullptr;
  std::chrono::duration<double> m_target_frame_time;
 public:
  explicit FullscreenApplication(const char *app_title, Color bg_color, double target_fps);
  ~FullscreenApplication();
  void run();
};


class AppException : public std::runtime_error {
 public:
  explicit AppException(const std::string &message) : std::runtime_error(message) {}
};

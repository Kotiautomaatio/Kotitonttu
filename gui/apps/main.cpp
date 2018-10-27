#include <SDL2/SDL.h>
#include <Color.hpp>
#include <chrono>
#include <zconf.h>

using namespace std::literals::chrono_literals;

constexpr Color bg_color = Color::RGB(75, 101, 132);
constexpr double target_fps = 60.0;
constexpr auto target_frame_time = 1000.0ms / target_fps;

int main() {
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    return 1;
  }
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  auto screen_width = DM.w;
  auto screen_height = DM.h;
  window = SDL_CreateWindow(
      "hello_sdl2",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      screen_width, screen_height,
      SDL_WINDOW_SHOWN
  );
  if (window == NULL) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    return 1;
  }
  SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
  screenSurface = SDL_GetWindowSurface(window);

  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, bg_color.red(), bg_color.green(), bg_color.blue()));
  bool should_continue = true;
  SDL_Event ev;


  while (should_continue) {
    auto start_time = std::chrono::system_clock::now();
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT) {
        should_continue = false;
      }
    }
    auto end_time =std::chrono::system_clock::now();
    auto computation_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    auto sleep_time = computation_time - target_frame_time;
    auto sleep = sleep_time.count();
    if (sleep > 0) {
      SDL_Delay(static_cast<Uint32>(sleep));
    }
    SDL_UpdateWindowSurface(window);
  }
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

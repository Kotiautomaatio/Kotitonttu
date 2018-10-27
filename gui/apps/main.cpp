#include <SDL2/SDL.h>
#include <Color.hpp>

constexpr Color bg_color = Color::RGB(75, 101, 132);

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
  SDL_UpdateWindowSurface(window);
  SDL_Delay(2000);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}

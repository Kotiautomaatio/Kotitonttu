#include <FullscreenApplication.hpp>
#include <chrono>

FullscreenApplication::FullscreenApplication(const char *app_title, Color bg_color, double target_fps) {
  using namespace std::chrono_literals;
  m_target_frame_time = 1000.0ms / target_fps;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "could not initialize sdl2: %s\n", SDL_GetError());
    throw AppException("could not initialize sdl2: ");
  }
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  auto screen_width = DM.w;
  auto screen_height = DM.h;
  m_window = std::unique_ptr<SDL_Window, SDLWindowDestroyer>(SDL_CreateWindow(
      app_title,
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      screen_width, screen_height,
      SDL_WINDOW_SHOWN
  ));
  if (m_window == nullptr) {
    fprintf(stderr, "could not create window: %s\n", SDL_GetError());
    throw AppException("could not create window");
  }
  SDL_SetWindowFullscreen(m_window.get(), SDL_WINDOW_FULLSCREEN);
  SDL_Surface* screenSurface = nullptr;
  screenSurface = SDL_GetWindowSurface(m_window.get());
  SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, bg_color.red(), bg_color.green(), bg_color.blue()));
}
FullscreenApplication::~FullscreenApplication() {
  SDL_Quit();
}
void FullscreenApplication::run() {
  bool should_continue = true;
  SDL_Event ev;

  while (should_continue) {
    auto start_time = std::chrono::system_clock::now();
    while (SDL_PollEvent(&ev) != 0) {
      if (ev.type == SDL_QUIT) {
        should_continue = false;
      }
      if (ev.type == SDL_KEYDOWN) {
        switch (ev.key.keysym.sym) {
          case SDLK_q:
            should_continue = false;
            break;
          default:
            break;
        }
      }
    }
    auto end_time =std::chrono::system_clock::now();
    auto computation_time = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    auto sleep_time = computation_time - m_target_frame_time;
    auto sleep = sleep_time.count();
    if (sleep > 0) {
      SDL_Delay(static_cast<Uint32>(sleep));
    }
    SDL_UpdateWindowSurface(m_window.get());
  }

}

#include <Color.hpp>
#include <FullscreenApplication.hpp>
#include <iostream>

constexpr Color bg_color = Color::RGB(75, 101, 132);
constexpr double target_fps = 60.0;

int main() {
  try {
    FullscreenApplication app("Kotitonttu GUI", bg_color, target_fps);
    app.run();
  } catch (const AppException& e) {
    std::cout << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

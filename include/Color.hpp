#pragma once

#include <cstdint>

class Color {
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
  uint8_t m_alpha;
 public:
  constexpr static Color RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept {return Color(r, g, b, a); }
  constexpr uint8_t red() const {return m_red;}
  constexpr uint8_t green() const {return m_green;}
  constexpr uint8_t blue() const {return m_blue;}
  constexpr uint8_t alpha() const {return m_alpha;}
 protected:
  constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_red(r), m_green(g), m_blue(b), m_alpha(a) {}
};

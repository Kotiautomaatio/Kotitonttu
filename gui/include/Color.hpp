//
// Created by tatu on 27.10.2018.
//
#pragma once

class Color {
  uint8_t m_red;
  uint8_t m_green;
  uint8_t m_blue;
  uint8_t m_alpha;
 public:
  constexpr static Color RGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {return Color(r, g, b, a); }
  constexpr uint8_t red() const {return m_red;}
  constexpr uint8_t green() const {return m_green;}
  constexpr uint8_t blue() const {return m_blue;}
 protected:
  constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : m_red(r), m_green(g), m_blue(b), m_alpha(a) {}
};

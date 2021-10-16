set(SOURCES
  Application.cpp
  Application.hpp
  gui/Color.hpp
  )

add_library(kotitonttu
  ${SOURCES}
  )

add_subdirectory(flatbuffers)
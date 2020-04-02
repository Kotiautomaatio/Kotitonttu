#pragma once

#include <Magnum/Ui/Plane.h>
#include <Magnum/Ui/UserInterface.h>
#include <Magnum/Ui/Button.h>

struct BaseUiPlane : Magnum::Ui::Plane {
  explicit BaseUiPlane(Magnum::Ui::UserInterface& ui);

  Magnum::Ui::Button buttonLamppu;


};

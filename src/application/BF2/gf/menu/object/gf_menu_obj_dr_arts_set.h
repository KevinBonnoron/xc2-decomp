#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjDrArtsSet : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

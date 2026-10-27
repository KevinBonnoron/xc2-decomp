#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjInn : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
};

} // namespace gf

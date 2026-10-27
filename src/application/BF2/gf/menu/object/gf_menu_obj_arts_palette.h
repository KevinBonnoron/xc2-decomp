#pragma once
#include "gf/menu/gf_menu_object.h"

namespace gf {

class GfMenuObjArtsPalette : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  static void push(unsigned int slot);
};

} // namespace gf

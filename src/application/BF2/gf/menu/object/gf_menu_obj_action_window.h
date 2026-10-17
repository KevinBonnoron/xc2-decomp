#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjActionWindow : public GfMenuObject {
public:
  GfMenuObjActionWindow(u32 handle);
  ~GfMenuObjActionWindow() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

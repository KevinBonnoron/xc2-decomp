#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjBtlMdlView : public GfMenuObject {
public:
  GfMenuObjBtlMdlView(u32 handle);
  ~GfMenuObjBtlMdlView() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjDrDetail : public GfMenuObject {
public:
  GfMenuObjDrDetail(u32 handle);
  ~GfMenuObjDrDetail() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

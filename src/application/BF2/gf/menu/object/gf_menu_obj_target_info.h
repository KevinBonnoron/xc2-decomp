#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjTargetInfo : public GfMenuObject {
public:
  GfMenuObjTargetInfo(u32 handle);
  ~GfMenuObjTargetInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

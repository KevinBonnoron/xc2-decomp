#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjEnvironmentInfo : public GfMenuObject {
public:
  GfMenuObjEnvironmentInfo(u32 handle);
  ~GfMenuObjEnvironmentInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

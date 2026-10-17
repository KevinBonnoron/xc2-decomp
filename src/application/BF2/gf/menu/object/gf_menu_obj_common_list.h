#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjCommonList : public GfMenuObject {
public:
  GfMenuObjCommonList(u32 handle);
  ~GfMenuObjCommonList() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

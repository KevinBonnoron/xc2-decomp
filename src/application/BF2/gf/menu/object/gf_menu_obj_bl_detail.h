#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjBlDetail : public GfMenuObject {
public:
  GfMenuObjBlDetail(u32 handle);
  ~GfMenuObjBlDetail() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

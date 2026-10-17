#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjQuestOrder : public GfMenuObject {
public:
  GfMenuObjQuestOrder(u32 handle);
  ~GfMenuObjQuestOrder() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

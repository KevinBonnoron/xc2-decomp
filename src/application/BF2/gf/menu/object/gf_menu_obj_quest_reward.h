#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjQuestReward : public GfMenuObject {
public:
  GfMenuObjQuestReward(u32 handle);
  ~GfMenuObjQuestReward() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

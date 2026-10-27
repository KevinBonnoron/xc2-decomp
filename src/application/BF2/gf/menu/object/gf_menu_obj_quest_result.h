#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjQuestResult : public GfMenuObject {
public:
  static void close();
  GfMenuObjQuestResult(u32 handle);
  ~GfMenuObjQuestResult() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

} // namespace gf

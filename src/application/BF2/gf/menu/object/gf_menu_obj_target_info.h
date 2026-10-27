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
  static void dispAllSymbol(bool disp);
  static void dispAllOther(bool disp);
  static void dispAllEnemy(bool disp);
  static void disp(bool disp);
};

} // namespace gf

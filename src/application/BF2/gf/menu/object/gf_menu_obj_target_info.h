#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjTargetInfo : public GfMenuObject {
public:
  GfMenuObjTargetInfo(u32 handle);
  ~GfMenuObjTargetInfo() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(GfMenuCallContext *context);
  static void dispAllSymbol(bool disp);
  static void dispAllOther(bool disp);
  static void dispAllEnemy(bool disp);
  static void disp(bool disp);
  static void startOpen(u32 handle, u32 object, int param0, int param1);
};

} // namespace gf

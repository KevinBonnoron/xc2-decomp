#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjBladeSet : public GfMenuObject {
public:
  static bool checkBladeRelease(u32 blade);
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam;

  static void registOpenParam(const OpenParam &);
};

} // namespace gf

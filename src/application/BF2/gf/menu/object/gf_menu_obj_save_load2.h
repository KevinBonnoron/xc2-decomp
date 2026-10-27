#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjSaveLoad2 : public GfMenuObject {
public:
  static void sendEvent(u32 handle, u32 type, u32 param);
  void initialize() override;
  void finalize() override;
  struct OpenParam {
    u16 unknown00; // Inferred role: mode; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
};

} // namespace gf

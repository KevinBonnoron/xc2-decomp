#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjMercenaryTop : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Role and original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  void sendOpenEvent(u32 handle, int type);
  void sendCloseEvent(u32 handle, int type);
  void initialize() override;
  void finalize() override;
};

} // namespace gf

#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjMercenaryForm : public GfMenuObject {
public:
  void sendOpenEvent(u32 handle, int type, f32 delay);
  void sendCloseEvent(u32 handle, int type, f32 delay);
  void initialize() override;
  void finalize() override;
};

} // namespace gf

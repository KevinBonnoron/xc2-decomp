#pragma once
#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjCommonInfo : public GfMenuObject {
public:
  void initialize() override;
  void finalize() override;
  void update() override;
  static void close(u32);
  static void closeAll();
  static void pausePickup();
  static void continuePickup();
};

} // namespace gf

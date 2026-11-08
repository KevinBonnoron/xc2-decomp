#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjComboRoute : public GfMenuObject {
public:
  GfMenuObjComboRoute(u32 handle);
  ~GfMenuObjComboRoute() override;
  static void close();
  static void disp(bool isDisp);
  static void open();
  void initialize() override;
  void finalize() override;
  void update() override;

  int unknown24[8]; // Inferred role: unused, -1 at start; original member name unknown.
};

static_assert(offsetof(GfMenuObjComboRoute, unknown24) == 0x24, "");
static_assert(sizeof(GfMenuObjComboRoute) == 0x48, "");

} // namespace gf

#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjPartyGauge : public GfMenuObject {
public:
  GfMenuObjPartyGauge(u32 handle);
  ~GfMenuObjPartyGauge() override;
  static void open();
  static void close();
  static void disp(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;

  int unknown24; // Inferred role: unused, -1 at start; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyGauge, unknown24) == 0x24, "");
static_assert(sizeof(GfMenuObjPartyGauge) == 0x28, "");

} // namespace gf

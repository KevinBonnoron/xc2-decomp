#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjOtherCursor : public GfMenuObject {
public:
  GfMenuObjOtherCursor(u32 handle);
  ~GfMenuObjOtherCursor() override;
  void initialize() override;
  void finalize() override;
  static void disp(bool disp);

  u32 unknown24; // Role and original member name unknown, zeroed by the constructor.
  u8 _28[0x30 - 0x28];
  u64 unknown30; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjOtherCursor, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjOtherCursor, unknown30) == 0x30, "");
static_assert(sizeof(GfMenuObjOtherCursor) == 0x38, "");

} // namespace gf

#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjMainSubmenu : public GfMenuObject {
public:
  GfMenuObjMainSubmenu(u32 handle);
  ~GfMenuObjMainSubmenu() override;
  void initialize() override;
  void finalize() override;
  void update() override;

  static bool isEnableSkipTime();

  u32 unknown24;                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown28;                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown2c;                          // Role and original member name unknown, cleared by the constructor.
  ui::UISelectObjList *unknown30;         // Inferred role: menu objects; original member name unknown.
  mm::mtl::FixedVector<int, 8> unknown38; // Inferred role: enabled menu entries; original member name unknown.
  u8 _60[0x64 - 0x60];
  bool unknown64; // Role and original member name unknown, set by the constructor.
  u8 _65[0x68 - 0x65];
  GfMenuCallContext *unknown68; // Inferred role: call context; original member name unknown.
  int unknown70;                // Role and original member name unknown, -1 at start.
  int unknown74[2];             // Role and original member name unknown, -1 at start.
  u8 _7c[0x80 - 0x7c];
};

static_assert(offsetof(GfMenuObjMainSubmenu, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjMainSubmenu, unknown74) == 0x74, "");
static_assert(sizeof(GfMenuObjMainSubmenu) == 0x80, "");

} // namespace gf

#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

class GfMenuObjBladeSwitch : public GfMenuObject {
public:
  GfMenuObjBladeSwitch(u32 handle);
  ~GfMenuObjBladeSwitch() override;
  static void open();
  static void close();
  static void setActive(bool isActive);
  void initialize() override;
  void finalize() override;

  bool unknown24; // Role and original member name unknown, cleared by the constructor.
  bool unknown25; // Role and original member name unknown, cleared by the constructor.
  bool unknown26; // Role and original member name unknown, cleared by the constructor.
  u8 _27[0x28 - 0x27];
  GfMenuSequence<GfMenuObjBladeSwitch, 8> unknown28; // Inferred role: queued steps; original member name unknown.
  u8 _2b8[0x2c0 - 0x2b8];
};

static_assert(offsetof(GfMenuObjBladeSwitch, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjBladeSwitch, unknown25) == 0x25, "");
static_assert(offsetof(GfMenuObjBladeSwitch, unknown26) == 0x26, "");
static_assert(offsetof(GfMenuObjBladeSwitch, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjBladeSwitch) == 0x2c0, "");

} // namespace gf

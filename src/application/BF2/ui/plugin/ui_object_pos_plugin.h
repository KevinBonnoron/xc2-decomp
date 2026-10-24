#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "types.h"
#include "ui/plugin/ui_object_disp_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectPosPlugin : public UIObjectDispPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectPosPlugin();
  virtual ~UIObjectPosPlugin();
  static UIObjectPosPlugin *create(u32 handle, s16 x, s16 y);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  mm::Pnt<s16> unknown7c; // Inferred role: pos; original member name unknown.
  bool unknown80;         // Inferred role: adjust screen; original member name unknown.
  u16 unknown82;          // Inferred role: adjust width; original member name unknown.
  u16 unknown84;          // Inferred role: adjust height; original member name unknown.
  s16 unknown86;          // Inferred role: adjust offset x; original member name unknown.
  s16 unknown88;          // Inferred role: adjust offset y; original member name unknown.
  u32 unknown8c;          // Inferred role: offset mode; original member name unknown.
  bool unknown90;         // Inferred role: adjusting; original member name unknown.
};

static_assert(offsetof(UIObjectPosPlugin, unknown7c) == 0x7c, "");
static_assert(offsetof(UIObjectPosPlugin, unknown80) == 0x80, "");
static_assert(offsetof(UIObjectPosPlugin, unknown82) == 0x82, "");
static_assert(offsetof(UIObjectPosPlugin, unknown86) == 0x86, "");
static_assert(offsetof(UIObjectPosPlugin, unknown8c) == 0x8c, "");
static_assert(offsetof(UIObjectPosPlugin, unknown90) == 0x90, "");
static_assert(sizeof(UIObjectPosPlugin) == 0x98, "");

} // namespace ui

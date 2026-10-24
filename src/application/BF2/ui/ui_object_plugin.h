#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectAcc;

class UIObjectPlugin : public mm::mtl::ReferenceObject {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectPlugin();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void reload(UIObjectAcc &acc) {}
  virtual void execute(UIObjectAcc &acc);
  virtual bool isNeedUpdate(UIObjectAcc &acc);

  UIObjectPlugin *unknown10; // Inferred role: next; original member name unknown.
  u32 unknown18;             // Inferred role: need update; original member name unknown.
};

static_assert(offsetof(UIObjectPlugin, unknown10) == 0x10, "");
static_assert(offsetof(UIObjectPlugin, unknown18) == 0x18, "");
static_assert(sizeof(UIObjectPlugin) == 0x20, "");

} // namespace ui

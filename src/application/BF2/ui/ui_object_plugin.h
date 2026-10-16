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

  UIObjectPlugin *next;
  u32 needUpdate;
};

static_assert(offsetof(UIObjectPlugin, next) == 0x10, "");
static_assert(offsetof(UIObjectPlugin, needUpdate) == 0x18, "");
static_assert(sizeof(UIObjectPlugin) == 0x20, "");

} // namespace ui

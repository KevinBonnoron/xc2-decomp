#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"
#include "ui/plugin/ui_object_pos_plugin.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObjectWorldPosPlugin : public UIObjectPosPlugin {
public:
  static mm::mtl::RTTI m_rtti;

  UIObjectWorldPosPlugin();
  virtual ~UIObjectWorldPosPlugin();
  static UIObjectWorldPosPlugin *create(u32 handle);
  virtual void execute(UIObjectAcc &acc);
  virtual const mm::mtl::RTTI *getRTTI() const;

  mm::Vec3 unknowna0; // Inferred role: world pos; original member name unknown.
};

static_assert(offsetof(UIObjectWorldPosPlugin, unknowna0) == 0xa0, "");
static_assert(sizeof(UIObjectWorldPosPlugin) == 0xb0, "");

} // namespace ui

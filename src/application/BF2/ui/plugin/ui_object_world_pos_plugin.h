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

  static UIObjectWorldPosPlugin *create(u32 handle);

  mm::Vec3 worldPos;
};

static_assert(offsetof(UIObjectWorldPosPlugin, worldPos) == 0xa0, "");

} // namespace ui

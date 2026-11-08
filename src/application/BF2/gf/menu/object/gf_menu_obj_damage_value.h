#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_many_objects.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {

class GfMenuObjDamageValue : public GfMenuObject {
public:
  // Queued by GfMenuManyObjects; the game gives it its own vtable, inheriting the dispose of the base. Layout from open, which compares
  // the position with the queued ones.
  struct DamageInfo : GfMenuManyObjects::InfoType {
    mm::Vec3 unknown10; // Inferred role: position of the damage value; original member name unknown.
  };

  GfMenuObjDamageValue(u32 handle);
  ~GfMenuObjDamageValue() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void closeAll();
};

static_assert(offsetof(GfMenuObjDamageValue::DamageInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjDamageValue::DamageInfo) == 0x20, "");

} // namespace gf

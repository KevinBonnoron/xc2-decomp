#pragma once
#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfMenuObjCompass : public GfMenuObject {
public:
  // Inferred role: entry of the compass icon list; original name unknown.
  struct unknown004 {
    u32 unknown00; // Inferred role: icon object handle; original member name unknown.
    u32 unknown04; // Inferred role: locator ids; original member name unknown.
    u32 unknown08; // Role and original member name unknown.
    int unknown0c; // Inferred role: frames left before the icon is hidden; original member name unknown.
  };

  GfMenuObjCompass(u32 handle);
  ~GfMenuObjCompass() override;
  static void close();
  static void open();
  void initialize() override;
  void finalize() override;

  static mm::mtl::FixedVector<unknown004, 32> m_IconObjList;
};

static_assert(sizeof(GfMenuObjCompass::unknown004) == 0x10, "");
static_assert(sizeof(GfMenuObjCompass) == 0x28, "");

} // namespace gf

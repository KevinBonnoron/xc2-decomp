#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"

namespace gf {

class GfMenuObjSort : public GfMenuObject {
public:
  GfMenuObjSort(u32 handle);
  ~GfMenuObjSort() override;
  static void close();
  static u16 getSortID(u16 id, u16 index);
  static void setSortLabelText(u16 id, u32 handle);
  void refreshItem(u32 selected, u32 count);
  void initialize() override;
  void finalize() override;
  void update() override;

  u32 unknown24; // Inferred role: handle of the sort object; original member name unknown.
  u32 unknown28; // Role and original member name unknown, zeroed by the constructor.
  u32 unknown2c; // Role and original member name unknown, zeroed by the constructor.
  u32 unknown30; // Inferred role: sort type count; original member name unknown.
};

static_assert(offsetof(GfMenuObjSort, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjSort, unknown30) == 0x30, "");

} // namespace gf

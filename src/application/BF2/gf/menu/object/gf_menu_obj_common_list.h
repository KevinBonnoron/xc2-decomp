#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_pnt.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonList : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00;          // Inferred role: handle of the object the list is placed by, 0 for a position; original member name unknown.
    const char *unknown08;  // Inferred role: layout name of the placement; original member name unknown.
    mm::Pnt<int> unknown10; // Inferred role: position; original member name unknown.
    int unknown18;          // Inferred role: row count; original member name unknown.
    int unknown1c;          // Inferred role: selected row; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close();
  static void moveCursor(u32 handle, int index);
  static void setupPlugin(u32 handle);
  GfMenuObjCommonList(u32 handle);
  ~GfMenuObjCommonList() override;
  void initialize() override;
  void finalize() override;
  void update() override;
};

static_assert(offsetof(GfMenuObjCommonList::OpenParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjCommonList::OpenParam, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjCommonList::OpenParam, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjCommonList::OpenParam, unknown1c) == 0x1c, "");
static_assert(sizeof(GfMenuObjCommonList::OpenParam) == 0x20, "");

} // namespace gf

#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_pnt.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjMinimap2 : public GfMenuObject {
public:
  GfMenuObjMinimap2(u32 handle);
  ~GfMenuObjMinimap2() override;
  static void changeMap();
  static void close();
  static void open();
  static void dispOffIconTable(u32 index, mm::mtl::FixedVector<u32, 128> &table);
  static void setupIconTable(u32 index, mm::mtl::FixedVector<u32, 128> &table, u32 image, mm::Pnt<s16> pos);
  static void destroyIconTable(mm::mtl::FixedVector<u32, 128> &table);
  static void createIconTable(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 128> &table);
  bool refreshMapPosition();
  void initialize() override;
  void finalize() override;

  static void enable();
  static void disable();

  bool unknown24;                           // Role and original member name unknown, cleared by the constructor.
  mm::mtl::FixedVector<u32, 128> unknown28; // Inferred role: icon objects; element type inferred from the stride of the game's loops; original member name unknown.
  u8 _230[0x240 - 0x230];
  u8 unknown240; // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjMinimap2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMinimap2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMinimap2, unknown240) == 0x240, "");
static_assert(sizeof(GfMenuObjMinimap2) == 0x248, "");

} // namespace gf

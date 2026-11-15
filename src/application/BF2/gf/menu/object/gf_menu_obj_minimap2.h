#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_math/mm_pnt.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuObjMinimap2 : public GfMenuObject {
public:
  // Layout from the inline constructor in initialize (0x710049e34c): 0x28 bytes from the allocator, 0x0c-0x1b cleared, owner at 0x20.
  class MainListener : public ui::UIObjectListener {
  public:
    // Inferred role: preset control and map size mode; original type name unknown.
    struct unknown003 {
      int unknown00; // Inferred role: running preset control, -1 when none; original member name unknown.
      int unknown04; // Inferred role: map size mode, 0 normal, 1 enlarged, 2 hidden; original member name unknown.
    };

    MainListener(GfMenuObjMinimap2 *owner) : unknown0c(0), unknown10(), unknown18(0), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: 1 while the map is shown; original member name unknown.
    unknown003 unknown10;
    u32 unknown18;                // Role and original member name unknown, cleared by the constructor.
    GfMenuObjMinimap2 *unknown20; // Inferred role: owner; original member name unknown.
  };

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
  void update() override;

  static void enable();
  static void disable();

  bool unknown24;                           // Role and original member name unknown, cleared by the constructor.
  mm::mtl::FixedVector<u32, 128> unknown28; // Inferred role: icon objects; element type inferred from the stride of the game's loops; original member name unknown.
  mm::Rect<s16> unknown230;                 // Inferred role: map area in the layout, filled by ui::UIObjectAcc::getLayoutRect; original member name unknown.
  mm::Rect<s16> unknown238;                 // Inferred role: map dummy image area, filled by ui::UIObjectAcc::getRect; original member name unknown.
  u8 unknown240;                            // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjMinimap2, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMinimap2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMinimap2, unknown240) == 0x240, "");
static_assert(offsetof(GfMenuObjMinimap2::MainListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjMinimap2::MainListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjMinimap2::MainListener, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuObjMinimap2::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjMinimap2::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjMinimap2, unknown230) == 0x230, "");
static_assert(offsetof(GfMenuObjMinimap2, unknown238) == 0x238, "");
static_assert(sizeof(GfMenuObjMinimap2) == 0x248, "");

} // namespace gf

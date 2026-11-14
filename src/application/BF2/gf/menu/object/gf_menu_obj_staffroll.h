#pragma once
#include <stddef.h>

#include "gf/menu/gf_credit_reader.h"
#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace fw {
class CommonResource;
} // namespace fw

namespace ui {
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjStaffroll : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjStaffroll *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjStaffroll *unknown20; // Inferred role: owner; original member name unknown.
  };

  // Inferred role: scrolled row; original member names unknown.
  struct RowInfo {
    u8 unknown00[0xe];                      // Inferred role: row values and flags; original member name unknown.
    mm::mtl::FixedVector<u32, 4> unknown10; // Inferred role: row text objects; original member name unknown.
  };

  GfMenuObjStaffroll(u32 handle);
  ~GfMenuObjStaffroll() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void start(f32 time, int type);
  static void fadeout();
  u32 createText(u32 index, const CreditReader::Column &column);

  u8 _24[0x28 - 0x24];
  fw::CommonResource *unknown28; // Inferred role: credits resource; original member name unknown.
  CreditReader unknown30;        // Inferred role: credits table reader; original member name unknown.
  int unknown58;                 // Role and original member name unknown, cleared by the constructor.
  u32 unknown5c;                 // Role and original member name unknown, cleared by the constructor.
  u32 unknown60;                 // Role and original member name unknown, cleared by the constructor.
  f32 unknown64;                 // Role and original member name unknown, cleared by the constructor.
  f32 unknown68;                 // Role and original member name unknown, cleared by the constructor.
  bool unknown6c;                // Role and original member name unknown, cleared by the constructor.
  u8 _6d[0x70 - 0x6d];
  ui::UISelectObjList *unknown70;     // Inferred role: row objects; original member name unknown.
  mm::mtl::Vector<RowInfo> unknown78; // Inferred role: scrolled rows; original member name unknown.
};

static_assert(offsetof(GfMenuObjStaffroll::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjStaffroll::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjStaffroll::RowInfo) == 0x28, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown6c) == 0x6c, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjStaffroll, unknown78) == 0x78, "");
static_assert(sizeof(GfMenuObjStaffroll) == 0xa0, "");

} // namespace gf

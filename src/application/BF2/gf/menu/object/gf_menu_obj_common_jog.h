#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlRevolveSelect;
class UISelectObjList;
struct EventData;
} // namespace ui

namespace gf {

class GfMenuCallContext;

class GfMenuObjCommonJog : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjCommonJog *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjCommonJog *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenParam {
    OpenParam() : unknown00(0), unknown04(-1) {}

    u32 unknown00; // Inferred role: open mode; original member name unknown.
    u32 unknown04; // Inferred role: selected menu, -1 for none; original member name unknown.
  };

  // Inferred role: visited menu entry, menu then selected index; original type name unknown.
  struct unknown002 {
    u16 unknown00; // Inferred role: menu; original member name unknown.
    u16 unknown02; // Inferred role: selected index; original member name unknown.
  };

  GfMenuObjCommonJog(u32 handle);
  ~GfMenuObjCommonJog() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  bool setup(u32 menu, int select);
  void startJogChange(u16 menu, int select);
  void listenerItemRevlover(const ui::EventData &event);
  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void pop(GfMenuCallContext *context);
  static void enable(GfMenuCallContext *context);
  static void disable(GfMenuCallContext *context);
  static void close(GfMenuCallContext *context);

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;     // Inferred role: item objects; original member name unknown.
  ui::UISelectObjList *unknown30;     // Inferred role: text objects; original member name unknown.
  ui::UICtrlRevolveSelect *unknown38; // Inferred role: ring control; original member name unknown.
  u32 unknown40;                      // Inferred role: selected object; original member name unknown.
  u8 _44[0x48 - 0x44];
  u8 *unknown48;  // Inferred role: menu table; original member name unknown.
  u8 *unknown50;  // Inferred role: icon table; original member name unknown.
  int unknown58;  // Inferred role: ring center offset; original member name unknown.
  bool unknown5c; // Inferred role: ring rolled up flag; original member name unknown.
  u8 _5d[0x5e - 0x5d];
  u16 unknown5e; // Inferred role: previous selected menu; original member name unknown.
  u16 unknown60; // Inferred role: selected menu; original member name unknown.
  u8 _62[0x64 - 0x62];
  int unknown64;                                 // Inferred role: selected index, -1 when none; original member name unknown.
  mm::mtl::FixedVector<unknown002, 4> unknown68; // Inferred role: visited menus; original member name unknown.
};

static_assert(offsetof(GfMenuObjCommonJog::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjCommonJog::MainListener) == 0x28, "");

static_assert(offsetof(GfMenuObjCommonJog::OpenParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjCommonJog::OpenParam) == 0x08, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown5e) == 0x5e, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown64) == 0x64, "");
static_assert(offsetof(GfMenuObjCommonJog, unknown68) == 0x68, "");
static_assert(sizeof(GfMenuObjCommonJog) == 0x80, "");

} // namespace gf

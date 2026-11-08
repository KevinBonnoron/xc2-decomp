#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlObject;
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuObjBladeKizunaRing : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjBladeKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct Achievement {
    Achievement(u16 line, u16 level, u16 state) : unknown00(line), unknown02(level), unknown04(state) {}

    u16 unknown00; // Inferred role: achievement line; original member name unknown.
    u16 unknown02; // Inferred role: achievement level; original member name unknown.
    u16 unknown04; // Inferred role: release state, 1 to order and 3 to release; original member name unknown.
  };

  static void close();
  static void open();
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setupName(ui::UIObjectAcc &acc);
  static int getAchievementList(mm::mtl::FixedVector<Achievement, 50> &list);
  GfMenuObjBladeKizunaRing(u32 handle);
  ~GfMenuObjBladeKizunaRing() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqComplete();

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28; // Inferred role: achievement icon objects; original member name unknown.
  ui::UICtrlObject *unknown30;    // Inferred role: ring frame control; original member name unknown.
  u8 _38[0x3c - 0x38];
  u16 unknown3c;  // Role and original member name unknown, cleared by the constructor.
  u16 unknown3e;  // Role and original member name unknown, cleared by the constructor.
  bool unknown40; // Role and original member name unknown, cleared by the constructor.
  u8 _41[0x44 - 0x41];
  u32 unknown44; // Role and original member name unknown, cleared by the constructor.
  int unknown48; // Inferred role: control id of the achievement icon, -1 when none; original member name unknown.
  int unknown4c; // Inferred role: completion state, 1 to start the next icon and 2 to wait for it; original member name unknown.
  f32 unknown50; // Inferred role: unused, 1.0 at start; original member name unknown.
  u8 _54[0x58 - 0x54];
  mm::mtl::FixedVector<Achievement, 50> unknown58;        // Inferred role: achievements to complete; original member name unknown.
  GfMenuSequence<GfMenuObjBladeKizunaRing, 8> unknown190; // Inferred role: steps; original member name unknown.
};

static_assert(sizeof(GfMenuObjBladeKizunaRing::Achievement) == 6, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown3e) == 0x3e, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown4c) == 0x4c, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBladeKizunaRing, unknown190) == 0x190, "");
static_assert(sizeof(GfMenuObjBladeKizunaRing) == 0x420, "");

} // namespace gf

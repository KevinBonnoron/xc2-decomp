#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuItemList;

class GfMenuObjDrKizunaRing : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjDrKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDrKizunaRing(u32 handle);
  ~GfMenuObjDrKizunaRing() override;

  static u32 getSkillUnlockLevel(u32 driver);
  static void movePointer(u32 handle, int index, ui::UISelectObjList *list);
  static void setupMain(ui::UIObjectAcc &acc);
  static void setupDriverSkillInfo(ui::UIObjectAcc &acc);
  static void setupSkillDetail(ui::UIObjectAcc &acc);

  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &, u32);
  bool seqCircleAnime();
  bool seqEndAnime();
  bool seqExecSkill();
  bool seqUnlockAnime();
  bool seqWait();

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;      // Inferred role: ring objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown30; // Inferred role: reference-counted object; type and original member name unknown.
  bool unknown38;                      // Role and original member name unknown, cleared by the constructor.
  u32 unknown3c;                       // Role and original member name unknown, cleared by the constructor.
  int unknown40;                       // Role and original member name unknown, set to -1 by the constructor.
  u8 _44[0x48 - 0x44];
  GfMenuCallContext *unknown48; // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown50; // Inferred role: call context; original member name unknown.
  u8 _58[0x60 - 0x58];
  u32 unknown60; // Role and original member name unknown, cleared by the constructor.
  u8 _64[0x68 - 0x64];
  GfMenuSequence<GfMenuObjDrKizunaRing, 8> unknown68; // Inferred role: skill learning steps; original member name unknown.
  int unknown2f8;                                     // Inferred role: step state; original member name unknown.
  u8 _2fc[0x300 - 0x2fc];
  GfMenuCallContext *unknown300; // Inferred role: call context; original member name unknown.
  GfMenuItemList *unknown308;    // Inferred role: reward items; original member name unknown.
  u32 unknown310;                // Role and original member name unknown, cleared by the constructor.
  u8 _314[0x318 - 0x314];
};

static_assert(offsetof(GfMenuObjDrKizunaRing::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown60) == 0x60, "");

static_assert(offsetof(GfMenuObjDrKizunaRing, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown300) == 0x300, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown308) == 0x308, "");
static_assert(offsetof(GfMenuObjDrKizunaRing, unknown310) == 0x310, "");
static_assert(sizeof(GfMenuObjDrKizunaRing) == 0x318, "");

} // namespace gf

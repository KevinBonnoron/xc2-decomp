#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UICtrlCursorSelect;
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuItemList;
struct GAME_VOICE_HANDLE;
struct GF_SCOM_HANDLE;

class GfMenuObjBlKizunaRing : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBlKizunaRing *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  class RingListener : public ui::UIObjectListener {
  public:
    RingListener(GfMenuObjBlKizunaRing *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: cursor needs no sound after the first selection; original member name unknown.
    u8 _10[0x1c - 0x10];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  class RingPadListener : public ui::UIObjectListener {
  public:
    RingPadListener(GfMenuObjBlKizunaRing *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  class SkillDetailListener : public ui::UIObjectListener {
  public:
    SkillDetailListener(GfMenuObjBlKizunaRing *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  class BladeSkillInfoListener : public ui::UIObjectListener {
  public:
    BladeSkillInfoListener(GfMenuObjBlKizunaRing *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    u8 _1c[0x20 - 0x1c];
    GfMenuObjBlKizunaRing *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct OpenParam {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u32 unknown04; // Inferred role: blade; original member name unknown.
  };

  struct Achievement {
    Achievement(u16 line, u16 level, u16 state) : unknown00(line), unknown02(level), unknown04(state) {}

    u16 unknown00; // Inferred role: achievement line; original member name unknown.
    u16 unknown02; // Inferred role: achievement level; original member name unknown.
    u16 unknown04; // Inferred role: release state, 1 to order and 3 to release; original member name unknown.
  };

  GfMenuObjBlKizunaRing(u32 handle);
  ~GfMenuObjBlKizunaRing() override;
  static void registOpenParam(const OpenParam &param);
  static void openForMercenary(u32 handle, u32 blade, u16 group);
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool isLockPos(int index);
  static bool isScreenLR(u32 screen);
  static void setupCircle(ui::UIObjectAcc &);
  static void setupMain(ui::UIObjectAcc &acc);
  static void setupBladeSkillInfo(ui::UIObjectAcc &acc);
  static void setupSkillSimple(ui::UIObjectAcc &acc);
  static void setupSkillDetail(ui::UIObjectAcc &acc);
  static void setupRing(ui::UIObjectAcc &acc);
  static void setupRingList(ui::UIObjectAcc &acc, ui::UISelectObjList *list);
  static void movePointer(u32 handle, int index, ui::UISelectObjList *list);
  static void dispDetail(ui::UIObjectAcc &acc, u32 blade);
  static void refreshRing(ui::UIObjectAcc &acc);
  static int getAchievementList(mm::mtl::FixedVector<Achievement, 50> &list, u32 &count, u32 &flags);
  static bool procAchieve(u32 handle, GfMenuObjBlKizunaRing *object);
  bool seqAchieve();
  bool seqComplete();
  bool seqEnd();
  bool seqWait();
  bool seqWaitVoice();

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;    // Inferred role: node objects; original member name unknown.
  ui::UICtrlCursorSelect *unknown30; // Inferred role: node cursor; original member name unknown.
  bool unknown38;                    // Inferred role: unused, cleared at start; original member name unknown.
  bool unknown39;                    // Inferred role: skill detail shown; original member name unknown.
  u8 _3a[0x3c - 0x3a];
  u32 unknown3c; // Inferred role: ring level of the selected node; original member name unknown.
  int unknown40; // Inferred role: selected node index, -1 at start; original member name unknown.
  u8 _44[0x48 - 0x44];
  GfMenuCallContext *unknown48; // Inferred role: call context; original member name unknown.
  u32 unknown50;                // Inferred role: achievement count; original member name unknown.
  u8 _54[0x58 - 0x54];
  GfMenuCallContext *unknown58;                    // Inferred role: call context; original member name unknown.
  mm::mtl::FixedVector<Achievement, 50> unknown60; // Inferred role: achievements to complete; original member name unknown.
  u32 unknown198;                                  // Inferred role: node animation; original member name unknown.
  u8 _19c[0x1a0 - 0x19c];
  GfMenuSequence<GfMenuObjBlKizunaRing, 8> unknown1a0; // Inferred role: achievement steps; original member name unknown.
  int unknown430;                                      // Inferred role: step; original member name unknown.
  int unknown434;                                      // Inferred role: item message step; original member name unknown.
  int unknown438;                                      // Inferred role: open mode, 0 from the main menu; original member name unknown.
  int unknown43c;                                      // Inferred role: blade when opened for a mercenary; original member name unknown.
  GfMenuCallContext *unknown440;                       // Inferred role: item message call context; original member name unknown.
  GfMenuItemList *unknown448;                          // Inferred role: item message list; original member name unknown.
  u32 unknown450;                                      // Inferred role: unused; original member name unknown.
  u32 unknown454;                                      // Inferred role: achievement index; original member name unknown.
  GAME_VOICE_HANDLE *unknown458;                       // Inferred role: blade voice; original member name unknown.
  u32 unknown460;                                      // Inferred role: node icon; original member name unknown.
  u8 _464[0x468 - 0x464];
  GF_SCOM_HANDLE *unknown468; // Inferred role: voice request; original member name unknown.
};

static_assert(offsetof(GfMenuObjBlKizunaRing::OpenParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjBlKizunaRing::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlKizunaRing::RingListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjBlKizunaRing::RingListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlKizunaRing::RingPadListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlKizunaRing::SkillDetailListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjBlKizunaRing::BladeSkillInfoListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlKizunaRing::OpenParam) == 0x08, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown39) == 0x39, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown58) == 0x58, "");
static_assert(sizeof(GfMenuObjBlKizunaRing::Achievement) == 6, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown198) == 0x198, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown430) == 0x430, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown434) == 0x434, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown438) == 0x438, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown440) == 0x440, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown448) == 0x448, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown450) == 0x450, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown454) == 0x454, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown458) == 0x458, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown460) == 0x460, "");
static_assert(offsetof(GfMenuObjBlKizunaRing, unknown468) == 0x468, "");
static_assert(sizeof(GfMenuObjBlKizunaRing) == 0x470, "");

} // namespace gf

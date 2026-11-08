#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
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

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuFieldSkillList;
class GfMenuMissionList;
class GfMenuReferenceNumber;
class GfMenuTeamList;

class GfMenuObjMercenaries : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjMercenaries *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjMercenaries(u32 handle);
  ~GfMenuObjMercenaries() override;
  static void setupLocationSelect(ui::UIObjectAcc &acc);
  static void setupLocationZone(ui::UIObjectAcc &acc, u16 zone);
  static void setupMission(ui::UIObjectAcc &acc);
  static void setupMercenaries(ui::UIObjectAcc &acc);
  static void updateTeamList(GfMenuTeamList *list);
  static void updateMissionList(GfMenuMissionList *list, u16 zone);
  static void updateBladeListReserver(GfMenuBladeList *list);
  static void updateBladeList(GfMenuBladeList *list, u32 team);
  static void updateFieldSkillList(GfMenuFieldSkillList *list, const GfMenuBladeList *blades);
  static bool isExistFieldSkill(u32 mission, u32 index);
  static void moveFieldSkillEnd(ui::UIObjectAcc &acc, u32 mission, u32 index);
  static void setupMercenariesCondParam(ui::UIObjectAcc &acc, int index, u32 type, const char *adapterFormat, const char *iconFormat);
  static bool isInvokeFieldSkill(u32 mission, u32 team);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqRewardStart();
  bool seqRewardStart2();
  bool seqRewardStart3();
  bool seqRewardComp();
  bool seqRewardComp2();
  bool seqRewardComp3();
  bool seqRewardComp4();
  bool seqRewardComp5();

  u8 _24[0x28 - 0x24];
  GfMenuCallContext *unknown28;        // Inferred role: call context; original member name unknown.
  ui::UISelectObjList *unknown30;      // Inferred role: list objects, not cleared by the constructor; original member name unknown.
  mm::mtl::ReferenceObject *unknown38; // Inferred role: reference-counted object; type and original member name unknown.
  ui::UISelectObjList *unknown40;      // Inferred role: list objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown48; // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuBladeList *unknown50;          // Inferred role: blades; original member name unknown.
  GfMenuFieldSkillList *unknown58;     // Inferred role: field skills; original member name unknown.
  GfMenuBladeList *unknown60;          // Inferred role: blades; original member name unknown.
  GfMenuMissionList *unknown68;        // Inferred role: missions; original member name unknown.
  GfMenuTeamList *unknown70;           // Inferred role: teams; original member name unknown.
  mm::mtl::ReferenceObject *unknown78; // Inferred role: reference-counted object; type and original member name unknown.
  mm::mtl::ReferenceObject *unknown80; // Inferred role: reference-counted object; type and original member name unknown.
  mm::mtl::ReferenceObject *unknown88; // Inferred role: reference-counted object; type and original member name unknown.
  mm::mtl::ReferenceObject *unknown90; // Inferred role: reference-counted object; type and original member name unknown.
  u32 unknown98;                       // Role and original member name unknown, cleared by the constructor.
  u16 unknown9c;                       // Role and original member name unknown, set to 1 by the constructor.
  u16 unknown9e;                       // Role and original member name unknown, cleared by the constructor.
  u16 unknowna0;                       // Role and original member name unknown, cleared by the constructor.
  u8 _a2[0xa8 - 0xa2];
  GfMenuBladeList *unknown0a8;      // Inferred role: blades; original member name unknown.
  GfMenuFieldSkillList *unknown0b0; // Inferred role: field skills; original member name unknown.
  GfMenuBladeList *unknown0b8;      // Inferred role: blades; original member name unknown.
  GfMenuBladeList *unknown0c0;      // Inferred role: blades; original member name unknown.
  GfMenuBladeList *unknown0c8;      // Inferred role: blades; original member name unknown.
  u64 unknown0d0;                   // Role and original member name unknown, cleared by the constructor.
  u64 unknown0d8;                   // Role and original member name unknown, cleared by the constructor.
  u16 unknown0e0;                   // Role and original member name unknown, cleared by the constructor.
  u8 _e2[0xe8 - 0xe2];
  GfMenuSequence<GfMenuObjMercenaries, 8> unknown0e8; // Inferred role: queued steps; original member name unknown.
  int unknown378;                                     // Inferred role: control of the reward screen steps; original member name unknown.
  u8 _37c[0x380 - 0x37c];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown380; // Inferred role: reference number; original member name unknown.
  u32 unknown388;                                          // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjMercenaries, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaries::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown0a8) == 0xa8, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown0d0) == 0xd0, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown0e0) == 0xe0, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown0e8) == 0xe8, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown378) == 0x378, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown380) == 0x380, "");
static_assert(offsetof(GfMenuObjMercenaries, unknown388) == 0x388, "");

} // namespace gf

#pragma once
#include <stddef.h>

#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"
#include "mm_thread/mm_thread_csection.h"
#include "types.h"
#include "ui/list/ui_list_info.h"
#include "ui/ui_str.h"

namespace gf {

struct MenuEnemyInfo;
struct MenuItemInfo;

class GfMenuReference : public mm::mtl::PtrSingleton<GfMenuReference> {
public:
  static const u32 ARTS_PALETTE_COUNT = 3;
  static const u32 ALL_ARTS_PALETTE_COUNT = 9;

  enum HOMURA_MODE {};

  struct FieldSkillInfo {
    u32 unknown00; // Inferred role: id; original member name unknown.
  };

  struct ElemComboRoot {
    ElemComboRoot() : unknown00(0), unknown04() {}

    u32 unknown00;                  // Inferred role: id; original member name unknown.
    mm::mtl::BitFlag<32> unknown04; // Inferred role: flags; original member name unknown.
  };

  struct ElementComboParty {
    u32 unknown00; // Inferred role: id; original member name unknown.
    f32 unknown04; // Inferred role: time left; original member name unknown.
  };

  struct ReferenceNumber {
    int unknown00; // Inferred role: min; original member name unknown.
    int unknown04; // Inferred role: max; original member name unknown.
    int unknown08; // Inferred role: value; original member name unknown.
  };

  struct ArtsPaletteInfo {
    ArtsPaletteInfo() : unknown00(0), unknown04(0.0f) {}

    u16 unknown00; // Inferred role: arts id; original member name unknown.
    f32 unknown04; // Inferred role: recast; original member name unknown.
  };

  struct ArtsPalette {
    ArtsPaletteInfo unknown00;             // Inferred role: info; original member name unknown.
    GfMenuObjUtil::ArtsIconInfo unknown08; // Inferred role: icon info; original member name unknown.
    u32 unknown1c;                         // Inferred role: element type; original member name unknown.
    bool unknown20;                        // Inferred role: enable; original member name unknown.
    u32 unknown24;                         // Inferred role: disable flags; original member name unknown.
  };

  static bool isInitialized();
  static void initReferenceNumber(u32 index);
  static void resetDriverVirtual();
  static void postReset();
  static u32 getFieldSkillMax();
  static void getFieldSkillInfo(u8 index, FieldSkillInfo &info);
  static void setArtsPaletteInfo(u8 index, const ArtsPaletteInfo &info);
  static void setArtsPaletteEnable(u8 index, bool isEnable, u32 disableFlags);
  static const ArtsPaletteInfo &getArtsPaletteInfo(u8 index);
  static const GfMenuObjUtil::ArtsIconInfo &getArtsPaletteIconInfo(u8 index);
  static u32 getArtsPaletteElementType(u8 index);
  static bool isArtsPaletteEnable(u8 index);
  static u32 getArtsPaletteDisable(u8 index);
  static u32 getTargetEnemyBuff(u32 index);
  static u32 getTargetEnemyWeakAttr();
  static void setChainNum(u32 chainNum);
  static u32 getChainNum();
  static void setWeaponJustRange(bool isJustRange);
  static bool isWeaponJustRange();
  static void setAwakeningRestTimeRatio(f32 ratio);
  static f32 getAwakeningRestTimeRatio();
  static void setChainAttackActionRecast(f32 recast);
  static f32 getChainAttackActionRecast();
  static void setChainAttackActionPartyID(int partyId);
  static int getChainAttackActionPartyID();
  static void setChainAttackActionCount(u32 count);
  static u32 getChainAttackActionCount();
  static void setChainAttackDamageRatio(f32 ratio);
  static f32 getChainAttackDamageRatio();
  static void setChainAttackExpRatio(f32 ratio);
  static f32 getChainAttackExpRatio();
  static void setChainAttackTotalDamage(u32 damage);
  static u32 getChainAttackTotalDamage();
  static void setChainAttackBurstCount(u32 count);
  static u32 getChainAttackBurstCount();
  static u32 getElementComboRootLevel(u32 index);
  static void setElementComboParty(u32 index, u32 id, f32 timeLeft);
  static u32 getElementComboParty(u32 index);
  static f32 getElementComboPartyTimeLeft(u32 index);
  static void setElementComboRequest(u32 request);
  static u32 getElementComboRequest();
  static void setHomuraModeInBattle(HOMURA_MODE mode);
  static HOMURA_MODE getHomuraModeInBattle();
  static bool isPaletteModeReverse();
  static bool isReversePaletteBtnState(u32 index, u32 button);
  static ui::UIListInfo<MenuEnemyInfo> *getEnemyLinkList();
  static ui::UIListInfo<MenuItemInfo> *getItemLinkList();
  static void addItemLink(const MenuItemInfo &info);
  static void setReferenceDriverID(u32 index, u32 id);
  static u32 getReferenceDriverID(u32 index);
  static void setReferenceBladeID(u32 index, u32 id);
  static u32 getReferenceBladeID(u32 index);
  static void setReferenceNumber(u32 index, int value);
  static void setReferenceNumberMin(u32 index, int min);
  static void setReferenceNumberMax(u32 index, int max);
  static int getReferenceNumber(u32 index);
  static int getReferenceNumberMin(u32 index);
  static int getReferenceNumberMax(u32 index);
  static void setReferenceTeamID(u32 id);
  static u32 getReferenceTeamID();
  static void setReferenceZoneID(u32 id);
  static u32 getReferenceZoneID();
  static void setReferenceMissionID(u32 id);
  static u32 getReferenceMissionID();
  static void setReferenceShopID(u32 id);
  static u32 getReferenceShopID();
  static void setReferenceWorldMapID(u32 id);
  static u32 getReferenceWorldMapID();
  static void setDriverVirtualLevel(u32 level);
  static u32 getDriverVirtualLevel();
  static void setDriverVirtualBladeID(u32 id);
  static u32 getDriverVirtualBladeID();
  static void setDriverVirtualBladeSlot(u32 slot);
  static u32 getDriverVirtualBladeSlot();
  static void setDriverVirtualEquipAcc(u32 id);
  static u32 getDriverVirtualEquipAcc();
  static void setDriverVirtualEquipAccSlot(u32 slot);
  static u32 getDriverVirtualEquipAccSlot();
  static void resetDriverAddIdeaLv();
  static void setDriverAddIdeaLv(u32 index, int level);
  static int getDriverAddIdeaLv(u32 index);
  static void setBladeVirtualEquipWpnChip(u32 id);
  static u32 getBladeVirtualEquipWpnChip();
  static void setBladeVirtualEquipOrb(u32 id);
  static u32 getBladeVirtualEquipOrb();
  static void setBladeVirtualEquipOrbSlot(u32 slot);
  static u32 getBladeVirtualEquipOrbSlot();
  static mm::threading::CriticalSection &getCriticalSection();
  static ui::UIStr &getReferenceString(u16 index);
  static void setReferenceString(ui::UIStr &string, u16 index);
  static void clearPartyStatusLock();

  u8 _08[0x4ca18 - 0x08];
  mm::threading::CriticalSection unknown4ca18;           // Inferred role: critical section; original member name unknown.
  bool unknown4ca40;                                     // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedVector<FieldSkillInfo, 28> unknown4ca48; // Inferred role: field skills; original member name unknown.
  ArtsPalette unknown4cac0[ARTS_PALETTE_COUNT];          // Inferred role: arts palettes; original member name unknown.
  u8 _4cb38[0x4cb3c - 0x4cb38];
  bool unknown4cb3c;   // Inferred role: just range; original member name unknown.
  f32 unknown4cb40;    // Inferred role: awakening rest time ratio; original member name unknown.
  f32 unknown4cb44;    // Inferred role: chain attack action recast; original member name unknown.
  u32 unknown4cb48;    // Inferred role: chain attack action count; original member name unknown.
  int unknown4cb4c;    // Inferred role: chain attack action party id; original member name unknown.
  f32 unknown4cb50;    // Inferred role: chain attack damage ratio; original member name unknown.
  f32 unknown4cb54;    // Inferred role: chain attack exp ratio; original member name unknown.
  u32 unknown4cb58;    // Inferred role: chain attack total damage; original member name unknown.
  u32 unknown4cb5c;    // Inferred role: chain attack burst count; original member name unknown.
  u32 unknown4cb60[2]; // Inferred role: target enemy buffs; original member name unknown.
  u8 _4cb68[0x4cb6c - 0x4cb68];
  u16 unknown4cb6c; // Inferred role: chain num; original member name unknown.
  u8 _4cb6e[0x4cb74 - 0x4cb6e];
  u32 unknown4cb74;                    // Inferred role: target enemy debuff; original member name unknown.
  u32 unknown4cb78;                    // Inferred role: target enemy weak attr; original member name unknown.
  HOMURA_MODE unknown4cb7c;            // Inferred role: homura mode; original member name unknown.
  bool unknown4cb80;                   // Inferred role: palette reverse; original member name unknown.
  mm::mtl::BitFlag<8> unknown4cb84[4]; // Inferred role: reverse palette btn states; original member name unknown.
  u8 _4cb94[0x4cb98 - 0x4cb94];
  ui::UIListInfo<MenuEnemyInfo> *unknown4cb98; // Inferred role: enemy links; original member name unknown.
  ui::UIListInfo<MenuItemInfo> *unknown4cba0;  // Inferred role: item links; original member name unknown.
  ElemComboRoot unknown4cba8[7];               // Inferred role: element combo roots; original member name unknown.
  ElementComboParty unknown4cbe0[2];           // Inferred role: element combo parties; original member name unknown.
  u32 unknown4cbf0;                            // Inferred role: element combo request; original member name unknown.
  u8 _4cbf4[0x4cbf8 - 0x4cbf4];
  u32 unknown4cbf8[8];             // Inferred role: reference driver ids; original member name unknown.
  u32 unknown4cc18[8];             // Inferred role: reference blade ids; original member name unknown.
  ReferenceNumber unknown4cc38[8]; // Inferred role: reference numbers; original member name unknown.
  u32 unknown4cc98;                // Inferred role: reference team id; original member name unknown.
  u32 unknown4cc9c;                // Inferred role: reference zone id; original member name unknown.
  u32 unknown4cca0;                // Inferred role: reference mission id; original member name unknown.
  u32 unknown4cca4;                // Inferred role: reference shop id; original member name unknown.
  u32 unknown4cca8;                // Inferred role: reference world map id; original member name unknown.
  u32 unknown4ccac;                // Inferred role: driver virtual level; original member name unknown.
  u32 unknown4ccb0;                // Inferred role: driver virtual blade id; original member name unknown.
  u32 unknown4ccb4;                // Inferred role: driver virtual blade slot; original member name unknown.
  u32 unknown4ccb8;                // Inferred role: driver virtual equip acc; original member name unknown.
  u32 unknown4ccbc;                // Inferred role: driver virtual equip acc slot; original member name unknown.
  int unknown4ccc0[4];             // Inferred role: driver add idea lvs; original member name unknown.
  u32 unknown4ccd0;                // Inferred role: blade virtual equip wpn chip; original member name unknown.
  u32 unknown4ccd4;                // Inferred role: blade virtual equip orb; original member name unknown.
  u32 unknown4ccd8;                // Inferred role: blade virtual equip orb slot; original member name unknown.
  u8 _4ccdc[0x4cce0 - 0x4ccdc];
  ui::UIStr unknown4cce0[8];                        // Inferred role: reference strings; original member name unknown.
  ArtsPalette unknown4cda0[ALL_ARTS_PALETTE_COUNT]; // Inferred role: all arts palettes; original member name unknown.
  mm::mtl::BitFlag<32> unknown4cf08;                // Inferred role: party status lock; original member name unknown.
  u8 _4cf0c[0x4cf10 - 0x4cf0c];
};

static_assert(offsetof(GfMenuReference, unknown4ca18) == 0x4ca18, "");
static_assert(offsetof(GfMenuReference, unknown4ca40) == 0x4ca40, "");
static_assert(offsetof(GfMenuReference, unknown4ca48) == 0x4ca48, "");
static_assert(offsetof(GfMenuReference, unknown4cac0) == 0x4cac0, "");
static_assert(offsetof(GfMenuReference, unknown4cb3c) == 0x4cb3c, "");
static_assert(offsetof(GfMenuReference, unknown4cb40) == 0x4cb40, "");
static_assert(offsetof(GfMenuReference, unknown4cb44) == 0x4cb44, "");
static_assert(offsetof(GfMenuReference, unknown4cb48) == 0x4cb48, "");
static_assert(offsetof(GfMenuReference, unknown4cb4c) == 0x4cb4c, "");
static_assert(offsetof(GfMenuReference, unknown4cb50) == 0x4cb50, "");
static_assert(offsetof(GfMenuReference, unknown4cb54) == 0x4cb54, "");
static_assert(offsetof(GfMenuReference, unknown4cb58) == 0x4cb58, "");
static_assert(offsetof(GfMenuReference, unknown4cb5c) == 0x4cb5c, "");
static_assert(offsetof(GfMenuReference, unknown4cb60) == 0x4cb60, "");
static_assert(offsetof(GfMenuReference, unknown4cb6c) == 0x4cb6c, "");
static_assert(offsetof(GfMenuReference, unknown4cb74) == 0x4cb74, "");
static_assert(offsetof(GfMenuReference, unknown4cb78) == 0x4cb78, "");
static_assert(offsetof(GfMenuReference, unknown4cb7c) == 0x4cb7c, "");
static_assert(offsetof(GfMenuReference, unknown4cb80) == 0x4cb80, "");
static_assert(offsetof(GfMenuReference, unknown4cb84) == 0x4cb84, "");
static_assert(offsetof(GfMenuReference, unknown4cb98) == 0x4cb98, "");
static_assert(offsetof(GfMenuReference, unknown4cba0) == 0x4cba0, "");
static_assert(offsetof(GfMenuReference, unknown4cba8) == 0x4cba8, "");
static_assert(offsetof(GfMenuReference, unknown4cbe0) == 0x4cbe0, "");
static_assert(offsetof(GfMenuReference, unknown4cbf0) == 0x4cbf0, "");
static_assert(offsetof(GfMenuReference, unknown4cbf8) == 0x4cbf8, "");
static_assert(offsetof(GfMenuReference, unknown4cc18) == 0x4cc18, "");
static_assert(offsetof(GfMenuReference, unknown4cc38) == 0x4cc38, "");
static_assert(offsetof(GfMenuReference, unknown4cc98) == 0x4cc98, "");
static_assert(offsetof(GfMenuReference, unknown4cca8) == 0x4cca8, "");
static_assert(offsetof(GfMenuReference, unknown4ccac) == 0x4ccac, "");
static_assert(offsetof(GfMenuReference, unknown4ccc0) == 0x4ccc0, "");
static_assert(offsetof(GfMenuReference, unknown4ccd0) == 0x4ccd0, "");
static_assert(offsetof(GfMenuReference, unknown4ccd8) == 0x4ccd8, "");
static_assert(offsetof(GfMenuReference, unknown4cce0) == 0x4cce0, "");
static_assert(offsetof(GfMenuReference, unknown4cf08) == 0x4cf08, "");
static_assert(sizeof(GfMenuReference) == 0x4cf10, "");

class GfMenuReferenceFs : public mm::mtl::ReferenceObject {
public:
  virtual void getFs(MenuFieldSkill &fs) const { fs = unknown0c; }

  MenuFieldSkill unknown0c; // Inferred role: field skill; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceFs, unknown0c) == 0x0c, "");

} // namespace gf

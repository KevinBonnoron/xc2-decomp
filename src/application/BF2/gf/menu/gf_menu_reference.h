#pragma once
#include <stddef.h>

#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_vector.h"
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
  enum HOMURA_MODE {};

  struct FieldSkillInfo {
    u32 id;
  };

  struct ElemComboRoot {
    ElemComboRoot() : id(0), flags() {}

    u32 id;
    mm::mtl::BitFlag<32> flags;
  };

  struct ElementComboParty {
    u32 id;
    f32 timeLeft;
  };

  struct ReferenceNumber {
    int min;
    int max;
    int value;
  };

  static bool isInitialized();
  static void initReferenceNumber(u32 index);
  static void resetDriverVirtual();
  static void postReset();
  static u32 getFieldSkillMax();
  static void getFieldSkillInfo(u8 index, FieldSkillInfo &info);
  static u32 getTargetEnemyBuff(u32 index);
  static u32 getTargetEnemyWeakAttr();
  static void setChainNum(u32 chainNum);
  static u16 getChainNum();
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
  mm::threading::CriticalSection criticalSection;
  bool initialized;
  mm::mtl::FixedVector<FieldSkillInfo, 28> fieldSkills;
  u8 _4cac0[0x4cb3c - 0x4cac0];
  bool isJustRange;
  f32 awakeningRestTimeRatio;
  f32 chainAttackActionRecast;
  u32 chainAttackActionCount;
  int chainAttackActionPartyId;
  f32 chainAttackDamageRatio;
  f32 chainAttackExpRatio;
  u32 chainAttackTotalDamage;
  u32 chainAttackBurstCount;
  u32 targetEnemyBuffs[2];
  u8 _4cb68[0x4cb6c - 0x4cb68];
  u16 chainNum;
  u8 _4cb6e[0x4cb74 - 0x4cb6e];
  u32 targetEnemyDebuff;
  u32 targetEnemyWeakAttr;
  HOMURA_MODE homuraMode;
  bool isPaletteReverse;
  mm::mtl::BitFlag<8> reversePaletteBtnStates[4];
  u8 _4cb94[0x4cb98 - 0x4cb94];
  ui::UIListInfo<MenuEnemyInfo> *enemyLinks;
  ui::UIListInfo<MenuItemInfo> *itemLinks;
  ElemComboRoot elementComboRoots[7];
  ElementComboParty elementComboParties[2];
  u32 elementComboRequest;
  u8 _4cbf4[0x4cbf8 - 0x4cbf4];
  u32 referenceDriverIds[8];
  u32 referenceBladeIds[8];
  ReferenceNumber referenceNumbers[8];
  u32 referenceTeamId;
  u32 referenceZoneId;
  u32 referenceMissionId;
  u32 referenceShopId;
  u32 referenceWorldMapId;
  u32 driverVirtualLevel;
  u32 driverVirtualBladeId;
  u32 driverVirtualBladeSlot;
  u32 driverVirtualEquipAcc;
  u32 driverVirtualEquipAccSlot;
  int driverAddIdeaLvs[4];
  u32 bladeVirtualEquipWpnChip;
  u32 bladeVirtualEquipOrb;
  u32 bladeVirtualEquipOrbSlot;
  u8 _4ccdc[0x4cce0 - 0x4ccdc];
  ui::UIStr referenceStrings[8];
  u8 _4cda0[0x4cf08 - 0x4cda0];
  mm::mtl::BitFlag<32> partyStatusLock;
  u8 _4cf0c[0x4cf10 - 0x4cf0c];
};

static_assert(offsetof(GfMenuReference, criticalSection) == 0x4ca18, "");
static_assert(offsetof(GfMenuReference, initialized) == 0x4ca40, "");
static_assert(offsetof(GfMenuReference, fieldSkills) == 0x4ca48, "");
static_assert(offsetof(GfMenuReference, isJustRange) == 0x4cb3c, "");
static_assert(offsetof(GfMenuReference, awakeningRestTimeRatio) == 0x4cb40, "");
static_assert(offsetof(GfMenuReference, chainAttackActionRecast) == 0x4cb44, "");
static_assert(offsetof(GfMenuReference, chainAttackActionCount) == 0x4cb48, "");
static_assert(offsetof(GfMenuReference, chainAttackActionPartyId) == 0x4cb4c, "");
static_assert(offsetof(GfMenuReference, chainAttackDamageRatio) == 0x4cb50, "");
static_assert(offsetof(GfMenuReference, chainAttackExpRatio) == 0x4cb54, "");
static_assert(offsetof(GfMenuReference, chainAttackTotalDamage) == 0x4cb58, "");
static_assert(offsetof(GfMenuReference, chainAttackBurstCount) == 0x4cb5c, "");
static_assert(offsetof(GfMenuReference, targetEnemyBuffs) == 0x4cb60, "");
static_assert(offsetof(GfMenuReference, chainNum) == 0x4cb6c, "");
static_assert(offsetof(GfMenuReference, targetEnemyDebuff) == 0x4cb74, "");
static_assert(offsetof(GfMenuReference, targetEnemyWeakAttr) == 0x4cb78, "");
static_assert(offsetof(GfMenuReference, homuraMode) == 0x4cb7c, "");
static_assert(offsetof(GfMenuReference, isPaletteReverse) == 0x4cb80, "");
static_assert(offsetof(GfMenuReference, reversePaletteBtnStates) == 0x4cb84, "");
static_assert(offsetof(GfMenuReference, enemyLinks) == 0x4cb98, "");
static_assert(offsetof(GfMenuReference, itemLinks) == 0x4cba0, "");
static_assert(offsetof(GfMenuReference, elementComboRoots) == 0x4cba8, "");
static_assert(offsetof(GfMenuReference, elementComboParties) == 0x4cbe0, "");
static_assert(offsetof(GfMenuReference, elementComboRequest) == 0x4cbf0, "");
static_assert(offsetof(GfMenuReference, referenceDriverIds) == 0x4cbf8, "");
static_assert(offsetof(GfMenuReference, referenceBladeIds) == 0x4cc18, "");
static_assert(offsetof(GfMenuReference, referenceNumbers) == 0x4cc38, "");
static_assert(offsetof(GfMenuReference, referenceTeamId) == 0x4cc98, "");
static_assert(offsetof(GfMenuReference, referenceWorldMapId) == 0x4cca8, "");
static_assert(offsetof(GfMenuReference, driverVirtualLevel) == 0x4ccac, "");
static_assert(offsetof(GfMenuReference, driverAddIdeaLvs) == 0x4ccc0, "");
static_assert(offsetof(GfMenuReference, bladeVirtualEquipWpnChip) == 0x4ccd0, "");
static_assert(offsetof(GfMenuReference, bladeVirtualEquipOrbSlot) == 0x4ccd8, "");
static_assert(offsetof(GfMenuReference, referenceStrings) == 0x4cce0, "");
static_assert(offsetof(GfMenuReference, partyStatusLock) == 0x4cf08, "");
static_assert(sizeof(GfMenuReference) == 0x4cf10, "");

} // namespace gf

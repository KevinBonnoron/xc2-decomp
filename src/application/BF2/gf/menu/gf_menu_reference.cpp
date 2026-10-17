#include "gf/menu/gf_menu_reference.h"

#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "ui/list/ui_list_info.h"

namespace gf {

bool GfMenuReference::isInitialized() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->initialized;
  }
  return false;
}

void GfMenuReference::initReferenceNumber(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    ReferenceNumber &number = reference->referenceNumbers[index];
    number.value = 0;
    number.min = 0;
    number.max = 9999;
  }
}

void GfMenuReference::resetDriverVirtual() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->driverVirtualLevel = 0;
    reference->driverVirtualBladeId = 0;
    reference->driverVirtualBladeSlot = 0;
    reference->driverVirtualEquipAcc = 0;
    reference->driverVirtualEquipAccSlot = 0;
    for (int i = 0; i < 4; i++) {
      reference->driverAddIdeaLvs[i] = 0;
    }
  }
}

void GfMenuReference::postReset() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    for (int i = 0; i < 4; i++) {
      reference->reversePaletteBtnStates[i].set(2, false);
    }
  }
}

u32 GfMenuReference::getFieldSkillMax() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->fieldSkills.size();
  }
  return 0;
}

void GfMenuReference::getFieldSkillInfo(u8 index, FieldSkillInfo &info) {
  GfMenuReference *reference = get();
  if (reference != nullptr && index < reference->fieldSkills.size()) {
    info = reference->fieldSkills.begin()[index];
  }
}

u32 GfMenuReference::getTargetEnemyBuff(u32 index) {
  GfMenuReference *reference = get();
  if (index < 3 && reference != nullptr) {
    if (index == 2) {
      return reference->targetEnemyDebuff;
    }
    return reference->targetEnemyBuffs[index];
  }
  return 0;
}

u32 GfMenuReference::getTargetEnemyWeakAttr() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->targetEnemyWeakAttr;
  }
  return 0;
}

void GfMenuReference::setChainNum(u32 chainNum) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainNum = chainNum;
  }
}

u32 GfMenuReference::getChainNum() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainNum;
  }
  return 0;
}

void GfMenuReference::setWeaponJustRange(bool isJustRange) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->isJustRange = isJustRange;
  }
}

bool GfMenuReference::isWeaponJustRange() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->isJustRange;
  }
  return false;
}

void GfMenuReference::setAwakeningRestTimeRatio(f32 ratio) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->awakeningRestTimeRatio = ratio;
  }
}

f32 GfMenuReference::getAwakeningRestTimeRatio() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->awakeningRestTimeRatio;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackActionRecast(f32 recast) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackActionRecast = recast;
  }
}

f32 GfMenuReference::getChainAttackActionRecast() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackActionRecast;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackActionPartyID(int partyId) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackActionPartyId = partyId;
  }
}

int GfMenuReference::getChainAttackActionPartyID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackActionPartyId;
  }
  return -1;
}

void GfMenuReference::setChainAttackActionCount(u32 count) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackActionCount = count;
  }
}

u32 GfMenuReference::getChainAttackActionCount() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackActionCount;
  }
  return 0;
}

void GfMenuReference::setChainAttackDamageRatio(f32 ratio) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackDamageRatio = ratio;
  }
}

f32 GfMenuReference::getChainAttackDamageRatio() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackDamageRatio;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackExpRatio(f32 ratio) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackExpRatio = ratio;
  }
}

f32 GfMenuReference::getChainAttackExpRatio() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackExpRatio;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackTotalDamage(u32 damage) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackTotalDamage = damage;
  }
}

u32 GfMenuReference::getChainAttackTotalDamage() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackTotalDamage;
  }
  return 0;
}

void GfMenuReference::setChainAttackBurstCount(u32 count) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->chainAttackBurstCount = count;
  }
}

u32 GfMenuReference::getChainAttackBurstCount() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->chainAttackBurstCount;
  }
  return 0;
}

u32 GfMenuReference::getElementComboRootLevel(u32 index) {
  static const u32 levels[7] = {1, 2, 2, 3, 3, 3, 3};
  if (index < 7) {
    return levels[index];
  }
  return 0;
}

void GfMenuReference::setElementComboParty(u32 index, u32 id, f32 timeLeft) {
  GfMenuReference *reference = get();
  if (index < 2 && reference != nullptr) {
    reference->elementComboParties[index].id = id;
    reference->elementComboParties[index].timeLeft = timeLeft;
  }
}

u32 GfMenuReference::getElementComboParty(u32 index) {
  GfMenuReference *reference = get();
  if (index < 2 && reference != nullptr) {
    return reference->elementComboParties[index].id;
  }
  return 0;
}

f32 GfMenuReference::getElementComboPartyTimeLeft(u32 index) {
  GfMenuReference *reference = get();
  if (index < 2 && reference != nullptr) {
    return reference->elementComboParties[index].timeLeft;
  }
  return 0.0f;
}

void GfMenuReference::setElementComboRequest(u32 request) {
  GfMenuReference *reference = get();
  if (request < 4 && reference != nullptr) {
    reference->elementComboRequest = request;
  }
}

u32 GfMenuReference::getElementComboRequest() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->elementComboRequest;
  }
  return 0;
}

void GfMenuReference::setHomuraModeInBattle(HOMURA_MODE mode) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->homuraMode = mode;
  }
}

GfMenuReference::HOMURA_MODE GfMenuReference::getHomuraModeInBattle() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->homuraMode;
  }
  return static_cast<HOMURA_MODE>(0);
}

bool GfMenuReference::isPaletteModeReverse() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->isPaletteReverse;
  }
  return false;
}

bool GfMenuReference::isReversePaletteBtnState(u32 index, u32 button) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    return reference->reversePaletteBtnStates[index].test(button);
  }
  return false;
}

ui::UIListInfo<MenuEnemyInfo> *GfMenuReference::getEnemyLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->enemyLinks;
  }
  return nullptr;
}

ui::UIListInfo<MenuItemInfo> *GfMenuReference::getItemLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->itemLinks;
  }
  return nullptr;
}

void GfMenuReference::setReferenceDriverID(u32 index, u32 id) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->referenceDriverIds[index] = id;
  }
}

u32 GfMenuReference::getReferenceDriverID(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->referenceDriverIds[index];
  }
  return 0;
}

void GfMenuReference::setReferenceBladeID(u32 index, u32 id) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->referenceBladeIds[index] = id;
  }
}

u32 GfMenuReference::getReferenceBladeID(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->referenceBladeIds[index];
  }
  return 0;
}

void GfMenuReference::setReferenceNumber(u32 index, int value) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->referenceNumbers[index].value = value;
  }
}

void GfMenuReference::setReferenceNumberMin(u32 index, int min) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->referenceNumbers[index].min = min;
  }
}

void GfMenuReference::setReferenceNumberMax(u32 index, int max) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->referenceNumbers[index].max = max;
  }
}

int GfMenuReference::getReferenceNumber(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->referenceNumbers[index].value;
  }
  return 0;
}

int GfMenuReference::getReferenceNumberMin(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->referenceNumbers[index].min;
  }
  return 0;
}

int GfMenuReference::getReferenceNumberMax(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->referenceNumbers[index].max;
  }
  return 0;
}

void GfMenuReference::setReferenceTeamID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->referenceTeamId = id > 3 ? 3 : id;
  }
}

u32 GfMenuReference::getReferenceTeamID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->referenceTeamId;
  }
  return 0;
}

void GfMenuReference::setReferenceZoneID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->referenceZoneId = id == 0 ? 1 : (id > 8 ? 8 : id);
  }
}

u32 GfMenuReference::getReferenceZoneID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->referenceZoneId;
  }
  return 0;
}

void GfMenuReference::setReferenceMissionID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->referenceMissionId = id == 0 ? 1 : (id > 500 ? 500 : id);
  }
}

u32 GfMenuReference::getReferenceMissionID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->referenceMissionId;
  }
  return 0;
}

void GfMenuReference::setReferenceShopID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->referenceShopId = id;
  }
}

u32 GfMenuReference::getReferenceShopID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->referenceShopId;
  }
  return 0;
}

void GfMenuReference::setReferenceWorldMapID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->referenceWorldMapId = id == 0 ? 1 : (id > 51 ? 51 : id);
  }
}

u32 GfMenuReference::getReferenceWorldMapID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->referenceWorldMapId;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualLevel(u32 level) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->driverVirtualLevel = level;
  }
}

u32 GfMenuReference::getDriverVirtualLevel() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->driverVirtualLevel;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualBladeID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->driverVirtualBladeId = id;
  }
}

u32 GfMenuReference::getDriverVirtualBladeID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->driverVirtualBladeId;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualBladeSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->driverVirtualBladeSlot = slot;
  }
}

u32 GfMenuReference::getDriverVirtualBladeSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->driverVirtualBladeSlot;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualEquipAcc(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->driverVirtualEquipAcc = id;
  }
}

u32 GfMenuReference::getDriverVirtualEquipAcc() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->driverVirtualEquipAcc;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualEquipAccSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->driverVirtualEquipAccSlot = slot;
  }
}

u32 GfMenuReference::getDriverVirtualEquipAccSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->driverVirtualEquipAccSlot;
  }
  return 0;
}

void GfMenuReference::resetDriverAddIdeaLv() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    for (int i = 0; i < 4; i++) {
      reference->driverAddIdeaLvs[i] = 0;
    }
  }
}

void GfMenuReference::setDriverAddIdeaLv(u32 index, int level) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    reference->driverAddIdeaLvs[index] = level;
  }
}

int GfMenuReference::getDriverAddIdeaLv(u32 index) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    return reference->driverAddIdeaLvs[index];
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipWpnChip(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->bladeVirtualEquipWpnChip = id;
  }
}

u32 GfMenuReference::getBladeVirtualEquipWpnChip() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->bladeVirtualEquipWpnChip;
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipOrb(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->bladeVirtualEquipOrb = id;
  }
}

u32 GfMenuReference::getBladeVirtualEquipOrb() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->bladeVirtualEquipOrb;
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipOrbSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->bladeVirtualEquipOrbSlot = slot;
  }
}

u32 GfMenuReference::getBladeVirtualEquipOrbSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->bladeVirtualEquipOrbSlot;
  }
  return 0;
}

mm::threading::CriticalSection &GfMenuReference::getCriticalSection() { return get()->criticalSection; }

ui::UIStr &GfMenuReference::getReferenceString(u16 index) {
  GfMenuReference *reference = get();
  return reference->referenceStrings[index];
}

void GfMenuReference::setReferenceString(ui::UIStr &string, u16 index) { get()->referenceStrings[index].copy(string); }

void GfMenuReference::clearPartyStatusLock() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->partyStatusLock.clear();
  }
  GfMenuObjPartyStatus::lock(false);
}

} // namespace gf

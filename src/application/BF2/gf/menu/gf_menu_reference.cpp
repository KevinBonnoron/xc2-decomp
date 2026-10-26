#include "gf/menu/gf_menu_reference.h"

#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "ui/list/ui_list_info.h"

namespace gf {

bool GfMenuReference::isInitialized() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ca40;
  }
  return false;
}

void GfMenuReference::initReferenceNumber(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    ReferenceNumber &number = reference->unknown4cc38[index];
    number.unknown08 = 0;
    number.unknown00 = 0;
    number.unknown04 = 9999;
  }
}

void GfMenuReference::resetDriverVirtual() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccac = 0;
    reference->unknown4ccb0 = 0;
    reference->unknown4ccb4 = 0;
    reference->unknown4ccb8 = 0;
    reference->unknown4ccbc = 0;
    for (int i = 0; i < 4; i++) {
      reference->unknown4ccc0[i] = 0;
    }
  }
}

void GfMenuReference::postReset() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    for (int i = 0; i < 4; i++) {
      reference->unknown4cb84[i].set(2, false);
    }
  }
}

u32 GfMenuReference::getFieldSkillMax() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ca48.size();
  }
  return 0;
}

void GfMenuReference::getFieldSkillInfo(u8 index, FieldSkillInfo &info) {
  GfMenuReference *reference = get();
  if (reference != nullptr && index < reference->unknown4ca48.size()) {
    info = reference->unknown4ca48.begin()[index];
  }
}

u32 GfMenuReference::getTargetEnemyBuff(u32 index) {
  GfMenuReference *reference = get();
  if (index < 3 && reference != nullptr) {
    if (index == 2) {
      return reference->unknown4cb74;
    }
    return reference->unknown4cb60[index];
  }
  return 0;
}

u32 GfMenuReference::getTargetEnemyWeakAttr() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb78;
  }
  return 0;
}

void GfMenuReference::setChainNum(u32 chainNum) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb6c = chainNum;
  }
}

u32 GfMenuReference::getChainNum() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb6c;
  }
  return 0;
}

void GfMenuReference::setWeaponJustRange(bool isJustRange) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb3c = isJustRange;
  }
}

bool GfMenuReference::isWeaponJustRange() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb3c;
  }
  return false;
}

void GfMenuReference::setAwakeningRestTimeRatio(f32 ratio) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb40 = ratio;
  }
}

f32 GfMenuReference::getAwakeningRestTimeRatio() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb40;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackActionRecast(f32 recast) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb44 = recast;
  }
}

f32 GfMenuReference::getChainAttackActionRecast() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb44;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackActionPartyID(int partyId) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb4c = partyId;
  }
}

int GfMenuReference::getChainAttackActionPartyID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb4c;
  }
  return -1;
}

void GfMenuReference::setChainAttackActionCount(u32 count) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb48 = count;
  }
}

u32 GfMenuReference::getChainAttackActionCount() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb48;
  }
  return 0;
}

void GfMenuReference::setChainAttackDamageRatio(f32 ratio) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb50 = ratio;
  }
}

f32 GfMenuReference::getChainAttackDamageRatio() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb50;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackExpRatio(f32 ratio) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb54 = ratio;
  }
}

f32 GfMenuReference::getChainAttackExpRatio() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb54;
  }
  return 0.0f;
}

void GfMenuReference::setChainAttackTotalDamage(u32 damage) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb58 = damage;
  }
}

u32 GfMenuReference::getChainAttackTotalDamage() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb58;
  }
  return 0;
}

void GfMenuReference::setChainAttackBurstCount(u32 count) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb5c = count;
  }
}

u32 GfMenuReference::getChainAttackBurstCount() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb5c;
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
    reference->unknown4cbe0[index].unknown00 = id;
    reference->unknown4cbe0[index].unknown04 = timeLeft;
  }
}

u32 GfMenuReference::getElementComboParty(u32 index) {
  GfMenuReference *reference = get();
  if (index < 2 && reference != nullptr) {
    return reference->unknown4cbe0[index].unknown00;
  }
  return 0;
}

f32 GfMenuReference::getElementComboPartyTimeLeft(u32 index) {
  GfMenuReference *reference = get();
  if (index < 2 && reference != nullptr) {
    return reference->unknown4cbe0[index].unknown04;
  }
  return 0.0f;
}

void GfMenuReference::setElementComboRequest(u32 request) {
  GfMenuReference *reference = get();
  if (request < 4 && reference != nullptr) {
    reference->unknown4cbf0 = request;
  }
}

u32 GfMenuReference::getElementComboRequest() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cbf0;
  }
  return 0;
}

void GfMenuReference::setHomuraModeInBattle(HOMURA_MODE mode) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cb7c = mode;
  }
}

GfMenuReference::HOMURA_MODE GfMenuReference::getHomuraModeInBattle() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb7c;
  }
  return static_cast<HOMURA_MODE>(0);
}

bool GfMenuReference::isPaletteModeReverse() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb80;
  }
  return false;
}

bool GfMenuReference::isReversePaletteBtnState(u32 index, u32 button) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    return reference->unknown4cb84[index].test(button);
  }
  return false;
}

ui::UIListInfo<MenuEnemyInfo> *GfMenuReference::getEnemyLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb98;
  }
  return nullptr;
}

ui::UIListInfo<MenuItemInfo> *GfMenuReference::getItemLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cba0;
  }
  return nullptr;
}

void GfMenuReference::addItemLink(const MenuItemInfo &info) {
  ui::UIListInfo<MenuItemInfo> *list = getItemLinkList();
  if (list != nullptr) {
    list->addContents(info);
  }
}

void GfMenuReference::setReferenceDriverID(u32 index, u32 id) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->unknown4cbf8[index] = id;
  }
}

u32 GfMenuReference::getReferenceDriverID(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->unknown4cbf8[index];
  }
  return 0;
}

void GfMenuReference::setReferenceBladeID(u32 index, u32 id) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->unknown4cc18[index] = id;
  }
}

u32 GfMenuReference::getReferenceBladeID(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->unknown4cc18[index];
  }
  return 0;
}

void GfMenuReference::setReferenceNumber(u32 index, int value) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->unknown4cc38[index].unknown08 = value;
  }
}

void GfMenuReference::setReferenceNumberMin(u32 index, int min) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->unknown4cc38[index].unknown00 = min;
  }
}

void GfMenuReference::setReferenceNumberMax(u32 index, int max) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    reference->unknown4cc38[index].unknown04 = max;
  }
}

int GfMenuReference::getReferenceNumber(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->unknown4cc38[index].unknown08;
  }
  return 0;
}

int GfMenuReference::getReferenceNumberMin(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->unknown4cc38[index].unknown00;
  }
  return 0;
}

int GfMenuReference::getReferenceNumberMax(u32 index) {
  GfMenuReference *reference = get();
  if (index < 8 && reference != nullptr) {
    return reference->unknown4cc38[index].unknown04;
  }
  return 0;
}

void GfMenuReference::setReferenceTeamID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cc98 = id > 3 ? 3 : id;
  }
}

u32 GfMenuReference::getReferenceTeamID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cc98;
  }
  return 0;
}

void GfMenuReference::setReferenceZoneID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cc9c = id == 0 ? 1 : (id > 8 ? 8 : id);
  }
}

u32 GfMenuReference::getReferenceZoneID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cc9c;
  }
  return 0;
}

void GfMenuReference::setReferenceMissionID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cca0 = id == 0 ? 1 : (id > 500 ? 500 : id);
  }
}

u32 GfMenuReference::getReferenceMissionID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cca0;
  }
  return 0;
}

void GfMenuReference::setReferenceShopID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cca4 = id;
  }
}

u32 GfMenuReference::getReferenceShopID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cca4;
  }
  return 0;
}

void GfMenuReference::setReferenceWorldMapID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cca8 = id == 0 ? 1 : (id > 51 ? 51 : id);
  }
}

u32 GfMenuReference::getReferenceWorldMapID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cca8;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualLevel(u32 level) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccac = level;
  }
}

u32 GfMenuReference::getDriverVirtualLevel() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccac;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualBladeID(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccb0 = id;
  }
}

u32 GfMenuReference::getDriverVirtualBladeID() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccb0;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualBladeSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccb4 = slot;
  }
}

u32 GfMenuReference::getDriverVirtualBladeSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccb4;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualEquipAcc(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccb8 = id;
  }
}

u32 GfMenuReference::getDriverVirtualEquipAcc() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccb8;
  }
  return 0;
}

void GfMenuReference::setDriverVirtualEquipAccSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccbc = slot;
  }
}

u32 GfMenuReference::getDriverVirtualEquipAccSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccbc;
  }
  return 0;
}

void GfMenuReference::resetDriverAddIdeaLv() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    for (int i = 0; i < 4; i++) {
      reference->unknown4ccc0[i] = 0;
    }
  }
}

void GfMenuReference::setDriverAddIdeaLv(u32 index, int level) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    reference->unknown4ccc0[index] = level;
  }
}

int GfMenuReference::getDriverAddIdeaLv(u32 index) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    return reference->unknown4ccc0[index];
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipWpnChip(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccd0 = id;
  }
}

u32 GfMenuReference::getBladeVirtualEquipWpnChip() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccd0;
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipOrb(u32 id) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccd4 = id;
  }
}

u32 GfMenuReference::getBladeVirtualEquipOrb() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccd4;
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipOrbSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccd8 = slot;
  }
}

u32 GfMenuReference::getBladeVirtualEquipOrbSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccd8;
  }
  return 0;
}

mm::threading::CriticalSection &GfMenuReference::getCriticalSection() { return get()->unknown4ca18; }

ui::UIStr &GfMenuReference::getReferenceString(u16 index) {
  GfMenuReference *reference = get();
  return reference->unknown4cce0[index];
}

void GfMenuReference::setReferenceString(ui::UIStr &string, u16 index) { get()->unknown4cce0[index].copy(string); }

void GfMenuReference::clearPartyStatusLock() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4cf08.clear();
  }
  GfMenuObjPartyStatus::lock(false);
}

} // namespace gf

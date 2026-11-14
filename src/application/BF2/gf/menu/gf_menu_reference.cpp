#include "gf/menu/gf_menu_reference.h"

#include <new>

#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_search_obj.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference_number.h" // IWYU pragma: keep
#include "gf/menu/list/gf_menu_enemy_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "gf/menu/object/gf_menu_obj_arts_palette.h"
#include "gf/menu/object/gf_menu_obj_party_status.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/fixed_array.h"   // IWYU pragma: keep
#include "mm_mtl/intrusive_ptr.h" // IWYU pragma: keep
#include "ui/list/ui_list_info.h"

namespace gf {
struct GF_OBJ_HANDLE;

GfMenuReference::~GfMenuReference() {}

void GfMenuReference::build(const GfSetupParam &param) {
// __LINE__ must be 67 as in the original file: its value changes the instruction order.
#line 67
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMenuReference(param);
}

void GfMenuReference::destroy() {
  GfMenuReference *reference = get();
  reference->finalize();
  delete reference;
}

void GfMenuReference::finalize() {
  mm::mtl::safeRelease(unknown4cb98);
  mm::mtl::safeRelease(unknown4cba0);
  while (unknown4c598.size() != 0) {
    GfSleep(1);
  }
  unknown4ca40 = false;
}

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
    unknown004 &number = reference->unknown4cc38[index];
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

void GfMenuReference::resetBladeVirtual() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccd0 = 0;
    reference->unknown4ccd4 = unknown006();
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

const GfMenuReference::ArtsPaletteInfo &GfMenuReference::getArtsPaletteInfo(u8 index) {
  static ArtsPaletteInfo empty;
  GfMenuReference *reference = get();
  const ArtsPaletteInfo *info = &empty;
  if (reference != nullptr) {
    if (index < ARTS_PALETTE_UNKNOWN_3) {
      info = &reference->unknown4cac0[index].unknown00;
    } else {
      info = &reference->unknown4cda0[index].unknown00;
      if (!(index < ALL_ARTS_PALETTE_UNKNOWN_9)) {
        info = &empty;
      }
    }
  }
  return *info;
}

const GfMenuObjUtil::ArtsIconInfo &GfMenuReference::getArtsPaletteIconInfo(u8 index) {
  static GfMenuObjUtil::ArtsIconInfo empty;
  GfMenuReference *reference = get();
  if (reference == nullptr) {
    return empty;
  }
  if (index < ARTS_PALETTE_UNKNOWN_3) {
    return reference->unknown4cac0[index].unknown08;
  }
  const GfMenuObjUtil::ArtsIconInfo *info = &reference->unknown4cda0[index].unknown08;
  if (!(index < ALL_ARTS_PALETTE_UNKNOWN_9)) {
    info = &empty;
  }
  return *info;
}

void GfMenuReference::setArtsPaletteEnable(u8 index, bool isEnable, u32 disableFlags) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    if (index < ARTS_PALETTE_UNKNOWN_3) {
      reference->unknown4cac0[index].unknown20 = isEnable;
      reference->unknown4cac0[index].unknown24 = disableFlags;
    }
    if (index < ALL_ARTS_PALETTE_UNKNOWN_9) {
      reference->unknown4cda0[index].unknown20 = isEnable;
      reference->unknown4cda0[index].unknown24 = disableFlags;
    }
  }
}

u32 GfMenuReference::getArtsPaletteElementType(u8 index) {
  GfMenuReference *reference = get();
  if (reference == nullptr) {
    return 0;
  }
  if (index < ARTS_PALETTE_UNKNOWN_3) {
    return reference->unknown4cac0[index].unknown1c;
  }
  if (index < ALL_ARTS_PALETTE_UNKNOWN_9) {
    return reference->unknown4cda0[index].unknown1c;
  }
  return 0;
}

bool GfMenuReference::isArtsPaletteEnable(u8 index) {
  GfMenuReference *reference = get();
  if (reference == nullptr) {
    return false;
  }
  if (index < ARTS_PALETTE_UNKNOWN_3) {
    return reference->unknown4cac0[index].unknown20;
  }
  if (index < ALL_ARTS_PALETTE_UNKNOWN_9) {
    return reference->unknown4cda0[index].unknown20;
  }
  return false;
}

u32 GfMenuReference::getArtsPaletteDisable(u8 index) {
  GfMenuReference *reference = get();
  if (reference == nullptr) {
    return 0;
  }
  if (index < ARTS_PALETTE_UNKNOWN_3) {
    return reference->unknown4cac0[index].unknown24;
  }
  if (index < ALL_ARTS_PALETTE_UNKNOWN_9) {
    return reference->unknown4cda0[index].unknown24;
  }
  return 0;
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

const GfMenuReference::ElemComboRoot &GfMenuReference::getElementComboRootInfo(u32 index) {
  static ElemComboRoot empty;
  GfMenuReference *reference = get();
  if (index < 7 && reference != nullptr) {
    return reference->unknown4cba8[index];
  }
  return empty;
}

void GfMenuReference::setElemComboRootInfo(u32 index, const ElemComboRoot &root) {
  GfMenuReference *reference = get();
  if (index < 7 && reference != nullptr) {
    reference->unknown4cba8[index] = root;
  }
}

u32 GfMenuReference::getElementComboRootCurrent() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    GF_OBJ_HANDLE *handle = GfMenuManager::getTargetObjHandle();
    if (handle != unknown020 && GfObjAcc(handle).getType() == OBJECT_TYPE_ENEMY) {
      GfObjProperty *property = GfObjUtil::getProperty(handle);
      if (property != nullptr) {
        GfObjPropertyEnemy *enemy = property->getEnemy();
        if (enemy != nullptr && enemy->unknowndc != 0) {
          for (u32 i = 0; i < 7; i++) {
            if (reference->unknown4cba8[i].unknown00 == enemy->unknowndc) {
              return i;
            }
          }
        }
      }
    }
  }
  return 7;
}

u32 GfMenuReference::getActiveElementComboID(u32 level) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    GfObjAcc acc(GfMenuManager::getTargetObjHandle());
    if (acc.isValid() && acc.getType() == OBJECT_TYPE_ENEMY) {
      GfObjProperty *property = GfObjUtil::getProperty(acc.getHandle());
      if (property == nullptr) {
        return 0;
      }
      GfObjPropertyEnemy *enemy = property->getEnemy();
      if (enemy == nullptr) {
        return 0;
      }
      if (level <= enemy->unknowne8) {
        u32 root = 0;
        if (level != 1) {
          root = 1;
          if (level != 2) {
            root = 3;
            if (level != 3) {
              return 0;
            }
          }
        }
        return getElementComboRootInfo(root).unknown00;
      }
    }
  }
  return 0;
}

u32 GfMenuReference::getElementComboRootLevel(u32 index) {
  // Inferred role: root level of each element combo route; original name unknown.
  static const u32 unknown028[7] = {1, 2, 2, 3, 3, 3, 3};
  if (index < 7) {
    return unknown028[index];
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

void GfMenuReference::setPaletteModeReverse(bool isReverse) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    if (reference->unknown4cb80 != isReverse) {
      GfMenuObjArtsPalette::reverse(isReverse);
    }
    reference->unknown4cb80 = isReverse;
  }
}

bool GfMenuReference::isReversePaletteBtnState(u32 index, u32 button) {
  GfMenuReference *reference = get();
  if (index < 4 && reference != nullptr) {
    return reference->unknown4cb84[index].test(button);
  }
  return false;
}

GfMenuEnemyList *GfMenuReference::getEnemyLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cb98;
  }
  return nullptr;
}

GfMenuItemList *GfMenuReference::getItemLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4cba0;
  }
  return nullptr;
}

void GfMenuReference::addEnemyLink(u32 enemy) {
  ui::UIListInfo<MenuEnemyInfo> *list = getEnemyLinkList();
  if (list != nullptr) {
    MenuEnemyInfo info;
    info.unknown00 = enemy;
    list->addContents(info);
  }
}

void GfMenuReference::addItemLink(const MenuItemInfo &info) {
  ui::UIListInfo<MenuItemInfo> *list = getItemLinkList();
  if (list != nullptr) {
    list->addContents(info);
  }
}

void GfMenuReference::clearLinkList() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    if (reference->unknown4cb98 != nullptr) {
      reference->unknown4cb98->clear();
    }
    if (reference->unknown4cba0 != nullptr) {
      reference->unknown4cba0->clear();
    }
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

void GfMenuReference::setReferenceBladeIDFromDriver(u32 driver) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
    if (acc.isValid()) {
      reference->unknown4cc18[0] = acc.getBlade(0, false);
      reference->unknown4cc18[1] = acc.getBlade(1, false);
      reference->unknown4cc18[2] = acc.getBlade(2, false);
    }
  }
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
    reference->unknown4ccd4.unknown00 = id;
  }
}

u32 GfMenuReference::getBladeVirtualEquipOrb() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccd4.unknown00;
  }
  return 0;
}

void GfMenuReference::setBladeVirtualEquipOrbSlot(u32 slot) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4ccd4.unknown04 = slot;
  }
}

u32 GfMenuReference::getBladeVirtualEquipOrbSlot() {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->unknown4ccd4.unknown04;
  }
  return 0;
}

GF_SEARCH_OBJ *GfMenuReference::createList(GF_SEARCH_OBJ *searchObj) {
  if (searchObj != unknown012) {
    REFLIST *list = new (unknown4070.unknown003()) REFLIST;
    list->unknown00 = searchObj;
    list->unknown08.clear();
    unknown4c598.push_back(list);
  }
  return searchObj;
}

GF_SEARCH_OBJ *GfMenuReference::createReference(const GfSearchParam &param) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    return reference->createList(GfGameSearchObj::createObj(param));
  }
  return nullptr;
}

void GfMenuReference::destroyReference(GF_SEARCH_OBJ *searchObj) {
  GfMenuReference *reference = get();
  if (reference != nullptr) {
    reference->unknown4c7d8.push_back(searchObj);
  }
}

mm::mtl::FixedList<MENUREF_OBJ *, 512> *GfMenuReference::getList(GF_SEARCH_OBJ *searchObj) {
  GfMenuReference *reference = get();
  if (reference == nullptr) {
    return nullptr;
  }
  ml::CS cs(reference->unknown4ca18);
  for (mm::mtl::FixedList<REFLIST *, 32>::iterator it = reference->unknown4c598.begin(); it != reference->unknown4c598.end(); ++it) {
    if ((*it)->unknown00 == searchObj) {
      return &(*it)->unknown08;
    }
  }
  return nullptr;
}

ml::CriticalSection &GfMenuReference::getCriticalSection() { return get()->unknown4ca18; }

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

int GfMenuReference::getBladeSetIDFromParty(u32 partyId, u32 slot) {
  DataParamAcc acc(GfGameParty::getHandleDriver(partyId));
  int result = -1;
  if (acc.isValid()) {
    u32 slotMax = GfMenuObjUtil::getBladeSlotMax();
    if (slot < slotMax) {
      int setId = acc.getBladeSet(false);
      if (GfMenuManager::isBattleState(0) || GfMenuManager::isBattleState(1)) {
        setId = GfSelectBlade::getStartBattleSetId(partyId);
      }
      if (acc.getValidDriverId() == DRIVER_UNKNOWN_1 && (setId == 3 || setId == 4)) {
        if (acc.getBlade(0, false) == BLADE_HOMURA) {
          setId = 0;
        } else if (acc.getBlade(1, false) == BLADE_HOMURA) {
          setId = 1;
        } else if (acc.getBlade(2, false) == BLADE_HOMURA) {
          setId = 2;
        }
      }
      u32 index = setId + slot;
      if (index >= slotMax) {
        index -= slotMax;
      }
      result = index;
    }
  }
  return result;
}

} // namespace gf

template class ml::fixed_size_alloc_inside<gf::MENUREF_OBJ, 512>;
template class ml::fixed_size_alloc_inside<gf::GfMenuReference::REFLIST, 32>;

template mm::mtl::PtrSingleton<gf::GfMenuReference>::~PtrSingleton();
template mm::mtl::FixedList<gf::GfMenuReference::REFLIST *, 32>::iterator
mm::mtl::FixedList<gf::GfMenuReference::REFLIST *, 32>::erase(mm::mtl::FixedList<gf::GfMenuReference::REFLIST *, 32>::iterator it);
template mm::mtl::FixedArray<mm::mtl::IntrusivePtr<gf::GfMenuReferenceNumber>, 7>::~FixedArray();

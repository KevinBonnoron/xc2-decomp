#include "gf/menu/adapter/gf_menu_gfobj_adapter.h"

#include "battle/misc_battle.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/gf_game_visible.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 BATTLE_STATE_UNKNOWN_1 = 1;
constexpr u32 BATTLE_STATE_UNKNOWN_3 = 3;
constexpr u32 BATTLE_STATE_UNKNOWN_5 = 5;
constexpr u32 PARTY_DRIVER_COUNT = 3;
// Inferred role: object attribute bit that shows the info icon of a hidden object; original name unknown.
constexpr u32 unknown002 = 1 << 3;

// Inferred role: blade property of an object, nullptr when it has none; original name unknown.
static inline GfObjPropertyBlade *unknown003(GF_OBJ_HANDLE *handle) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return nullptr;
  }
  return property->getBlade();
}

GfMenuGfObjAdapter::GfMenuGfObjAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways, bool isUpdateAfter)
    : GfMenuAdapter(plugin, isUpdateAfter, isUpdateAlways), unknown48(INVALID_HANDLE), unknown70(0), unknown78(nullptr) {}

GfMenuGfObjAdapter::~GfMenuGfObjAdapter() {
  if (unknown78 != nullptr) {
    delete unknown78;
    unknown78 = nullptr;
  }
}

bool GfMenuGfObjAdapter::update_NowHp(GF_OBJ_HANDLE *handle) {
  u32 hp;
  u32 maxHp;
  if (!GfGameUtil::getNowHpForUi(handle, &hp) || !GfGameUtil::getMaxHpForUi(handle, &maxHp)) {
    return false;
  }

  setNumberMax(maxHp);
  setNumber(hp);
  return true;
}

bool GfMenuGfObjAdapter::update_Battle(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() == OBJECT_TYPE_ENEMY) {
    return true;
  }

  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }
  return property->unknown10 != nullptr ? property->unknown10->unknown30 : false;
}

bool GfMenuGfObjAdapter::update_InfoBody(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if ((acc.getAttribute() & unknown002) == 0 && !GfGameVisible::isVisible(handle)) {
    return false;
  }
  if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_1) && acc.getType() == OBJECT_TYPE_ENEMY) {
    GfObjProperty *property = GfObjUtil::getProperty(handle);
    if (property == nullptr) {
      return false;
    }
    GfObjPropertyCharacter *character = property->unknown10;
    if (character == nullptr) {
      return false;
    }
    if (GfMenuManager::getTargetObjHandle() == handle) {
      if (character->unknown30) {
        return false;
      }
    } else if (!character->unknown30) {
      return false;
    }
  }
  if (GfGameUtil::isUiNameDistMatch(handle)) {
    return true;
  }
  return GfMenuManager::getTargetObjHandle() == handle;
}

bool GfMenuGfObjAdapter::update_InfoDisp(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if ((acc.getAttribute() & unknown002) == 0 && !GfGameVisible::isVisible(handle)) {
    return false;
  }
  return GfGameUtil::isUiInfoIconDistMatch(handle);
}

bool GfMenuGfObjAdapter::update_InfoIcon(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if ((acc.getAttribute() & unknown002) == 0 && !GfGameVisible::isVisible(handle)) {
    return false;
  }
  int icon = GfGameUtil::getUiInfoIconBdatId(handle);
  if (icon == -1) {
    return false;
  }
  setNumber(GfMenuBdat::getIconImageIndex(icon));
  return GfGameUtil::isUiInfoIconDistMatch(handle);
}

bool GfMenuGfObjAdapter::update_TargetDisp(GF_OBJ_HANDLE *handle) { return GfMenuManager::getTargetObjHandle() == handle; }

bool GfMenuGfObjAdapter::update_AccessDisp(GF_OBJ_HANDLE *handle) { return GfMenuManager::getAccessObjHandle() == handle; }

bool GfMenuGfObjAdapter::update_EN_Lv(GF_OBJ_HANDLE *handle) {
  DataParamAcc acc(handle);
  if (acc.isValid()) {
    setNumber(acc.getLevel(false));
    return true;
  }
  return false;
}

bool GfMenuGfObjAdapter::update_EN_ArtsName(GF_OBJ_HANDLE *handle) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }

  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr || enemy->unknownc4 == 0) {
    return false;
  }

  ui::UIStr name = GfMenuObjUtil::getEnemyArtsName(enemy->unknownc4);
  if (name.isValid()) {
    setText(name);
    return true;
  }
  return false;
}

bool GfMenuGfObjAdapter::update_EN_ArtsID(GF_OBJ_HANDLE *handle) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }

  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr) {
    return false;
  }

  setNumber(enemy->unknownc4);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboName(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }

  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }

  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr || enemy->unknowndc == 0) {
    return false;
  }

  setText(GfMenuObjUtil::getElementComboName(enemy->unknowndc));
  return true;
}

bool GfMenuGfObjAdapter::update_EN_Aggressive(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }
  GF_OBJ_HANDLE *enemy = acc.getHandle();
  GfGameUtil::UiEnemyStatusIconInfo info;
  if (enemy != INVALID_HANDLE) {
    info.create(enemy);
  }
  return info.unknown00;
}

bool GfMenuGfObjAdapter::update_EN_Link(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }
  GF_OBJ_HANDLE *enemy = acc.getHandle();
  GfGameUtil::UiEnemyStatusIconInfo info;
  if (enemy != INVALID_HANDLE) {
    info.create(enemy);
  }
  return info.unknown01;
}

bool GfMenuGfObjAdapter::update_EN_Arts(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }
  return enemy->unknownc4 != 0;
}

bool GfMenuGfObjAdapter::update_EN_FightComboIcon(GF_OBJ_HANDLE *handle) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }

  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr || enemy->unknownec == 0) {
    return false;
  }

  setNumber(enemy->unknownec - 1);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_FightComboName(GF_OBJ_HANDLE *handle) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }

  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr || enemy->unknownec == 0) {
    return false;
  }

  u32 msgId = GfMenuObjUtil::getMsgIDFromList(BDAT_MNU_MSG_REACTION, enemy->unknownec);
  ui::UIStr name(GfDataBdat::getFP(BDAT_MENU_ENEMY_REACTION), msgId);
  setText(name);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_FightComboTime(GF_OBJ_HANDLE *handle) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr) {
    return false;
  }

  GfObjPropertyEnemy *enemy = property->getEnemy();
  if (enemy == nullptr) {
    return false;
  }

  setNumber(enemy->unknownf0 * 100.0f);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_FightComboSuspend(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }
  return enemy->unknownf4;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboLv(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr || enemy->unknowndc == 0 || enemy->unknowne8 == 0) {
    return false;
  }

  setNumber(enemy->unknowne8 - 1);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboTime(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr || enemy->unknowndc == 0 || enemy->unknowne8 == 3) {
    return false;
  }

  setNumber(enemy->unknowne0 * 100.0f);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboState(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }
  return enemy->unknowndc != 0;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboAttrIcon(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr || enemy->unknowndc == 0) {
    return false;
  }

  u8 attribute = GfMenuObjUtil::getElementComboAtr(enemy->unknowndc);
  if (attribute == 0) {
    return false;
  }

  setNumber(attribute);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboAttrCol(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr || enemy->unknowndc == 0) {
    return false;
  }

  mm::mtl::FixStr<32> color;
  color.format("elemental%02d", GfMenuObjUtil::getElementComboAtr(enemy->unknowndc));
  setColor(color.c_str());
  return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboAttrPtn(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr || enemy->unknowndc == 0) {
    return false;
  }

  mm::mtl::FixStr<32> pattern;
  pattern.format("element%02d", GfMenuObjUtil::getElementComboAtr(enemy->unknowndc));
  setTextFacePattern(pattern.c_str());
  return true;
}

bool GfMenuGfObjAdapter::update_EN_ElemComboSuspend(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }
  return enemy->unknowne4;
}

// Inferred role: highest weak attribute of an enemy, 0 for none; original name unknown.
static inline u32 unknown001(const GfObjPropertyEnemy &enemy) {
  u32 attribute = 0;
  for (u32 index = 1; index <= 8; index++) {
    attribute = (enemy.unknownd8 & (1 << index)) != 0 ? index : attribute;
  }
  return attribute;
}

bool GfMenuGfObjAdapter::update_EN_WeakAttrIcon(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }

  u32 attribute = unknown001(*enemy);
  setNumber(attribute);
  return attribute != 0;
}

bool GfMenuGfObjAdapter::update_EN_WeakAttrColor(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }

  u32 attribute = unknown001(*enemy);

  mm::mtl::FixStr<32> color;
  color.format("elemental%02d", attribute);
  setColor(color.c_str());
  return attribute != 0;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrOn(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }

  if (enemy->unknown120.size() > unknown70) {
    u32 attribute = enemy->unknown120[unknown70];
    if (attribute >= 1 && attribute <= 8) {
      return (enemy->unknownfc[attribute].unknown00 & unknown138::FLAG_UNKNOWN_0) != 0;
    }
  }
  return false;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrTarget(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }

  if (enemy->unknown120.size() > unknown70) {
    u32 attribute = enemy->unknown120[unknown70];
    if (attribute >= 1 && attribute <= 8) {
      u16 flags = enemy->unknownfc[attribute].unknown00;
      if ((flags & unknown138::FLAG_UNKNOWN_2) == 0) {
        return (flags & unknown138::FLAG_UNKNOWN_1) != 0;
      }
    }
  }
  return false;
}

bool GfMenuGfObjAdapter::update_EN_ResAttrBurst(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }

  if (enemy->unknown120.size() > unknown70) {
    u32 attribute = enemy->unknown120[unknown70];
    if (attribute >= 1 && attribute <= 8) {
      return (enemy->unknownfc[attribute].unknown00 & unknown138::FLAG_UNKNOWN_2) != 0;
    }
  }
  return false;
}

bool GfMenuGfObjAdapter::update_EN_ElemEffID(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr) {
    return false;
  }

  setNumber(enemy->unknownf8);
  return true;
}

bool GfMenuGfObjAdapter::update_EN_TypeIcon(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return false;
  }

  if (GfMenuObjUtil::isEnemyBoss(handle)) {
    setNumber(2);
  } else if (GfMenuObjUtil::isEnemyNamed(handle)) {
    setNumber(1);
  } else {
    setNumber(0);
  }
  return true;
}

bool GfMenuGfObjAdapter::update_EN_Scout(GF_OBJ_HANDLE *handle) {
  GfObjPropertyEnemy *enemy = getEnProperty(handle);
  if (enemy == nullptr || !enemy->unknownc2) {
    return false;
  }

  setNumber(0);
  return true;
}

bool GfMenuGfObjAdapter::update_BL_Kizuna(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  GfObjPropertyBlade *blade = unknown003(handle);
  if (blade == nullptr) {
    return false;
  }

  setNumber(btl::Misc::GetKizunaStage(blade->unknown1a4, nullptr) + 1);
  return true;
}

bool GfMenuGfObjAdapter::update_BL_Special(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  GfObjPropertyBlade *blade = unknown003(handle);
  if (blade == nullptr) {
    return false;
  }

  int number;
  if (unknown70 == blade->unknown1a8) {
    number = blade->unknown1ac * 100.0f;
  } else if (unknown70 > blade->unknown1a8) {
    number = 0;
  } else {
    number = getNumberMax();
  }

  setNumber(number);
  return number > 0;
}

bool GfMenuGfObjAdapter::update_BL_SpecialLv(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  GfObjPropertyBlade *blade = unknown003(handle);
  if (blade == nullptr) {
    return false;
  }

  setNumber(blade->unknown1a8);
  return true;
}

bool GfMenuGfObjAdapter::update_BL_ChangeRecast(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_5)) {
    DataParamAcc paramAcc(handle);
    if (!paramAcc.isValid()) {
      return false;
    }

    if (paramAcc.getValidBdatId() == BLADE_HOMURI) {
      if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_3)) {
        setNumber(100);
        return true;
      }
    } else if (GfDataBlade::getSetDriver(BLADE_HOMURI) == GfDataBlade::getSetDriver(paramAcc.getValidBdatId())) {
      setNumber(0);
      return false;
    }
  }

  GfObjPropertyBlade *blade = unknown003(handle);
  if (blade == nullptr) {
    return false;
  }

  setNumber(blade->unknown1b0 * 100.0f);
  return blade->unknown1b0 > 0.0f;
}

bool GfMenuGfObjAdapter::update_BL_DispComboReady(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() == OBJECT_TYPE_BLADE && !GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_3)) {
    GfObjPropertyBlade *blade = unknown003(handle);
    if (blade == nullptr) {
      return false;
    }

    if ((blade->unknown1b4 & GfObjPropertyBlade::FLAG_UNKNOWN_0) != 0) {
      return true;
    }
    return (blade->unknown1b4 & GfObjPropertyBlade::FLAG_UNKNOWN_1) != 0;
  }
  return false;
}

bool GfMenuGfObjAdapter::update_BL_DispCurrent(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_3)) {
    int partyId = GfMenuReference::getChainAttackActionPartyID();
    if (partyId >= 0 && partyId < PARTY_DRIVER_COUNT) {
      return false;
    }
  }
  return GfMenuObjUtil::getLeaderBladeHandle(true) == handle;
}

void GfMenuGfObjAdapter::update(const fw::UpdateInfo &info) {
  if (unknown78 != nullptr) {
    changeGfObj(unknown78->getGfObjHandle());
  }

  if ((unknown20 & (FLAG_CHANGED | FLAG_UPDATE_ALWAYS)) != 0 && unknown50.isValid()) {
    setDisp(unknown48 != INVALID_HANDLE ? unknown50(unknown48) : false);
    unknown20 &= ~FLAG_CHANGED;
  }
}

void GfMenuGfObjAdapter::changeGfObj(GF_OBJ_HANDLE *handle) {
  if (unknown48 != handle) {
    unknown48 = handle;
    setChange();
  }
}

void GfMenuGfObjAdapter::changePartyDriver(u8 partyId) {
  if (unknown78 != nullptr && unknown78->fromPartyDriver() != nullptr) {
    PartyDriverConverter *converter = unknown78->fromPartyDriver();
    converter->unknown08 = partyId;
  }
}

void GfMenuGfObjAdapter::changePartyBlade(u8 partyId, u8 slot) {
  if (unknown78 != nullptr && unknown78->fromPartyBlade() != nullptr) {
    PartyBladeConverter *converter = unknown78->fromPartyBlade();
    converter->unknown08 = partyId;
    converter->unknown0c = slot;
  }
}

GfObjPropertyEnemy *GfMenuGfObjAdapter::getEnProperty(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return nullptr;
  }

  GfObjProperty *property = GfObjUtil::getProperty(handle);
  return property != nullptr ? property->getEnemy() : nullptr;
}

GF_OBJ_HANDLE *GfMenuGfObjAdapter::PartyDriverConverter::getGfObjHandle() { return GfGameParty::getHandleDriver(unknown08); }

GfMenuGfObjAdapter::PartyDriverConverter *GfMenuGfObjAdapter::PartyDriverConverter::fromPartyDriver() { return this; }

GfMenuGfObjAdapter::PartyBladeConverter *GfMenuGfObjAdapter::IConverter::fromPartyBlade() { return nullptr; }

GfMenuGfObjAdapter::PartyDriverConverter *GfMenuGfObjAdapter::IConverter::fromPartyDriver() { return nullptr; }

GF_OBJ_HANDLE *GfMenuGfObjAdapter::PartyBladeConverter::getGfObjHandle() {
  u32 partyId = unknown08;
  if (partyId == 0) {
    if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_3)) {
      int chainPartyId = GfMenuReference::getChainAttackActionPartyID();
      partyId = chainPartyId >= 0 && chainPartyId < PARTY_DRIVER_COUNT ? chainPartyId : 0;
    } else {
      partyId = 0;
    }
  }
  return GfMenuObjUtil::getBladeHandleFromPartySlot(partyId, unknown0c, unknown10);
}

GfMenuGfObjAdapter::PartyBladeConverter *GfMenuGfObjAdapter::PartyBladeConverter::fromPartyBlade() { return this; }

GF_OBJ_HANDLE *GfMenuGfObjAdapter::TargetEnemyConverter::getGfObjHandle() { return GfMenuManager::getTargetObjHandle(); }

GF_OBJ_HANDLE *GfMenuGfObjAdapter::ReferenceConverter::getGfObjHandle() {
  if (unknown08.get() != nullptr) {
    return unknown08.get()->unknown001();
  }
  return INVALID_HANDLE;
}

} // namespace gf

template bool mm::mtl::Delegate<bool(gf::GF_OBJ_HANDLE *)>::memberFuncInvoker<gf::GfMenuGfObjAdapter>(const mm::mtl::Delegate<bool(gf::GF_OBJ_HANDLE *)> *, gf::GF_OBJ_HANDLE *);

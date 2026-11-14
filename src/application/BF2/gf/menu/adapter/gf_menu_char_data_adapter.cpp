#include "gf/menu/adapter/gf_menu_char_data_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_battle.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_blade_arts.h"
#include "gf/data/gf_data_blade_arts_n.h"
#include "gf/data/gf_data_blade_skill.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_skill.h"
#include "gf/data/gf_data_en_book.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_field_skill.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_manager.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/list/gf_menu_blade_list.h"
#include "gf/menu/list/gf_menu_driver_list.h"
#include "gf/menu/list/gf_menu_enemy_list.h"
#include "gf/menu/list/gf_menu_id_list.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

constexpr u32 BATTLE_STATE_UNKNOWN_3 = 3;
// Inferred role: number of drivers of the party, bound of the chain attack party index; original name unknown.
constexpr u32 PARTY_DRIVER_UNKNOWN_3 = 3;

static GfMenuCharDataAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuCharDataAdapter::update_HpMax, {GfMenuAdapter::unknown004_0, 0, 9999}},
    {&GfMenuCharDataAdapter::update_Lv, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuCharDataAdapter::update_Name, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_FaceIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_PhysDef, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_EtherDef, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_Guard, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_AutoAtkDmg, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuCharDataAdapter::update_Critical, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_HobbyName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_HobbyIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_FavoriteItemName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_FavoriteItemIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_Strength, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuCharDataAdapter::update_EtherPow, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuCharDataAdapter::update_Dex, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuCharDataAdapter::update_Agl, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuCharDataAdapter::update_Luck, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuCharDataAdapter::update_AttrName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_Exp, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ExpNext, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ExpBonus, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ExpProgress, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_DR_ExpProgressBonus, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_DR_LevelUpEnable, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_Wp, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuCharDataAdapter::update_DR_Sp, {GfMenuAdapter::unknown004_0, 0, 99999}},
    {&GfMenuCharDataAdapter::update_DR_SetBladeFace, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_Bustup, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_BustupPlate, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_BladeEnable, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_KizunaRingOpen, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuCharDataAdapter::update_DR_KizunaRingMax, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuCharDataAdapter::update_DR_IdeaPoint, {GfMenuAdapter::unknown004_0, 0, 10000}},
    {&GfMenuCharDataAdapter::update_DR_IdeaLv, {GfMenuAdapter::unknown004_0, 0, 10}},
    {&GfMenuCharDataAdapter::update_DR_ExpNextVirtual, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_DR_ClassName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_ClassBuffName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_DR_ClassBuffVal, {GfMenuAdapter::unknown004_0, -99, 99}},
    {&GfMenuCharDataAdapter::update_DR_ClassBuffLv, {GfMenuAdapter::unknown004_0, 0, 3}},
    {&GfMenuCharDataAdapter::update_DR_BtlFace, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_WeaponIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AttrIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SpecialName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SpecialDesc, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_ArtsName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_ArtsDesc, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_FieldSkillName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_FieldSkillDesc, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_FieldSkillLv, {GfMenuAdapter::unknown004_0, 0, 9}},
    {&GfMenuCharDataAdapter::update_BL_SkillName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SkillDesc, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_SkillLv, {GfMenuAdapter::unknown004_0, 0, 5}},
    {&GfMenuCharDataAdapter::update_BL_RareIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Bustup, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Power, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuCharDataAdapter::update_BL_Attr, {GfMenuAdapter::unknown004_0, 0, 9}},
    {&GfMenuCharDataAdapter::update_BL_AttrCol, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AttrCol2, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_GenderIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Enable, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_DR_Name, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_DR_Face, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_weaponTypeName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_GenderText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_RoleName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_RoleIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_ChangeBtnIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_IdeaPoint, {GfMenuAdapter::unknown004_0, 0, 10000}},
    {&GfMenuCharDataAdapter::update_BL_IdeaLv, {GfMenuAdapter::unknown004_0, 0, 10}},
    {&GfMenuCharDataAdapter::update_BL_RecastLv, {GfMenuAdapter::unknown004_0, 0, 5}},
    {&GfMenuCharDataAdapter::update_BL_BtlSkillIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_BtlSkillLv, {GfMenuAdapter::unknown004_0, 0, 5}},
    {&GfMenuCharDataAdapter::update_BL_Selectable, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Selectable2, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Releasable, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AffinityIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_AffinityText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_KizunaRingOpen, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuCharDataAdapter::update_BL_KizunaRingMax, {GfMenuAdapter::unknown004_0, 0, 99}},
    {&GfMenuCharDataAdapter::update_BL_CorrectiveTypeName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_CorrectiveValue, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuCharDataAdapter::update_BL_OrbSlotEnable, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_InMercenry, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Rank, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_Rarity, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_CVName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_IlustName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_TeamName, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_BL_WpnImage, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_BookID, {GfMenuAdapter::unknown004_0, 0, 9999}},
    {&GfMenuCharDataAdapter::update_EN_Family, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_Genus, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuCharDataAdapter::update_EN_RewardExp, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuCharDataAdapter::update_EN_RewardGold, {GfMenuAdapter::unknown004_0, 0, 999999999}},
};

GfMenuCharDataAdapter::GfObjConverter *GfMenuCharDataAdapter::IConverter::fromGfObj() { return nullptr; }

GfMenuCharDataAdapter::PartyDriverConverter *GfMenuCharDataAdapter::IConverter::fromPartyDriver() { return nullptr; }

GfMenuCharDataAdapter::PartyBladeConverter *GfMenuCharDataAdapter::IConverter::fromPartyBlade() { return nullptr; }

void GfMenuCharDataAdapter::GfObjConverter::getCharData(u8 &type, u32 &id) {
  GfObjAcc acc(unknown08);
  type = acc.getType();
  id = acc.getBdatId();
}

GfMenuCharDataAdapter::GfObjConverter *GfMenuCharDataAdapter::GfObjConverter::fromGfObj() { return this; }

void GfMenuCharDataAdapter::PartyDriverConverter::getCharData(u8 &type, u32 &id) {
  GfObjAcc acc(GfGameParty::getHandleDriver(unknown08));
  type = acc.getType();
  id = acc.getBdatId();
}

GfMenuCharDataAdapter::PartyDriverConverter *GfMenuCharDataAdapter::PartyDriverConverter::fromPartyDriver() { return this; }

void GfMenuCharDataAdapter::PartyBladeConverter::getCharData(u8 &type, u32 &id) {
  u32 partyId = unknown08;
  if (partyId == 0) {
    if (GfMenuManager::isBattleState(BATTLE_STATE_UNKNOWN_3)) {
      int chainPartyId = GfMenuReference::getChainAttackActionPartyID();
      if (chainPartyId >= 0 && chainPartyId < PARTY_DRIVER_UNKNOWN_3) {
        partyId = chainPartyId;
      } else {
        partyId = 0;
      }
    } else {
      partyId = 0;
    }
  }
  bool isBackSlot = unknown10;
  type = OBJECT_TYPE_BLADE;
  if (!isBackSlot) {
    id = GfMenuObjUtil::getBladeIDFromPartySlot(partyId, unknown0c, unknown11);
  } else {
    id = GfMenuObjUtil::getBladeIDFromPartyBackSlot(partyId, unknown0c, unknown11);
  }
}

GfMenuCharDataAdapter::PartyBladeConverter *GfMenuCharDataAdapter::PartyBladeConverter::fromPartyBlade() { return this; }

void GfMenuCharDataAdapter::DriverListConverter::getCharData(u8 &type, u32 &id) {
  u32 index = unknown10;
  if (index == -1) {
    index = unknown08->getIndex(true);
    if (index == -1) {
      return;
    }
  }
  if (static_cast<int>(index) < static_cast<int>(unknown08->getSize())) {
    type = OBJECT_TYPE_PC;
    id = unknown08->getContents(unknown08->getPageIndex(index)).unknown00;
  }
}

void GfMenuCharDataAdapter::BladeListConverter::getCharData(u8 &type, u32 &id) {
  u32 index = unknown10;
  if (index == -1) {
    index = unknown08->getIndex(true);
    if (index == -1) {
      return;
    }
  }
  if (static_cast<int>(index) < static_cast<int>(unknown08->getSize())) {
    type = OBJECT_TYPE_BLADE;
    id = unknown08->getContents(unknown08->getPageIndex(index)).unknown00;
  }
}

void GfMenuCharDataAdapter::EnemyListConverter::getCharData(u8 &type, u32 &id) {
  u32 index = unknown10;
  if (index == -1) {
    index = unknown08->getIndex(true);
    if (index == -1) {
      return;
    }
  }
  if (static_cast<int>(index) < static_cast<int>(unknown08->getSize())) {
    type = OBJECT_TYPE_ENEMY;
    id = unknown08->getContents(unknown08->getPageIndex(index)).unknown00;
  }
}

void GfMenuCharDataAdapter::EnBookListConverter::getCharData(u8 &type, u32 &id) {
  u32 index = unknown10;
  if (index == -1) {
    index = unknown08->getIndex(true);
    if (index == -1) {
      return;
    }
  }
  if (static_cast<int>(index) < static_cast<int>(unknown08->getSize())) {
    u32 book = unknown08->getContents(unknown08->getPageIndex(index)).unknown00;
    type = OBJECT_TYPE_ENEMY;
    id = GfBdatChrEnArrange::get()->getBTL_EnBookBaseEnemyID(book);
  }
}

void GfMenuCharDataAdapter::ReferenceDriverConverter::getCharData(u8 &type, u32 &id) {
  type = OBJECT_TYPE_PC;
  id = GfMenuReference::getReferenceDriverID(unknown08);
}

void GfMenuCharDataAdapter::ReferenceBladeConverter::getCharData(u8 &type, u32 &id) {
  type = OBJECT_TYPE_BLADE;
  id = GfMenuReference::getReferenceBladeID(unknown08);
}

void GfMenuCharDataAdapter::BladeSetConverter::getCharData(u8 &type, u32 &id) {
  DataParamAcc acc(OBJECT_TYPE_PC, unknown08, GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    u32 blade = GfMenuObjUtil::getBladeIDFromDriverSlot(acc.getValidDriverId(), unknown0c);
    type = OBJECT_TYPE_BLADE;
    id = blade;
  }
}

void GfMenuCharDataAdapter::ReferenceBladeSetConverter::getCharData(u8 &type, u32 &id) {
  DataParamAcc acc(OBJECT_TYPE_PC, GfMenuReference::getReferenceDriverID(unknown08), GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    u32 blade = GfMenuObjUtil::getBladeIDFromDriverSlot(acc.getValidDriverId(), unknown0c);
    type = OBJECT_TYPE_BLADE;
    id = blade;
  }
}

void GfMenuCharDataAdapter::ReferenceBladeOwnerDriverConverter::getCharData(u8 &type, u32 &id) {
  type = OBJECT_TYPE_PC;
  id = GfDataBlade::getSetDriver(GfMenuReference::getReferenceBladeID(unknown08));
}

GfMenuCharDataAdapter::GfMenuCharDataAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways)
    : GfMenuAdapter(plugin, false, isUpdateAlways), unknown70(nullptr), unknown78(0), unknown79(0), unknown7c(0), unknown80(0), unknown88(nullptr) {}

GfMenuCharDataAdapter::~GfMenuCharDataAdapter() {
  if (unknown70 != nullptr) {
    delete unknown70;
    unknown70 = nullptr;
  }
  mm::mtl::safeRelease(unknown88);
}

void GfMenuCharDataAdapter::setSlotList(GfMenuBladeList *list) {
  mm::mtl::safeRelease(unknown88);
  unknown88 = list;
  unknown88->addRef();
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::create(u32 handle, u32 type, u8 objType, u32 id, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &info = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, info.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 614 as in the original source: it is the line argument of operator new.
#line 614
      GfMenuCharDataAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuCharDataAdapter(plugin, isUpdateAlways);
      adapter->unknown50.bind(adapter, info.update);
      adapter->unknown78 = objType;
      adapter->unknown7c = id;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromGfObj(u32 handle, u32 type, GF_OBJ_HANDLE *objHandle, bool isUpdateAlways) {
  // __LINE__ must be 645 as in the original source: it is the line argument of operator new.
#line 645
  GfObjConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjConverter(objHandle);
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromPartyDriver(u32 handle, u32 type, u8 partyId, bool isUpdateAlways) {
  // __LINE__ must be 652 as in the original source: it is the line argument of operator new.
#line 652
  PartyDriverConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PartyDriverConverter(partyId);
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromPartyBlade(u32 handle, u32 type, u8 partyId, int slot, bool isUpdateAlways, bool isBackSlot, bool isVirtual) {
  // __LINE__ must be 659 as in the original source: it is the line argument of operator new.
#line 659
  PartyBladeConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PartyBladeConverter(partyId, slot, isBackSlot, isVirtual);
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromReferenceDriver(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 696 as in the original source: it is the line argument of operator new.
#line 696
  ReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceDriverConverter(index);
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromReferenceBlade(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 703 as in the original source: it is the line argument of operator new.
#line 703
  ReferenceBladeConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceBladeConverter(index);
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

GfMenuCharDataAdapter *GfMenuCharDataAdapter::createFromReferenceBladeOwnerDriver(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  // __LINE__ must be 724 as in the original source: it is the line argument of operator new.
#line 724
  ReferenceBladeOwnerDriverConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceBladeOwnerDriverConverter(index);
  u8 objType;
  u32 id;
  converter->getCharData(objType, id);
  GfMenuCharDataAdapter *adapter = create(handle, type, objType, id, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown70 = converter;
  }
  return adapter;
}

void GfMenuCharDataAdapter::update(const fw::UpdateInfo &info) {
  if (unknown70 != nullptr) {
    u8 type = 0;
    u32 id = 0;
    unknown70->getCharData(type, id);
    changeCharData(type, id);
  }
  if ((unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) == 0) {
    return;
  }
  if (!unknown50.isValid()) {
    return;
  }
  DataParamAcc acc(unknown78, unknown7c, GIMMICK_TYPE_UNKNOWN_0);
  bool isDisp = false;
  if (acc.isValid()) {
    acc.setMenuParam();
    if (unknown79 != 0) {
      if (unknown78 == OBJECT_TYPE_PC) {
        if (GfMenuReference::getDriverVirtualLevel() != 0) {
          acc.setVirtualLevel(GfMenuReference::getDriverVirtualLevel());
        }
        if (GfMenuReference::getDriverVirtualBladeID() != 0) {
          u32 blade = GfMenuReference::getDriverVirtualBladeID();
          int slot = GfMenuReference::getDriverVirtualBladeSlot();
          if (static_cast<int>(acc.getValidDriverId()) == static_cast<int>(GfDataBlade::getSetDriver(blade))) {
            slot = GfDataBlade::getDriverSetID(blade);
          }
          acc.setVirtualSetBlade(GfMenuReference::getDriverVirtualBladeID(), slot);
        }
        if (GfMenuReference::getDriverVirtualEquipAcc() != 0) {
          u32 slot = GfMenuReference::getDriverVirtualEquipAccSlot();
          u32 accessory = GfMenuReference::getDriverVirtualEquipAcc();
          acc.setVirtualEquipAcc(slot, accessory);
        }
      } else if (unknown78 == OBJECT_TYPE_BLADE) {
        if (GfMenuReference::getBladeVirtualEquipWpnChip() != 0) {
          acc.setVirtualEquipWpnChip(GfMenuReference::getBladeVirtualEquipWpnChip());
        }
        if (GfMenuReference::getBladeVirtualEquipOrb() != 0) {
          u32 slot = GfMenuReference::getBladeVirtualEquipOrbSlot();
          u32 orb = GfMenuReference::getBladeVirtualEquipOrb();
          acc.setVirtualEquipOrb(orb, slot);
        }
      }
    }
    if (acc.getObjType() == OBJECT_TYPE_BLADE && !GfMenuObjUtil::isValidBlade(acc.getValidBdatId())) {
      isDisp = false;
    } else {
      isDisp = unknown50(acc);
    }
  }
  setDisp(isDisp);
  unknown20 &= ~FLAG_UNKNOWN_0;
}

void GfMenuCharDataAdapter::changeGfObj(GF_OBJ_HANDLE *handle) {
  if (unknown70 != nullptr && unknown70->fromGfObj() != nullptr) {
    GfObjConverter *converter = unknown70->fromGfObj();
    converter->unknown08 = handle;
  }
}

void GfMenuCharDataAdapter::changePartyDriver(u8 partyId) {
  if (unknown70 != nullptr && unknown70->fromPartyDriver() != nullptr) {
    PartyDriverConverter *converter = unknown70->fromPartyDriver();
    converter->unknown08 = partyId;
  }
}

void GfMenuCharDataAdapter::changePartyBlade(u8 partyId, u8 slot) {
  if (unknown70 != nullptr && unknown70->fromPartyBlade() != nullptr) {
    PartyBladeConverter *converter = unknown70->fromPartyBlade();
    converter->unknown08 = partyId;
    converter->unknown0c = slot;
  }
}

bool GfMenuCharDataAdapter::update_DR_Exp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    u32 used = GfDataDriver::getExpUsed(acc.getValidDriverId());
    setNumber(acc.getBattleExp() + used);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    u8 *bdat;
    u32 textId;
    if (GfDataBattle::getClassName(bdat, textId, acc.getClass(unknown79 == 1))) {
      if (bdat == nullptr) {
        return false;
      }
      if (textId == 0) {
        return false;
      }
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_BtlFace(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    int icon;
    if (acc.isValid() && acc.getObjType() == OBJECT_TYPE_PC && acc.getBdatId() == 1 && GfGameManager::isRexAwakening()) {
      icon = 8;
    } else {
      u32 iconData = acc.getIconData();
      if (iconData == 0) {
        return false;
      }
      icon = GfMenuBdat::getIconImageIndex(iconData);
    }
    setNumber(icon);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_FieldSkillIndex(acc);
    if (index >= 3) {
      return false;
    }
    bool result = false;
    if (acc.getFieldSkill(index, false) != 0) {
      setNumber(acc.getFieldSkillLevel(index, false));
      result = true;
    }
    return result;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SkillLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_SkillIndex(acc);
    if (index >= 3) {
      return false;
    }
    setNumber(acc.getBladeSkillLevel(index, false));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AttrCol2(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 attribute = GfMenuObjUtil::getBladeAttributeID(acc.getValidBdatId());
    mm::mtl::FixStr<32> color;
    color.format("elemental%02d", attribute);
    setColor(color.c_str());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_RoleName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_ROLE_NAME_MS);
    if (bdat != nullptr) {
      ui::UIStr text(bdat, acc.getRole(false));
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Selectable2(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    if (GfMenuReference::getReferenceDriverID(0) == 1) {
      setMulColor("white");
    } else {
      const char *color = "unuse";
      if (!GfDataBlade::isEnableEngageRex(acc.getValidBdatId())) {
        color = "white";
      }
      setMulColor(color);
    }
  }
  return true;
}

bool GfMenuCharDataAdapter::update_BL_CorrectiveValue(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    if (GfMenuObjUtil::getBladeCorrectiveType(acc.getValidBdatId()) != 0) {
      setNumber(GfMenuObjUtil::getBladeCorrectiveRatio(acc.getValidBdatId()));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_ArtsName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 arts = acc.getBladeArtsN(unknown80, false);
    if (arts == 0) {
      return false;
    }
    u8 *bdat;
    u32 textId;
    if (GfDataBladeArtsN::getName(bdat, textId, arts)) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_ArtsDesc(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 arts = acc.getBladeArtsN(unknown80, false);
    if (arts == 0) {
      return false;
    }
    u8 *bdat;
    u32 textId;
    if (GfDataBladeArtsN::getCaption(bdat, textId, arts)) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_GenderIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    int icon;
    if (GfDataBlade::isMale(acc.getValidBdatId())) {
      icon = 0;
    } else if (GfDataBlade::isFemale(acc.getValidBdatId())) {
      icon = 1;
    } else {
      icon = 2;
    }
    setNumber(icon);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_DR_Face(const DataParamAcc &acc) {
  u32 driver = GfDataBlade::getCreator(acc.getValidBdatId());
  if (driver == 0) {
    return false;
  }
  DataParamAcc driverAcc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
  int icon = GfMenuObjUtil::getFaceIconID(driverAcc);
  bool result = false;
  if (icon != 0) {
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    result = true;
  }
  return result;
}

bool GfMenuCharDataAdapter::update_HpMax(const DataParamAcc &acc) {
  setNumber(acc.getHpMax(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_PhysDef(const DataParamAcc &acc) {
  setNumber(acc.getPArmor(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_EtherDef(const DataParamAcc &acc) {
  setNumber(acc.getEArmor(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Guard(const DataParamAcc &acc) {
  setNumber(acc.getGuardRate(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_AutoAtkDmg(const DataParamAcc &acc) {
  u32 min = acc.getNorAtkDmgMin(unknown79 == 1);
  u32 max = acc.getNorAtkDmgMax(unknown79 == 1);
  setNumber((min + max) / 2);
  return true;
}

bool GfMenuCharDataAdapter::update_Critical(const DataParamAcc &acc) {
  setNumber(acc.getCriticalRate(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Strength(const DataParamAcc &acc) {
  setNumber(acc.getStrength(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_EtherPow(const DataParamAcc &acc) {
  setNumber(acc.getPowerEther(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Dex(const DataParamAcc &acc) {
  setNumber(acc.getDex(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Agl(const DataParamAcc &acc) {
  setNumber(acc.getAgility(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Luck(const DataParamAcc &acc) {
  setNumber(acc.getLuck(unknown79 == 1));
  return true;
}

bool GfMenuCharDataAdapter::update_Lv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC || acc.getObjType() == OBJECT_TYPE_BLADE || acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(acc.getLevel(unknown79 == 1));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpNext(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    if (acc.getLevel(false) < 99) {
      setNumber(acc.getExpNext(false));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpBonus(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(acc.getExp());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_LevelUpEnable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    return GfDataDriver::isEnableLevelUp(acc.getValidDriverId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_Wp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(acc.getWeaponPoint(unknown80));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_Sp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(acc.getSkillPoint());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_Bustup(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(GfMenuObjUtil::convMenuDriverID(acc.getValidDriverId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_BustupPlate(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    int driver = GfMenuObjUtil::convMenuDriverID(acc.getValidDriverId());
    int plate = 0;
    if (driver != 0) {
      plate = driver - 1;
    }
    setNumber(plate);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_BladeEnable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    return GfMenuObjUtil::isValidBlade(acc.getBlade(unknown80, false));
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_KizunaRingOpen(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(GfDataDriverSkill::getValidSkillNum(acc.getValidDriverId(), false));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_KizunaRingMax(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(15);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_IdeaPoint(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    SDataIdea *idea = GfDataDriver::getSDataIdea(acc.getValidDriverId());
    setNumber(idea->unknown00[unknown80].unknown00);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffVal(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    setNumber(GfMenuObjUtil::getDriverClassBuffRatio(acc.getClass(unknown79 == 1), unknown80));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    u8 level = GfMenuObjUtil::getDriverClassBuffLv(acc.getClass(unknown79 == 1), unknown80);
    if (level != 0) {
      setNumber(level - 1);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_WeaponIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 weaponType = GfDataBlade::getBladeWpnType(acc.getValidBdatId());
    if (weaponType != 0) {
      setNumber(weaponType - 1);
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AttrIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 icon = GfMenuObjUtil::getBladeAttributeIconID(acc.getValidBdatId());
    if (icon != 0) {
      setNumber(GfMenuBdat::getIconImageIndex(icon));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_RareIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 icon = GfMenuObjUtil::getBladeRareIconID(acc.getValidBdatId());
    if (icon != 0) {
      setNumber(GfMenuBdat::getIconImageIndex(icon));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Bustup(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfMenuObjUtil::convMenuBladeID(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Power(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(acc.getBladePower(unknown79 == 1));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Attr(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfMenuObjUtil::getBladeAttributeID(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AttrCol(const DataParamAcc &acc) { return acc.getObjType() == OBJECT_TYPE_BLADE; }

bool GfMenuCharDataAdapter::update_BL_Enable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    return GfMenuObjUtil::isValidBlade(acc.getValidBdatId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_IdeaPoint(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    SDataIdea *idea = GfDataBlade::getSDataIdea(acc.getValidBdatId());
    setNumber(idea->unknown00[unknown80].unknown00);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_IdeaLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    SDataIdea *idea = GfDataBlade::getSDataIdea(acc.getValidBdatId());
    setNumber(idea->unknown00[unknown80].unknown04);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_RecastLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(0x137);
    setNumber(GfMenuBdat::getValueLevel(bdat, acc.getCoolTime()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_BtlSkillIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    acc.getBladeSkill(unknown80, false);
    setNumber(0);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_BtlSkillLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(acc.getBladeSkillLevel(unknown80, false));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Selectable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    const char *color = nullptr;
    if (!GfMenuObjUtil::isBladeSelectable(acc.getValidBdatId(), unknown88)) {
      color = "unuse";
    }
    setMulColor(color);
  }
  return true;
}

bool GfMenuCharDataAdapter::update_BL_Releasable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    const char *color = nullptr;
    if (!GfMenuObjUtil::isBladeReleasable(acc.getValidBdatId(), unknown88)) {
      color = "unuse";
    }
    setMulColor(color);
  }
  return true;
}

bool GfMenuCharDataAdapter::update_BL_AffinityIcon(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 rank = GfDataBlade::getTrustRank(acc.getValidBdatId());
    if (rank > 1) {
      setNumber(rank - 1);
    }
    return rank != 0;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_KizunaRingOpen(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfDataBlade::getKizunaringCompleteNum(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_KizunaRingMax(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    setNumber(GfDataBlade::getKizunaringMax(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_OrbSlotEnable(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    return unknown80 < GfEquipUtil::getEquipOrbMax(acc.getValidBdatId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_InMercenry(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    return GfDataBlade::isActivateMercenaryTeam(acc.getValidBdatId());
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Rank(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      setNumber(GfMenuObjUtil::getBladeRank(blade));
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_Rarity(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      setNumber(GfMenuObjUtil::getBladeRarity(blade));
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_AttrName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE || acc.getObjType() == OBJECT_TYPE_ENEMY) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_ATTR);
    int attribute = acc.getAttribute(-1, false);
    u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_ATTR_MS);
    u16 name = Bdat::getVal(bdat, "name", Bdat::getIdTop(msBdat) + attribute).valueU16;
    ui::UIStr text(msBdat, name);
    setText(text);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SpecialName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat;
    u32 textId;
    bool found;
    if (unknown80 < 3) {
      u32 arts = acc.getBladeArts(unknown80, false);
      if (arts == 0) {
        return false;
      }
      found = GfDataBladeArts::getName(bdat, textId, arts);
    } else {
      u32 arts = acc.getBladeArtsEx(false);
      if (arts == 0) {
        return false;
      }
      found = GfDataBladeArts::getExName(bdat, textId, arts);
    }
    if (found) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SpecialDesc(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat;
    u32 textId;
    bool found;
    u32 artsEx = acc.getBladeArtsEx(false);
    if (artsEx == 0) {
      return false;
    }
    if (unknown80 < 3) {
      u32 arts = acc.getBladeArts(unknown80, false);
      if (arts == 0) {
        return false;
      }
      found = GfDataBladeArts::getCaption(bdat, textId, arts);
    } else {
      found = GfDataBladeArts::getExCaption(bdat, textId, artsEx);
    }
    if (found) {
      ui::UIStr text(bdat, textId);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_FieldSkillIndex(acc);
    if (index < 3) {
      u32 fieldSkill = acc.getFieldSkill(index, false);
      if (fieldSkill == 0) {
        return false;
      }
      if (acc.getFieldSkillLevel(index, false) == 0) {
        return false;
      }
      u8 *bdat;
      u32 textId;
      if (GfDataFieldSkill::getName(bdat, textId, fieldSkill)) {
        ui::UIStr text(bdat, textId);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_FieldSkillDesc(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_FieldSkillIndex(acc);
    if (index < 3) {
      u32 fieldSkill = acc.getFieldSkill(index, false);
      if (fieldSkill == 0) {
        return false;
      }
      u8 *bdat;
      u32 textId;
      if (GfDataFieldSkill::getCaption(bdat, textId, fieldSkill)) {
        ui::UIStr text(bdat, textId);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SkillName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 index = getBL_SkillIndex(acc);
    if (index < 3) {
      u32 skill = acc.getBladeSkill(index, false);
      if (skill == 0) {
        return false;
      }
      if (acc.getBladeSkillLevel(index, false) == 0) {
        return false;
      }
      u8 *bdat;
      u32 textId;
      if (GfDataBladeSkill::getName(bdat, textId, skill)) {
        ui::UIStr text(bdat, textId);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_weaponTypeName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_WEAPON_TYPE);
    u32 weaponType = GfDataBlade::getSDataBlade(acc.getValidBdatId()).unknown821;
    u8 *msBdat = GfDataBdat::getFP(BDAT_ITM_PCWPNTYPE_MS);
    u16 name = Bdat::getVal(bdat, "name", weaponType).valueU16;
    ui::UIStr text(msBdat, name);
    setText(text);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_CorrectiveTypeName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_MENU_ST_CORRECTIONVALUE);
    if (bdat != nullptr) {
      u32 type = GfMenuObjUtil::getBladeCorrectiveType(acc.getValidBdatId());
      if (type != 0) {
        ui::UIStr text(bdat, type);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_TeamName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      ui::UIStr text;
      if (GfMenuObjUtil::getBladeTeamName(blade, text)) {
        setText(text);
        return true;
      }
      return false;
    }
    return false;
  }
  return false;
}

u32 GfMenuCharDataAdapter::getBL_FieldSkillIndex(const DataParamAcc &acc) {
  u32 count = 0;
  for (u32 index = 0; index < 3; index++) {
    if (acc.getFieldSkill(index, false) != 0 && acc.getFieldSkillLevel(index, false) != 0) {
      if (count == unknown80) {
        return index;
      }
      count++;
    }
  }
  return 3;
}

u32 GfMenuCharDataAdapter::getBL_SkillIndex(const DataParamAcc &acc) {
  u32 count = 0;
  for (u32 index = 0; index < 3; index++) {
    if (acc.getBladeSkill(index, false) != 0 && acc.getBladeSkillLevel(index, false) != 0) {
      if (count == unknown80) {
        return index;
      }
      count++;
    }
  }
  return 3;
}

bool GfMenuCharDataAdapter::update_EN_Genus(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    GfBdatRsc *bdatRsc = GfBdatRsc::get();
    if (bdatRsc != nullptr) {
      u32 rsc = GfDataEnemy::getRscIdByArrangeId(acc.getValidBdatId());
      if (rsc != 0) {
        u32 name = bdatRsc->getRscEnGenusNAME(bdatRsc->getRscEnTypeGenus(rsc));
        ui::UIStr text(GfDataBdat::getFP(BDAT_BTL_ENGENUS_MS), name);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_Name(const DataParamAcc &acc) {
  setText(GfMenuObjUtil::getName(acc));
  return true;
}

bool GfMenuCharDataAdapter::update_FaceIcon(const DataParamAcc &acc) {
  u32 icon = GfMenuObjUtil::getFaceIconID(acc);
  if (icon != 0) {
    setNumber(GfMenuBdat::getIconImageIndex(icon));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_SetBladeFace(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    u32 blade = acc.getBlade(-1, false);
    if (blade == 0) {
      return false;
    }
    if (!GfDataBlade::isDummyBlade(blade)) {
      DataParamAcc bladeAcc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
      int icon = GfMenuObjUtil::getFaceIconID(bladeAcc);
      if (icon != 0) {
        setNumber(GfMenuBdat::getIconImageIndex(icon));
        return true;
      }
      return false;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_IdeaLv(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    SDataIdea *idea = GfDataDriver::getSDataIdea(acc.getValidDriverId());
    u32 level = idea->unknown00[unknown80].unknown04;
    if (unknown79 != 0) {
      setNumberMax(15);
      int virtualLevel = level + GfMenuReference::getDriverAddIdeaLv(unknown80);
      u32 clamped = 0;
      if (virtualLevel >= 0) {
        clamped = virtualLevel;
      }
      level = 15;
      if (clamped < 16) {
        level = clamped;
      }
    }
    setNumber(level);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpNextVirtual(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_PC) {
    return false;
  }

  int exp;
  if (GfMenuReference::getDriverVirtualLevel() == 0) {
    if (acc.getObjType() != OBJECT_TYPE_PC) {
      return false;
    }
    if (acc.getLevel(false) > 98) {
      return false;
    }
    exp = acc.getExpNext(false);
  } else {
    exp = GfDataDriver::getExpSetLevel(acc.getValidDriverId(), GfMenuReference::getDriverVirtualLevel() + 1);
  }
  setNumber(exp);
  return true;
}

bool GfMenuCharDataAdapter::update_EN_BookID(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(GfDataEnBook::getEnBoolId(acc.getValidBdatId()));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_EN_RewardExp(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(acc.getLevelExp());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_EN_RewardGold(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    setNumber(acc.getLevelGold());
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpProgress(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    if (acc.getLevel(false) < 99) {
      f32 exp = acc.getBattleExp();
      f32 next = GfDataDriver::getExpSetLevel(acc.getValidDriverId(), acc.getLevel(false) + 1);
      u32 progress;
      if (exp >= next) {
        progress = 100;
      } else {
        progress = exp / next * 100.0f;
      }
      setNumber(progress);
    } else {
      setNumber(0);
    }
    setNumberMax(100);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ExpProgressBonus(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    if (acc.getLevel(false) < 99) {
      f32 exp = acc.getBattleExp() + acc.getExp();
      f32 next = GfDataDriver::getExpSetLevel(acc.getValidDriverId(), acc.getLevel(false) + 1);
      u32 progress;
      if (exp >= next) {
        progress = 100;
      } else {
        progress = exp / next * 100.0f;
      }
      setNumber(progress);
    } else {
      setNumber(0);
    }
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_DR_ClassBuffName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    u32 type = GfMenuObjUtil::getDriverClassBuffType(acc.getClass(unknown79 == 1), unknown80);
    if (type != 0) {
      ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_CLASS), type);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_DR_Name(const DataParamAcc &acc) {
  u32 driver = GfDataBlade::getCreator(acc.getValidBdatId());
  if (driver != 0) {
    DataParamAcc driverAcc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
    setText(GfMenuObjUtil::getName(driverAcc));
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_AffinityText(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    GfIdea rank = GfDataBlade::getTrustRank(acc.getValidBdatId());
    setText(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_ST_CONGENIALITY), rank));
    return rank != 0;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_CVName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      u32 name = GfDataBlade::getMenuCastName(blade);
      if (name != 0) {
        ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_CAST_NAME), name);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_IlustName(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 blade = acc.getValidBdatId();
    if (GfMenuObjUtil::isValidBlade(blade)) {
      u32 name = GfDataBlade::getMenuIlustName(blade);
      if (name != 0) {
        ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_ILUST_NAME), name);
        setText(text);
        return true;
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_EN_Family(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_ENEMY) {
    GfBdatRsc *bdatRsc = GfBdatRsc::get();
    if (bdatRsc != nullptr) {
      u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_ENB_FAMILY);
      if (bdat != nullptr) {
        u32 rsc = GfDataEnemy::getRscIdByArrangeId(acc.getValidBdatId());
        if (rsc != 0) {
          u32 family = bdatRsc->getRscEnTypeFamily(rsc);
          if (family == 0) {
            return false;
          }
          u32 name = Bdat::getVal(bdat, "name", family - 1).valueU16;
          ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_ENEMY_CATEGORY), name);
          setText(text);
          return true;
        }
      }
    }
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_GenderText(const DataParamAcc &acc) {
  if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    u32 gender;
    if (GfDataBlade::isMale(acc.getValidBdatId())) {
      gender = 0;
    } else if (GfDataBlade::isFemale(acc.getValidBdatId())) {
      gender = 1;
    } else {
      gender = 2;
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_GENDER);
    u32 top = Bdat::getIdTop(bdat);
    u8 *msBdat = GfDataBdat::getFP(BDAT_MENU_MS);
    u16 name = Bdat::getVal(bdat, "name", top + gender).valueU16;
    ui::UIStr text(msBdat, name);
    setText(text);
    return true;
  }
  return false;
}

bool GfMenuCharDataAdapter::update_BL_SkillDesc(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  u32 index = getBL_SkillIndex(acc);
  if (index >= 3) {
    return false;
  }
  u32 skill = acc.getBladeSkill(index, false);
  if (skill == 0) {
    return false;
  }
  if (acc.getBladeSkillLevel(index, false) == 0) {
    return false;
  }
  u8 *bdat;
  u32 textId;
  if (!GfDataBladeSkill::getEnhanceCaption(bdat, textId, skill, acc.getBladeSkillLevel(index, false))) {
    return false;
  }
  u16 enhance = GfDataBladeSkill::getEnhance(skill, acc.getBladeSkillLevel(index, false));
  ui::UIStr text(bdat, textId);
  text.unknown12 = enhance;
  setText(text);
  return true;
}

bool GfMenuCharDataAdapter::update_HobbyIcon(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_PC && acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  u32 favorite = 0;
  u32 id = 0;
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    id = acc.getValidDriverId();
    favorite = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(unknown80));
    if (favorite == 0) {
      return false;
    }
  } else if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    id = acc.getValidBdatId();
    favorite = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(unknown80));
    if (favorite == 0) {
      return false;
    }
  }
  u32 stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, unknown80 != 0 ? FAVORITE_UNKNOWN_1 : FAVORITE_UNKNOWN_0);
  if (stat == 2) {
    return false;
  }
  u32 icon = 0;
  if (stat == 1) {
    icon = 0x40;
  } else if (!GfMenuItemUtil::getIconNumber(ItemType::ITEM_TYPE_UNKNOWN_10, favorite, icon, false)) {
    return false;
  }
  setNumber(icon);
  return true;
}

bool GfMenuCharDataAdapter::update_HobbyName(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_PC && acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  u32 favorite = 0;
  u32 id = 0;
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    id = acc.getValidDriverId();
    favorite = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(unknown80));
  } else if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    id = acc.getValidBdatId();
    favorite = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(unknown80));
  }
  u32 stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, unknown80 != 0 ? FAVORITE_UNKNOWN_1 : FAVORITE_UNKNOWN_0);
  u32 bdatId = BDAT_MENU_MS;
  u32 textId;
  if (stat == 1) {
    textId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", 1).valueU16;
  } else if (stat == 2) {
    textId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", 2).valueU16;
  } else {
    if (favorite >= FAVORITE_CATEGORY_FOOD_UNKNOWN_12) {
      textId = favorite - (FAVORITE_CATEGORY_FOOD_UNKNOWN_12 - 1);
      bdatId = BDAT_MENU_FAVORITE_CATEGORY;
    } else {
      return false;
    }
  }
  ui::UIStr text(GfDataBdat::getFP(bdatId), textId);
  setText(text);
  return true;
}

bool GfMenuCharDataAdapter::update_FavoriteItemIcon(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_PC && acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  u32 id = 0;
  u32 favorite = 0;
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    id = acc.getValidDriverId();
    favorite = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(FAVORITE_UNKNOWN_2 + unknown80));
    if (favorite == 0) {
      return false;
    }
  } else if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    id = acc.getValidBdatId();
    favorite = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(FAVORITE_UNKNOWN_2 + unknown80));
    if (favorite == 0) {
      return false;
    }
  }
  u32 stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, unknown80 != 0 ? FAVORITE_UNKNOWN_3 : FAVORITE_UNKNOWN_2);
  if (stat == 2) {
    return false;
  }
  u32 icon = 0;
  if (stat == 1) {
    icon = 0x40;
  } else {
    ItemProperty property;
    GfItemUtil::getProperty(property, favorite, 0);
    if (property.unknown4e >= FAVORITE_CATEGORY_FOOD_UNKNOWN_12) {
      if (!GfMenuItemUtil::getIconNumber(ItemType::ITEM_TYPE_UNKNOWN_10, property.unknown4e, icon, false)) {
        return false;
      }
    } else {
      return false;
    }
  }
  setNumber(icon);
  return true;
}

bool GfMenuCharDataAdapter::update_FavoriteItemName(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_PC && acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  u32 favorite = 0;
  u32 id = 0;
  if (acc.getObjType() == OBJECT_TYPE_PC) {
    id = acc.getValidDriverId();
    favorite = GfDataDriver::getFavorite(id, static_cast<FAVORITE>(FAVORITE_UNKNOWN_2 + unknown80));
  } else if (acc.getObjType() == OBJECT_TYPE_BLADE) {
    id = acc.getValidBdatId();
    favorite = GfDataBlade::getFavorite(id, static_cast<FAVORITE>(FAVORITE_UNKNOWN_2 + unknown80));
  }
  u32 stat = GfMenuObjUtil::getFavoriteStat(acc.getObjType(), id, unknown80 != 0 ? FAVORITE_UNKNOWN_3 : FAVORITE_UNKNOWN_2);
  ui::UIStr name;
  if (stat != 1) {
    if (stat == 2) {
      u32 textId = Bdat::getVal(GfDataBdat::getFP(BDAT_MNU_MSG_POUCH), "name", 2).valueU16;
      name.copy(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), textId));
    } else {
      GfMenuItemUtil::getItemName(ItemType::ITEM_TYPE_UNKNOWN_10, favorite, name);
    }
    if (name.isValid()) {
      setText(name);
      return true;
    }
  }
  return false;
}

// Inferred role: buttons assigned to the three blade slots of a driver; original name unknown.
static const u32 unknown001[] = {0x1000, 0x2000, 0x4000};

bool GfMenuCharDataAdapter::update_BL_ChangeBtnIcon(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  if (!GfDataBlade::isSetBlade(acc.getValidBdatId())) {
    return false;
  }
  DataParamAcc driverAcc(OBJECT_TYPE_PC, GfDataBlade::getSetDriver(acc.getValidBdatId()), GIMMICK_TYPE_UNKNOWN_0);
  bool result = false;
  if (driverAcc.isValid()) {
    for (u32 slot = 0; slot < sizeof(unknown001) / sizeof(unknown001[0]); slot++) {
      if (driverAcc.getBlade(slot, false) == acc.getValidBdatId()) {
        s16 icon = GfMenuObjUtil::getBtnIconNumber(unknown001[slot]);
        setNumber(GfMenuBdat::getIconImageIndex(icon));
        result = true;
        break;
      }
    }
  }
  return result;
}

bool GfMenuCharDataAdapter::update_BL_WpnImage(const DataParamAcc &acc) {
  if (acc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = acc.getEquipWeapon(0, unknown79 == 1);
  if (weapon == 0) {
    return false;
  }
  u32 rsc = 0;
  if (!GfDataBlade::isCommonBlade(acc.getValidBdatId())) {
    GfBdatChrBl *bdatChrBl = GfBdatChrBl::get();
    if (bdatItem->isPcWpnFlagPrivate(weapon)) {
      if (bdatChrBl->getChrBlPrivateWpnR_Driver(acc.getValidBdatId()) != 0) {
        rsc = bdatChrBl->getChrBlPrivateWpnR_Driver(acc.getValidBdatId());
      } else if (bdatChrBl->getChrBlPrivateWpnR(acc.getValidBdatId()) != 0) {
        rsc = bdatChrBl->getChrBlPrivateWpnR(acc.getValidBdatId());
      }
    }
  }
  if (rsc == 0) {
    rsc = bdatItem->getPcWpnRscR(weapon);
    if (rsc == 0) {
      return false;
    }
  }
  int image = GfBdatRsc::get()->getRSC_PcWpnMenuImageID(rsc);
  if (image == 0) {
    return false;
  }
  setNumber(image);
  return true;
}

} // namespace gf

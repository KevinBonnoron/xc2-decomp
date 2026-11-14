#include "gf/menu/adapter/gf_menu_item_adapter.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/item/gf_pouch_util.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/gf_menu_item_util.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixstr.h"
#include "ui/plugin/ui_object_time_plugin.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_object_plugin.h"
#include "ui/ui_str.h"

namespace gf {

namespace {

// Inferred role: reward type of each item of a mercenaries mission; original name unknown.
const QUEST_REWARD unknown001[] = {QUEST_REWARD_UNKNOWN_8, QUEST_REWARD_UNKNOWN_9, QUEST_REWARD_UNKNOWN_10, QUEST_REWARD_UNKNOWN_11};

} // namespace

static GfMenuItemAdapter::TypeInfo TYPE_INFOS[] = {
    {&GfMenuItemAdapter::update_Name, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuItemAdapter::update_Icon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuItemAdapter::update_IconAll, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuItemAdapter::update_Count, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuItemAdapter::update_CountMax, {GfMenuAdapter::unknown004_0, 0, 999}},
    {&GfMenuItemAdapter::update_Price, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuItemAdapter::update_SellPrice, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuItemAdapter::update_RareIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuItemAdapter::update_EquipableColor, {GfMenuAdapter::unknown004_8, 0, 0}},
    {&GfMenuItemAdapter::update_Caption, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuItemAdapter::update_CategoryIcon, {GfMenuAdapter::unknown004_1, 0, 0}},
    {&GfMenuItemAdapter::update_GetAreaText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuItemAdapter::update_SubCategoryText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuItemAdapter::update_EffectTime, {GfMenuAdapter::unknown004_7, 3, 0}},
    {&GfMenuItemAdapter::update_EffectText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuItemAdapter::update_useEnergy, {GfMenuAdapter::unknown004_0, 0, 9999}},
    {&GfMenuItemAdapter::update_needEther, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuItemAdapter::update_dustEther, {GfMenuAdapter::unknown004_0, 0, 999999999}},
    {&GfMenuItemAdapter::update_PArmor, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuItemAdapter::update_EArmor, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuItemAdapter::update_revise, {GfMenuAdapter::unknown004_0, 0, 100}},
    {&GfMenuItemAdapter::update_dispRevise, {GfMenuAdapter::unknown004_3, 0, 0}},
    {&GfMenuItemAdapter::update_roleText, {GfMenuAdapter::unknown004_2, 0, 0}},
    {&GfMenuItemAdapter::update_canStack, {GfMenuAdapter::unknown004_3, 0, 0}},
};

GfMenuItemAdapter::GfMenuItemAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways) : GfMenuAdapter(plugin, false, isUpdateAlways), unknown68(nullptr) {}

GfMenuItemAdapter::~GfMenuItemAdapter() {
  if (unknown68 != nullptr) {
    delete unknown68;
    unknown68 = nullptr;
  }
}

GfMenuItemAdapter *GfMenuItemAdapter::create(u32 handle, u32 type, const MenuItemInfo &info, bool isUpdateAlways) {
  ui::UIObjectAcc acc(handle);
  if (acc.isValid()) {
    TypeInfo &typeInfo = TYPE_INFOS[type];
    ui::UIObjectPlugin *plugin = createPlugin(handle, typeInfo.setup);
    if (plugin != nullptr) {
      // __LINE__ must be 641 as in the original source: it is the line argument of operator new.
#line 641
      GfMenuItemAdapter *adapter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuItemAdapter(plugin, isUpdateAlways);
      adapter->unknown48.bind(adapter, typeInfo.update);
      adapter->unknown38 = info;
      plugin->release();
      return adapter;
    }
  }
  return nullptr;
}

bool GfMenuItemAdapter::update_Name(const MenuItemInfo &info) {
  bool result = false;
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    ui::UIStr name;
    GfMenuItemUtil::getItemName(info.unknown00, info.unknown04, name);
    if (name.isValid()) {
      setText(name);
      result = true;
    }
  }
  return result;
}

bool GfMenuItemAdapter::update_IconAll(const MenuItemInfo &info) {
  if (unknown38.unknown04 == 0 || unknown38.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0 || info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0) {
    return false;
  }
  u32 param = 0;
  u32 number;
  if (info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_10) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    param = property.unknown4e;
    if (param == 0) {
      return false;
    }
  } else if (info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_2) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    param = property.unknown65 + 1;
  } else if (info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_7) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    param = property.unknown4d;
  }
  if (GfMenuItemUtil::getIconNumber(info.unknown00, param, number, false)) {
    setNumber(number);
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_Count(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    setNumber(info.unknown08);
  } else {
    setNumber(0);
  }
  return true;
}

bool GfMenuItemAdapter::update_CountMax(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    setNumber(GfItemUtil::getEnableStock(info.unknown04));
  } else {
    setNumber(0);
  }
  return true;
}

bool GfMenuItemAdapter::update_Price(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    ItemPrice price;
    price.clear();
    GfItemUtil::getPrice(price, info.unknown04, GfMenuReference::getReferenceShopID());
    setNumber(price.unknown04);
  } else {
    setNumber(0);
  }
  return true;
}

bool GfMenuItemAdapter::update_SellPrice(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    if (info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_6 && info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_14 && info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_15) {
      ItemPrice price;
      price.clear();
      GfItemUtil::getPrice(price, info.unknown04, GfMenuReference::getReferenceShopID());
      setNumber(price.unknown08);
      return true;
    }
    return false;
  }
  setNumber(0);
  return false;
}

bool GfMenuItemAdapter::update_RareIcon(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    if (info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_6 && info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_14 && info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_15) {
      setNumber(GfDataItem::getRarity(info.unknown04));
      return true;
    }
    return false;
  }
  return false;
}

bool GfMenuItemAdapter::update_EquipableColor(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0) {
    if (unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_3) {
      if (unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_2) {
        return true;
      }
      if (GfMenuItemUtil::canEquipAcc(info.unknown04, 0, 0) != 0) {
        setMulColor("unuse");
        return true;
      }
    }
    setMulColor("white");
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_CategoryIcon(const MenuItemInfo &info) {
  if (unknown38.unknown04 == 0 || unknown38.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0 || info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_3 || info.unknown04 == 0) {
    return false;
  }
  setNumber(1);
  return true;
}

bool GfMenuItemAdapter::update_GetAreaText(const MenuItemInfo &info) {
  if (unknown38.unknown04 == 0) {
    return false;
  }
  if (unknown38.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0) {
    return false;
  }
  u8 *mapInfoBdat = GfDataBdat::getFP(BDAT_FLD_MAPINFO);
  u16 zone;
  switch (info.unknown00) {
  case ItemType::ITEM_TYPE_UNKNOWN_1: {
    const char *column = unknown70 == 0 ? "Zone" : "Zone2";
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_PC_WPN_CHIP);
    zone = Bdat::getVal(bdat, column, info.unknown04).valueU16;
    break;
  }
  case ItemType::ITEM_TYPE_UNKNOWN_2: {
    const char *column = unknown70 == 0 ? "Zone" : "Zone2";
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_PC_EQUIP);
    zone = Bdat::getVal(bdat, column, info.unknown04).valueU16;
    break;
  }
  case ItemType::ITEM_TYPE_UNKNOWN_7: {
    if (unknown70 != 0) {
      return false;
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_COLLECTION_LIST);
    zone = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    break;
  }
  case ItemType::ITEM_TYPE_UNKNOWN_8: {
    if (unknown70 != 0) {
      return false;
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_TRESURE_LIST);
    zone = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    break;
  }
  case ItemType::ITEM_TYPE_UNKNOWN_10: {
    if (unknown70 != 0) {
      return false;
    }
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_FAVORITE_LIST);
    zone = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    break;
  }
  default:
    return false;
  }
  if (zone != 0) {
    u16 nameId = Bdat::getVal(GfDataBdat::getFP(BDAT_FLD_MAPLIST), "nameID", zone).valueU16;
    ui::UIStr text(mapInfoBdat, nameId);
    if (text.c_str() != nullptr && *text.c_str() != '\0') {
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuItemAdapter::update_SubCategoryText(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_10) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    int index = property.unknown4e - 11;
    if (index > 0) {
      ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_FAVORITE_CATEGORY), index);
      setText(text);
      return true;
    }
  }
  return false;
}

bool GfMenuItemAdapter::update_EffectTime(const MenuItemInfo &info) {
  if (unknown38.unknown04 == 0 || unknown38.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0 || info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_10) {
    return false;
  }
  ItemProperty property;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  ui::uiDateTime time = {};
  time.unknown03_7 = property.unknown52 / 60;
  time.unknown04_6 = property.unknown52 % 60;
  setTime(time);
  return true;
}

bool GfMenuItemAdapter::update_EffectText(const MenuItemInfo &info) {
  if (unknown38.unknown04 == 0 || unknown38.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0 || info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_10 || unknown70 > 2) {
    return false;
  }
  ItemProperty property;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  u16 effect = property.unknown50;
  bool result = false;
  if (effect != 0) {
    u8 *setBdat = GfDataBdat::getFP(BDAT_BTL_POUCH_BUFF_SET);
    u8 *buffBdat = GfDataBdat::getFP(BDAT_BTL_POUCH_BUFF);
    u8 *textBdat = GfDataBdat::getFP(BDAT_BTL_POUCHBUFF_MS);
    mm::mtl::FixStr<32> column;
    column.format("PBuff%d", unknown70 + 1);
    u8 buff = Bdat::getVal(setBdat, column.c_str(), effect).valueU8;
    if (buff != 0) {
      u8 name = Bdat::getVal(buffBdat, "Name", buff).valueU8;
      u16 option = (unknown70 & 3) | (effect << 2);
      ui::UIStr text(textBdat, name);
      text.unknown12 = option;
      setText(text);
      result = true;
    }
  }
  return result;
}

bool GfMenuItemAdapter::update_useEnergy(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 >= ItemType::ITEM_TYPE_UNKNOWN_16 && info.unknown00 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
    setNumber(GfDataHana::getPartsPower(info.unknown04));
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_needEther(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 >= ItemType::ITEM_TYPE_UNKNOWN_16 && info.unknown00 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    setNumber(property.unknown68);
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_dustEther(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 >= ItemType::ITEM_TYPE_UNKNOWN_16 && info.unknown00 <= ItemType::ITEM_TYPE_UNKNOWN_20) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    setNumber(property.unknown6c);
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_PArmor(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_16) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    setNumber(property.unknown76);
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_EArmor(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_16) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    setNumber(property.unknown77);
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_revise(const MenuItemInfo &info) {
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_16) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    u32 revise = property.unknown78;
    if (revise == 0) {
      revise = property.unknown79;
      if (revise == 0) {
        revise = property.unknown7a;
        if (revise == 0) {
          revise = property.unknown7b;
          if (revise == 0) {
            revise = property.unknown7c == 0 ? property.unknown7d : property.unknown7c;
          }
        }
      }
    }
    setNumber(revise);
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_dispRevise(const MenuItemInfo &info) {
  if (unknown38.unknown04 == 0 || unknown38.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_0 || info.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_16) {
    return false;
  }
  ItemProperty property;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  if (property.unknown78 != 0 && unknown70 == 0) {
    return true;
  }
  if (property.unknown79 != 0 && unknown70 == 1) {
    return true;
  }
  if (property.unknown7a != 0 && unknown70 == 2) {
    return true;
  }
  if (property.unknown7b != 0 && unknown70 == 3) {
    return true;
  }
  if (property.unknown7c != 0 && unknown70 == 4) {
    return true;
  }
  if (property.unknown7d != 0 && unknown70 == 5) {
    return true;
  }
  return false;
}

bool GfMenuItemAdapter::update_roleText(const MenuItemInfo &info) {
  bool result = false;
  if (unknown38.unknown04 != 0 && unknown38.unknown00 != ItemType::ITEM_TYPE_UNKNOWN_0 && info.unknown00 == ItemType::ITEM_TYPE_UNKNOWN_16) {
    ItemProperty property;
    GfItemUtil::getProperty(property, info.unknown04, 0);
    u8 role = property.unknown75;
    if (role != 0) {
      ui::UIStr text(GfDataBdat::getFP(BDAT_MENU_ROLE_NAME_MS), role);
      setText(text);
      result = true;
    }
  }
  return result;
}

bool GfMenuItemAdapter::update_canStack(const MenuItemInfo &info) { return GfMenuItemUtil::canCountStack(info.unknown00); }

GfMenuItemAdapter *GfMenuItemAdapter::createFromCoverter(u32 handle, u32 type, IConverter *converter, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromList(u32 handle, u32 type, GfMenuItemList *list, int listIndex, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 676 as in the original source: it is the line argument of operator new.
#line 676
  ListConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ListConverter(list, listIndex);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromReference(u32 handle, u32 type, mm::mtl::IntrusivePtr<IGfMenuReferenceItem> item, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 687 as in the original source: it is the line argument of operator new.
#line 687
  ReferenceItemConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceItemConverter(item);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromRefernceList(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceList<GfMenuItemList>> list, u32 listIndex, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 698 as in the original source: it is the line argument of operator new.
#line 698
  ReferenceListConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceListConverter(list, listIndex);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromPouch(u32 handle, u32 type, u32 pouchIndex, u32 driver, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 709 as in the original source: it is the line argument of operator new.
#line 709
  PouchConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PouchConverter(pouchIndex, driver);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromPouchReferenceIndex(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driver, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 720 as in the original source: it is the line argument of operator new.
#line 720
  PouchReferenceIndexConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PouchReferenceIndexConverter(number, driver);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromPouchReferenceDriver(u32 handle, u32 type, u32 pouchIndex, u32 driverIndex, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 731 as in the original source: it is the line argument of operator new.
#line 731
  PouchReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PouchReferenceDriverConverter(pouchIndex, driverIndex);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromPouchReferenceIndexReferenceDriver(u32 handle, u32 type, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 driverIndex, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 742 as in the original source: it is the line argument of operator new.
#line 742
  PouchReferenceIndexReferenceDriverConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) PouchReferenceIndexReferenceDriverConverter(number, driverIndex);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromMission(u32 handle, u32 type, u32 mission, u32 index, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 754 as in the original source: it is the line argument of operator new.
#line 754
  MissionConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MissionConverter(mission, index);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromReferenceMission(u32 handle, u32 type, u32 index, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 765 as in the original source: it is the line argument of operator new.
#line 765
  ReferenceMissionConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceMissionConverter(index);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter != nullptr) {
    adapter->unknown68 = converter;
  }
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromDriverEquip(u32 handle, u32 type, u32 driver, u32 slot, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 776 as in the original source: it is the line argument of operator new.
#line 776
  DriverEquipConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) DriverEquipConverter(driver, slot);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromReferenceDriverEquip(u32 handle, u32 type, u32 driverIndex, u32 slot, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 787 as in the original source: it is the line argument of operator new.
#line 787
  ReferenceDriverEquipConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceDriverEquipConverter(driverIndex, slot);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromBladeEquip(u32 handle, u32 type, u32 blade, u32 slot, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 798 as in the original source: it is the line argument of operator new.
#line 798
  BladeEquipConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) BladeEquipConverter(blade, slot);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

GfMenuItemAdapter *GfMenuItemAdapter::createFromReferenceBladeEquip(u32 handle, u32 type, u32 bladeIndex, u32 slot, bool isUpdateAlways) {
  if (handle == 0) {
    return nullptr;
  }
  // __LINE__ must be 809 as in the original source: it is the line argument of operator new.
#line 809
  ReferenceBladeEquipConverter *converter = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) ReferenceBladeEquipConverter(bladeIndex, slot);
  MenuItemInfo info;
  converter->getItemInfo(info);
  GfMenuItemAdapter *adapter = create(handle, type, info, isUpdateAlways);
  if (adapter == nullptr) {
    return nullptr;
  }
  adapter->unknown68 = converter;
  return adapter;
}

void GfMenuItemAdapter::changeItem(const MenuItemInfo &info) {
  if (unknown38.unknown00 == info.unknown00 && unknown38.unknown04 == info.unknown04 && unknown38.unknown08 == info.unknown08) {
    return;
  }
  unknown38 = info;
  setChange();
}

void GfMenuItemAdapter::update(const fw::UpdateInfo &updateInfo) {
  if (unknown68 != nullptr) {
    MenuItemInfo info;
    unknown68->getItemInfo(info);
    changeItem(info);
  }

  if (unknown48.isValid() && (unknown20 & (FLAG_UNKNOWN_0 | FLAG_UNKNOWN_1)) != 0) {
    setDisp(unknown48(unknown38));
    unknown20 &= ~FLAG_UNKNOWN_0;
  }
}

GfMenuItemAdapter::ListConverter *GfMenuItemAdapter::IConverter::fromList() { return nullptr; }

GfMenuItemAdapter::PouchConverter *GfMenuItemAdapter::IConverter::fromPouch() { return nullptr; }

GfMenuItemAdapter::MissionConverter *GfMenuItemAdapter::IConverter::fromMission() { return nullptr; }

void GfMenuItemAdapter::ListConverter::getItemInfo(MenuItemInfo &info) {
  if (listIndex == -1) {
    info = list->getContents(list->getIndex(false));
  } else {
    if (listIndex >= list->getSize()) {
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_0;
      info.unknown04 = 0;
      return;
    }
    info = list->getContents(list->getPageIndex(listIndex));
  }
}

void GfMenuItemAdapter::ReferenceListConverter::getItemInfo(MenuItemInfo &info) {
  if (list->unknown10 != nullptr) {
    GfMenuItemList &itemList = *list->unknown10;
    if (listIndex < itemList.getSize()) {
      info = itemList.getContents(itemList.getPageIndex(listIndex));
    } else {
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_0;
      info.unknown04 = 0;
    }
  }
}

void GfMenuItemAdapter::ReferenceItemConverter::getItemInfo(MenuItemInfo &info) { item->getItem(info); }

void GfMenuItemAdapter::PouchConverter::getItemInfo(MenuItemInfo &info) {
  SDataPouch *pouch = GfPouchUtil::getPouch(driver, pouchIndex);
  info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_10;
  info.unknown04 = pouch->unknown04;
  info.unknown08 = 1;
}

void GfMenuItemAdapter::PouchReferenceIndexConverter::getItemInfo(MenuItemInfo &info) {
  u32 pouchIndex = number->unknown0c;
  SDataPouch *pouch = GfPouchUtil::getPouch(driver, pouchIndex);
  info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_10;
  info.unknown04 = pouch->unknown04;
  info.unknown08 = 1;
}

void GfMenuItemAdapter::PouchReferenceIndexReferenceDriverConverter::getItemInfo(MenuItemInfo &info) {
  u32 pouchIndex = number->unknown0c;
  SDataPouch *pouch = GfPouchUtil::getPouch(GfMenuReference::getReferenceDriverID(driverIndex), pouchIndex);
  info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_10;
  info.unknown04 = pouch->unknown04;
  info.unknown08 = 1;
}

void GfMenuItemAdapter::PouchReferenceDriverConverter::getItemInfo(MenuItemInfo &info) {
  u32 index = pouchIndex;
  SDataPouch *pouch = GfPouchUtil::getPouch(GfMenuReference::getReferenceDriverID(driverIndex), index);
  info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_10;
  info.unknown04 = pouch->unknown04;
  info.unknown08 = 1;
}

void GfMenuItemAdapter::MissionConverter::getItemInfo(MenuItemInfo &info) {
  if (index < 4) {
    u32 item;
    u32 number;
    GfGameMercenaries::getRewardItem(item, number, mission, unknown001[index]);
    GfDataItem::getItemType(info.unknown00, info.unknown04, item);
    info.unknown04 = item;
    info.unknown08 = number;
  }
}

void GfMenuItemAdapter::ReferenceMissionConverter::getItemInfo(MenuItemInfo &info) {
  if (index < 4) {
    u32 item;
    u32 number;
    GfGameMercenaries::getRewardItem(item, number, GfMenuReference::getReferenceMissionID(), unknown001[index]);
    GfDataItem::getItemType(info.unknown00, info.unknown04, item);
    info.unknown04 = item;
    info.unknown08 = number;
  }
}

void GfMenuItemAdapter::DriverEquipConverter::getItemInfo(MenuItemInfo &info) {
  DataParamAcc acc(OBJECT_TYPE_PC, driver, GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    u32 accessory;
    if (slot == 0) {
      accessory = acc.getEquipAcce(0, false);
    } else {
      accessory = 0;
    }
    GfDataItem::getItemType(info.unknown00, info.unknown04, accessory);
    info.unknown08 = 1;
  }
}

void GfMenuItemAdapter::ReferenceDriverEquipConverter::getItemInfo(MenuItemInfo &info) {
  DataParamAcc acc(OBJECT_TYPE_PC, GfMenuReference::getReferenceDriverID(driverIndex), GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    u32 accessory;
    if (slot == 0) {
      accessory = acc.getEquipAcce(0, false);
    } else {
      accessory = 0;
    }
    GfDataItem::getItemType(info.unknown00, info.unknown04, accessory);
    info.unknown08 = 1;
  }
}

void GfMenuItemAdapter::BladeEquipConverter::getItemInfo(MenuItemInfo &info) {
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    if (slot < 3) {
      info.unknown04 = GfEquipUtil::getEquipBladeOrb(blade, slot);
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_3;
    }
    info.unknown08 = 1;
  }
}

void GfMenuItemAdapter::ReferenceBladeEquipConverter::getItemInfo(MenuItemInfo &info) {
  u32 blade = GfMenuReference::getReferenceBladeID(bladeIndex);
  DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_UNKNOWN_0);
  if (acc.isValid()) {
    if (slot < 3) {
      info.unknown04 = GfEquipUtil::getEquipBladeOrb(blade, slot);
      info.unknown00 = ItemType::ITEM_TYPE_UNKNOWN_3;
    }
    info.unknown08 = 1;
  }
}

} // namespace gf

template bool mm::mtl::Delegate<bool(const gf::MenuItemInfo &)>::memberFuncInvoker<gf::GfMenuItemAdapter>(const mm::mtl::Delegate<bool(const gf::MenuItemInfo &)> *, const gf::MenuItemInfo &);

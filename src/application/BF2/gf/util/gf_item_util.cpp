#include "gf/util/gf_item_util.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_shop.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_item_id.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/item/gf_item_box.h"

namespace gf {

enum {
  BOOSTER_VALUE_MAX_DEFAULT = 5,
};

u32 GfItemUtil::getCountByType(ItemType::Type type) {
  u32 start;
  u32 end;
  int count = 0;
  if (GfDataItem::getItemBdatCount(start, end, type)) {
    for (u32 id = start; id < end; id++) {
      count += getItemBoxCount(id);
    }
  }
  return count;
}

u32 GfItemUtil::getItemBoxCount(u32 item) { return GfItemBox::get()->countItem(item); }

u32 GfItemUtil::getCountByItemCategory(u32 category) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 start;
  u32 end;
  int count = 0;
  switch (GfDataItem::getTypeByItemCategory(category)) {
  case ItemType::PRECIOUS:
    if (GfDataItem::getItemBdatCount(start, end, ItemType::PRECIOUS)) {
      for (u32 id = start; id < end; id++) {
        if (bdatItem->getPreciousCategory(id) == category) {
          count += getItemBoxCount(id);
        }
      }
    }
    break;
  case ItemType::COLLECTION_LIST:
    if (GfDataItem::getItemBdatCount(start, end, ItemType::COLLECTION_LIST)) {
      for (u32 id = start; id < end; id++) {
        if (bdatItem->getCollectionListCategory(id) == category) {
          count += getItemBoxCount(id);
        }
      }
    }
    break;
  case ItemType::TRESURE:
    if (GfDataItem::getItemBdatCount(start, end, ItemType::TRESURE)) {
      for (u32 id = start; id < end; id++) {
        if (bdatItem->getTresureCategory(id) == category) {
          count += getItemBoxCount(id);
        }
      }
    }
    break;
  case ItemType::FAVORITE:
    if (GfDataItem::getItemBdatCount(start, end, ItemType::FAVORITE)) {
      for (u32 id = start; id < end; id++) {
        if (bdatItem->getFavoriteCategory(id) == category) {
          count += getItemBoxCount(id);
        }
      }
    }
    break;
  default:
    break;
  }
  return count;
}

bool GfItemUtil::addItemBox(u32 item, int count) {
  if (!addItemBoxWithSilent(item, count)) {
    return false;
  }
  GfEvent::callItemAdd(item, count);
  return true;
}

bool GfItemUtil::addItemBoxWithSilent(u32 item, int count) {
  if (count > 0) {
    if (GfDataItem::isNoMultiple(item) || !GfItemBox::addItem(item, count)) {
      return false;
    }
    GfDataItem::setNoMultiple(item, true);
    return true;
  }
  if (count < 0) {
    return GfItemBox::decItem(item, -count);
  }
  return GfItemBox::addItem(item, count);
}

bool GfItemUtil::addItemBoxForDebug(u32 item, int count) {
  if (!addItemBoxWithSilent(item, count)) {
    return false;
  }
  GfEvent::callItemAdd(item, count);
  return true;
}

u32 GfItemUtil::getItemBoxCountWithoutEquip(u32 item) { return GfItemBox::get()->countItemWithoutEquip(item); }

bool GfItemUtil::isEnableAddItemBox(u32 item, int count) {
  ItemType::Type type = GfDataItem::getItemType(item);
  if (count > 0) {
    int boxCount = GfItemBox::get()->isMulti(type) ? GfItemBox::get()->countItem(item) : GfItemBox::get()->countItemCategory(type);
    int stock = getEnableStock(item);
    return boxCount < stock && count <= stock - boxCount;
  }
  if (count < 0) {
    return GfItemBox::get()->countItem(item) >= -count;
  }
  return false;
}

ItemType::Type GfItemUtil::getType(u32 item) { return GfDataItem::getItemType(item); }

u32 GfItemUtil::getEnableStock(u32 item) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  int stock;
  switch (GfDataItem::getItemType(item)) {
  case ItemType::PRECIOUS:
    stock = bdatItem->getPreciousValueMax(item);
    break;
  case ItemType::FAVORITE: {
    OwnerBonus *ownerBonus = GfGameManager::getOwnerBonus();
    stock = bdatItem->getFavoriteValueMax(item) + ownerBonus->unknown00[OWNER_BONUS_FAVORITE_VALUE_MAX];
    break;
  }
  case ItemType::CRYSTAL_LIST:
    stock = bdatItem->getCrystalListValueMax(item);
    break;
  case ItemType::BOOSTER: {
    OwnerBonus *ownerBonus = GfGameManager::getOwnerBonus();
    int valueMax = bdatItem->getBoosterValueMax(item);
    stock = (valueMax == 0 ? BOOSTER_VALUE_MAX_DEFAULT : valueMax) + ownerBonus->unknown00[OWNER_BONUS_BOOSTER_VALUE_MAX];
    break;
  }
  default:
    stock = GfItemBox::get()->maxStockItem(item);
    break;
  }
  return stock == 0 ? 1 : stock;
}

static u32 atLeastOne(u32 value) { return value == 0 ? 1 : value; }

void GfItemUtil::getPrice(ItemPrice &price, u32 item, u32 shop) {
  u32 value = GfDataItem::getPrice(item);
  price.unknown00 = value;
  price.unknown04 = value;
  price.unknown08 = value / 2;
  price.unknown0c = 0;
  price.unknown10 = 0;
  if (value == 0) {
    return;
  }

  GfBdatShop *bdatShop = GfBdatShop::get();
  u32 level = GfDataDevelop::getLevel(GfGameManager::getMapZoneID());
  f32 buyPrice = price.unknown00;
  if (shop != 0 && level != 0) {
    buyPrice -= buyPrice * bdatShop->getShopListDiscount(shop, level - 1) * 0.01f;
  }
  price.unknown04 = atLeastOne(buyPrice);
  price.unknown0c = atLeastOne(price.unknown00 * 0.01f);
  price.unknown10 = atLeastOne(price.unknown00 * 0.005f);
}

GfItem GfItemUtil::getInfo(u32 item) {
  GfItem info;
  info.unknown02 = getItemBoxCount(item);
  info.unknown00 = item;
  return info;
}

bool GfItemUtil::isPrecious(u32 item) { return GfDataItem::getItemType(item) == ItemType::PRECIOUS; }

void GfItemUtil::getPropertyChip(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown18 = bdatItem->getPcWpnChipDebugName(property.unknown04);
  property.unknown64 = bdatItem->getPcWpnChipRank(property.unknown04);
}

void GfItemUtil::getPropertyAcce(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown18 = bdatItem->getPcEquipDebugName(property.unknown04);
  property.unknown4a = bdatItem->getPcEquipEnhance1(property.unknown04);
  property.unknown4c = 0;
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 0, bdatItem->isPcEquipFlagEqPC01(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 1, bdatItem->isPcEquipFlagEqPC02(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 2, bdatItem->isPcEquipFlagEqPC03(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 3, bdatItem->isPcEquipFlagEqPC04(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 4, bdatItem->isPcEquipFlagEqPC05(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 5, bdatItem->isPcEquipFlagEqPC06(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 6, bdatItem->isPcEquipFlagEqPC07(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 7, bdatItem->isPcEquipFlagEqPC08(property.unknown04));
  property.unknown00.set(ItemProperty::FLAG_EQUIP_DRIVER + 8, bdatItem->isPcEquipFlagEqPC09(property.unknown04));
  property.unknown65 = bdatItem->getPcEquipIcon(property.unknown04);
}

void GfItemUtil::getPropertyOrb(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown18 = bdatItem->getEmptyOrbDebugName(property.unknown04);
  property.unknown54 = bdatItem->getEmptyOrbRecipe(property.unknown04);
  property.unknown56 = bdatItem->getEmptyOrbEquipItemID(property.unknown04);
}

void GfItemUtil::getPropertyOrbEquip(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown18 = bdatItem->getEmptyOrbDebugName(property.unknown04);
  property.unknown4a = bdatItem->getEquipOrbEnhance(property.unknown04);
  property.unknown4c = bdatItem->getEquipOrbEnhanceCategory(property.unknown04);
}

void GfItemUtil::getPropertySalvage(ItemProperty &property) { property.unknown00.set(ItemProperty::FLAG_QUEST, GfBdatItem::get()->getSalvageQuest(property.unknown04) != 0); }

void GfItemUtil::getPropertyPrecious(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown58 = bdatItem->getPreciousCategory(property.unknown04);
  property.unknown5a = bdatItem->getPreciousType(property.unknown04);
}

void GfItemUtil::getPropertyInfo(ItemProperty &property) {}

void GfItemUtil::getPropertyEvent(ItemProperty &property) {}

void GfItemUtil::getPropertyCollect(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown4d = bdatItem->getCollectionListCategory(property.unknown04);
  property.unknown12 = bdatItem->getCollectionListZone(property.unknown04);
}

void GfItemUtil::getPropertyTresure(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown5d = bdatItem->getTresureCategory(property.unknown04);
  property.unknown5e = bdatItem->getTresureGraphic(property.unknown04);
  property.unknown12 = bdatItem->getTresureZone(property.unknown04);
  property.unknown60 = bdatItem->getTresureFlag(property.unknown04);
  property.unknown00.set(ItemProperty::FLAG_NO_MULTIPLE, bdatItem->getTresureNoMultiple(property.unknown04) != 0);
}

void GfItemUtil::getPropertyFavorite(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown4e = bdatItem->getFavoriteCategory(property.unknown04);
  property.unknown12 = bdatItem->getFavoriteZone(property.unknown04);
  property.unknown50 = bdatItem->getFavoriteType(property.unknown04);
  property.unknown52 = bdatItem->getFavoriteTime(property.unknown04);
}

void GfItemUtil::getPropertyCrystal(ItemProperty &property) {}

void GfItemUtil::getPropertyBooster(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown45 = bdatItem->getBoosterCategory(property.unknown04);
  property.unknown46 = bdatItem->getBoosterIdea(property.unknown04);
}

void GfItemUtil::getPropertyHanaArts(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown4a = bdatItem->getITM_HanaArtsEnhEnhance(property.unknown04);
  property.unknown70 = bdatItem->getITM_HanaArtsEnhCondition(property.unknown04);
  property.unknown68 = bdatItem->getITM_HanaArtsEnhNeedEther(property.unknown04);
  property.unknown6c = bdatItem->getITM_HanaArtsEnhDustEther(property.unknown04);
}

void GfItemUtil::getPropertyHanaAssist(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown4a = bdatItem->getITM_HanaAssistEnhance(property.unknown04);
  property.unknown70 = bdatItem->getITM_HanaAssistCondition(property.unknown04);
  property.unknown68 = bdatItem->getITM_HanaAssistNeedEther(property.unknown04);
  property.unknown6c = bdatItem->getITM_HanaAssistDustEther(property.unknown04);
}

void GfItemUtil::getPropertyHanaAttribute(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown74 = bdatItem->getITM_HanaAtrAtr(property.unknown04);
  property.unknown70 = bdatItem->getITM_HanaAtrCondition(property.unknown04);
  property.unknown68 = bdatItem->getITM_HanaAtrNeedEther(property.unknown04);
  property.unknown6c = bdatItem->getITM_HanaAtrDustEther(property.unknown04);
}

void GfItemUtil::getPropertyHanaNArts(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown72 = bdatItem->getITM_HanaNArtsSetNArts(property.unknown04);
  property.unknown70 = bdatItem->getITM_HanaNArtsSetCondition(property.unknown04);
  property.unknown68 = bdatItem->getITM_HanaNArtsSetNeedEther(property.unknown04);
  property.unknown6c = bdatItem->getITM_HanaNArtsSetDustEther(property.unknown04);
}

void GfItemUtil::getPropertyHanaRole(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.unknown70 = bdatItem->getITM_HanaRoleCondition(property.unknown04);
  property.unknown68 = bdatItem->getITM_HanaRoleNeedEther(property.unknown04);
  property.unknown6c = bdatItem->getITM_HanaRoleDustEther(property.unknown04);
  property.unknown75 = bdatItem->getITM_HanaRoleRole(property.unknown04);
  property.unknown76 = bdatItem->getITM_HanaRolePArmor(property.unknown04);
  property.unknown77 = bdatItem->getITM_HanaRoleEArmor(property.unknown04);
  property.unknown78 = bdatItem->getITM_HanaRoleHpMaxRev(property.unknown04);
  property.unknown79 = bdatItem->getITM_HanaRoleStrengthRev(property.unknown04);
  property.unknown7a = bdatItem->getITM_HanaRolePowEtherRev(property.unknown04);
  property.unknown7b = bdatItem->getITM_HanaRoleDexRev(property.unknown04);
  property.unknown7c = bdatItem->getITM_HanaRoleAgilityRev(property.unknown04);
  property.unknown7d = bdatItem->getITM_HanaRoleLuckRev(property.unknown04);
}

bool GfItemUtil::getProperty(ItemProperty &property, u32 item, u32 shop) {
  property.clear();
  ItemType::Type type;
  u32 index;
  if (!GfDataItem::getItemType(type, index, item)) {
    return property.unknown00.test(ItemProperty::FLAG_VALID);
  }

  property.unknown00.set(ItemProperty::FLAG_VALID);
  property.unknown04 = item;
  property.unknown06 = index;
  property.unknown08 = type;
  property.unknown0c = getItemBoxCount(item);
  property.unknown10 = getEnableStock(item);
  property.unknown14 = getItemTime(item);
  GfDataItem::getName(property.unknown20, property.unknown28, item);
  GfDataItem::getCaption(property.unknown20, property.unknown2c, item);
  getPrice(property.unknown30, item, shop);
  property.unknown44 = GfDataItem::getRarity(item);
  property.unknown00.set(ItemProperty::FLAG_NO_SELL, !GfDataItem::isEnableSell(item));

  switch (type) {
  case ItemType::PC_WPN_CHIP:
    getPropertyChip(property);
    break;
  case ItemType::PC_EQUIP:
    getPropertyAcce(property);
    break;
  case ItemType::EQUIP_ORB:
    getPropertyOrbEquip(property);
    break;
  case ItemType::SALVAGE:
    getPropertySalvage(property);
    break;
  case ItemType::PRECIOUS:
    getPropertyPrecious(property);
    break;
  case ItemType::COLLECTION_LIST:
    getPropertyCollect(property);
    break;
  case ItemType::TRESURE:
    getPropertyTresure(property);
    break;
  case ItemType::EMPTY_ORB:
    getPropertyOrb(property);
    break;
  case ItemType::FAVORITE:
    getPropertyFavorite(property);
    break;
  case ItemType::CRYSTAL_LIST:
    getPropertyCrystal(property);
    break;
  case ItemType::BOOSTER:
    getPropertyBooster(property);
    break;
  case ItemType::INFO:
    getPropertyInfo(property);
    break;
  case ItemType::EVENT:
    getPropertyEvent(property);
    break;
  case ItemType::HANA_ROLE:
    getPropertyHanaRole(property);
    break;
  case ItemType::HANA_ATR:
    getPropertyHanaAttribute(property);
    break;
  case ItemType::HANA_ARTS_ENH:
    getPropertyHanaArts(property);
    break;
  case ItemType::HANA_N_ARTS_SET:
    getPropertyHanaNArts(property);
    break;
  case ItemType::HANA_ASSIST:
    getPropertyHanaAssist(property);
    break;
  default:
    return false;
  }
  return property.unknown00.test(ItemProperty::FLAG_VALID);
}

u32 GfItemUtil::getItemTime(u32 item) { return GfItemBox::get()->getItemTime(item); }

u32 GfItemUtil::getItemTime(u32 item, GfItemHandle handle) { return GfItemBox::get()->getItemTime(item, handle); }

bool GfItemUtil::isFavoriteFood(u32 item) {
  if (GfDataItem::getItemType(item) != ItemType::FAVORITE) {
    return false;
  }
  u32 category = GfBdatItem::get()->getFavoriteCategory(item);
  return category >= FAVORITE_CATEGORY_FOOD_FIRST && category <= FAVORITE_CATEGORY_FOOD_LAST;
}

ItemType::Type GfItemUtil::getItemCategory(u32 item) {
  ItemType::Type type;
  u32 index;
  if (!GfDataItem::getItemType(type, index, item)) {
    return ItemType::NONE;
  }
  return index == 0 ? type : ItemType::NONE;
}

u32 GfItemUtil::getCrystalNum() { return getCountByType(ItemType::CRYSTAL_LIST); }

bool GfItemUtil::isValidCrystal(u32 item) {
  ItemType::Type type;
  u32 index;
  if (GfDataItem::getItemType(type, index, item)) {
    if (type == ItemType::CRYSTAL_LIST) {
      u32 condition = GfBdatItem::get()->getCrystalListCondition(item);
      if (condition != 0) {
        return GfGameCond::isGameCond(condition);
      }
    }
  }
  return true;
}

void GfItemUtil::setEquipFlag(u32 item, GfItemHandle handle, bool isEquip) {
  GfItemHandle equipHandle = handle;
  GfItemBox::get()->setEquipFlag(item, equipHandle, isEquip);
}

GfItemHandle GfItemUtil::getNoEquipItemHandle(u32 item) { return GfItemBox::get()->getNoEquipItemHandle(item); }

void GfItemUtil::setupNewGameParam() {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 start = bdatItem->getEventStart();
  u32 end = bdatItem->getEventEnd();
  for (u32 id = start; id < end; id++) {
    u32 count = getItemBoxCount(id);
    if (count != 0) {
      GfItemBox::decItemForNewGame(id, count);
    }
  }

  start = bdatItem->getInfoStart();
  end = bdatItem->getInfoEnd();
  for (u32 id = start; id < end; id++) {
    if (bdatItem->getInfoClearNewGame(id) != 0) {
      u32 count = getItemBoxCount(id);
      if (count != 0) {
        GfItemBox::decItemForNewGame(id, count);
      }
    }
  }

  start = bdatItem->getPreciousStart();
  end = bdatItem->getPreciousEnd();
  for (u32 id = start; id < end; id++) {
    if (bdatItem->getPreciousClearNewGame(id) != 0) {
      u32 count = getItemBoxCount(id);
      if (count != 0) {
        GfItemBox::decItemForNewGame(id, count);
      }
    }
  }

  start = bdatItem->getTresureStart();
  end = bdatItem->getTresureEnd();
  for (u32 id = start; id < end; id++) {
    if (bdatItem->getTresureClearNewGame(id) != 0) {
      u32 count = getItemBoxCount(id);
      if (count != 0) {
        GfItemBox::decItemForNewGame(id, count);
      }
    }
  }

  GfDataItem::setNoMultiple(ITEM_CRYSTAL_WADATSUMI, false);
  GfDataItem::setNoMultiple(ITEM_CRYSTAL_SUZAKU, false);
  GfDataItem::setNoMultiple(ITEM_CRYSTAL_UNNAMED_RARE, false);
  if (getItemBoxCount(ITEM_CRYSTAL_WADATSUMI) != 0) {
    GfItemBox::decItemForNewGame(ITEM_CRYSTAL_WADATSUMI, 1);
  }
}

} // namespace gf

#include "gf/util/gf_equip_util.cpp"
#include "gf/util/gf_shop_util.cpp"

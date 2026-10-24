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
    stock = bdatItem->getFavoriteValueMax(item) + ownerBonus->values[OWNER_BONUS_FAVORITE_VALUE_MAX];
    break;
  }
  case ItemType::CRYSTAL_LIST:
    stock = bdatItem->getCrystalListValueMax(item);
    break;
  case ItemType::BOOSTER: {
    OwnerBonus *ownerBonus = GfGameManager::getOwnerBonus();
    int valueMax = bdatItem->getBoosterValueMax(item);
    stock = (valueMax == 0 ? BOOSTER_VALUE_MAX_DEFAULT : valueMax) + ownerBonus->values[OWNER_BONUS_BOOSTER_VALUE_MAX];
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
  price.price = value;
  price.buyPrice = value;
  price.sellPrice = value / 2;
  price.buyDevelop = 0;
  price.sellDevelop = 0;
  if (value == 0) {
    return;
  }

  GfBdatShop *bdatShop = GfBdatShop::get();
  u32 level = GfDataDevelop::getLevel(GfGameManager::getMapZoneID());
  f32 buyPrice = price.price;
  if (shop != 0 && level != 0) {
    buyPrice -= buyPrice * bdatShop->getShopListDiscount(shop, level - 1) * 0.01f;
  }
  price.buyPrice = atLeastOne(buyPrice);
  price.buyDevelop = atLeastOne(price.price * 0.01f);
  price.sellDevelop = atLeastOne(price.price * 0.005f);
}

GfItem GfItemUtil::getInfo(u32 item) {
  GfItem info;
  info.count = getItemBoxCount(item);
  info.id = item;
  return info;
}

bool GfItemUtil::isPrecious(u32 item) { return GfDataItem::getItemType(item) == ItemType::PRECIOUS; }

void GfItemUtil::getPropertyChip(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.debugName = bdatItem->getPcWpnChipDebugName(property.id);
  property.chipRank = bdatItem->getPcWpnChipRank(property.id);
}

void GfItemUtil::getPropertyAcce(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.debugName = bdatItem->getPcEquipDebugName(property.id);
  property.enhance = bdatItem->getPcEquipEnhance1(property.id);
  property.enhanceCategory = 0;
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 0, bdatItem->isPcEquipFlagEqPC01(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 1, bdatItem->isPcEquipFlagEqPC02(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 2, bdatItem->isPcEquipFlagEqPC03(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 3, bdatItem->isPcEquipFlagEqPC04(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 4, bdatItem->isPcEquipFlagEqPC05(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 5, bdatItem->isPcEquipFlagEqPC06(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 6, bdatItem->isPcEquipFlagEqPC07(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 7, bdatItem->isPcEquipFlagEqPC08(property.id));
  property.flags.set(ItemProperty::FLAG_EQUIP_DRIVER + 8, bdatItem->isPcEquipFlagEqPC09(property.id));
  property.icon = bdatItem->getPcEquipIcon(property.id);
}

void GfItemUtil::getPropertyOrb(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.debugName = bdatItem->getEmptyOrbDebugName(property.id);
  property.recipe = bdatItem->getEmptyOrbRecipe(property.id);
  property.equipItem = bdatItem->getEmptyOrbEquipItemID(property.id);
}

void GfItemUtil::getPropertyOrbEquip(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.debugName = bdatItem->getEmptyOrbDebugName(property.id);
  property.enhance = bdatItem->getEquipOrbEnhance(property.id);
  property.enhanceCategory = bdatItem->getEquipOrbEnhanceCategory(property.id);
}

void GfItemUtil::getPropertySalvage(ItemProperty &property) { property.flags.set(ItemProperty::FLAG_QUEST, GfBdatItem::get()->getSalvageQuest(property.id) != 0); }

void GfItemUtil::getPropertyPrecious(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.preciousCategory = bdatItem->getPreciousCategory(property.id);
  property.preciousType = bdatItem->getPreciousType(property.id);
}

void GfItemUtil::getPropertyInfo(ItemProperty &property) {}

void GfItemUtil::getPropertyEvent(ItemProperty &property) {}

void GfItemUtil::getPropertyCollect(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.collectionCategory = bdatItem->getCollectionListCategory(property.id);
  property.zone = bdatItem->getCollectionListZone(property.id);
}

void GfItemUtil::getPropertyTresure(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.tresureCategory = bdatItem->getTresureCategory(property.id);
  property.tresureGraphic = bdatItem->getTresureGraphic(property.id);
  property.zone = bdatItem->getTresureZone(property.id);
  property.tresureFlag = bdatItem->getTresureFlag(property.id);
  property.flags.set(ItemProperty::FLAG_NO_MULTIPLE, bdatItem->getTresureNoMultiple(property.id) != 0);
}

void GfItemUtil::getPropertyFavorite(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.favoriteCategory = bdatItem->getFavoriteCategory(property.id);
  property.zone = bdatItem->getFavoriteZone(property.id);
  property.favoriteType = bdatItem->getFavoriteType(property.id);
  property.favoriteTime = bdatItem->getFavoriteTime(property.id);
}

void GfItemUtil::getPropertyCrystal(ItemProperty &property) {}

void GfItemUtil::getPropertyBooster(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.boosterCategory = bdatItem->getBoosterCategory(property.id);
  property.boosterIdea = bdatItem->getBoosterIdea(property.id);
}

void GfItemUtil::getPropertyHanaArts(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.enhance = bdatItem->getITM_HanaArtsEnhEnhance(property.id);
  property.condition = bdatItem->getITM_HanaArtsEnhCondition(property.id);
  property.needEther = bdatItem->getITM_HanaArtsEnhNeedEther(property.id);
  property.dustEther = bdatItem->getITM_HanaArtsEnhDustEther(property.id);
}

void GfItemUtil::getPropertyHanaAssist(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.enhance = bdatItem->getITM_HanaAssistEnhance(property.id);
  property.condition = bdatItem->getITM_HanaAssistCondition(property.id);
  property.needEther = bdatItem->getITM_HanaAssistNeedEther(property.id);
  property.dustEther = bdatItem->getITM_HanaAssistDustEther(property.id);
}

void GfItemUtil::getPropertyHanaAttribute(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.hanaAttribute = bdatItem->getITM_HanaAtrAtr(property.id);
  property.condition = bdatItem->getITM_HanaAtrCondition(property.id);
  property.needEther = bdatItem->getITM_HanaAtrNeedEther(property.id);
  property.dustEther = bdatItem->getITM_HanaAtrDustEther(property.id);
}

void GfItemUtil::getPropertyHanaNArts(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.nArts = bdatItem->getITM_HanaNArtsSetNArts(property.id);
  property.condition = bdatItem->getITM_HanaNArtsSetCondition(property.id);
  property.needEther = bdatItem->getITM_HanaNArtsSetNeedEther(property.id);
  property.dustEther = bdatItem->getITM_HanaNArtsSetDustEther(property.id);
}

void GfItemUtil::getPropertyHanaRole(ItemProperty &property) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  property.condition = bdatItem->getITM_HanaRoleCondition(property.id);
  property.needEther = bdatItem->getITM_HanaRoleNeedEther(property.id);
  property.dustEther = bdatItem->getITM_HanaRoleDustEther(property.id);
  property.hanaRole = bdatItem->getITM_HanaRoleRole(property.id);
  property.pArmor = bdatItem->getITM_HanaRolePArmor(property.id);
  property.eArmor = bdatItem->getITM_HanaRoleEArmor(property.id);
  property.hpMaxRev = bdatItem->getITM_HanaRoleHpMaxRev(property.id);
  property.strengthRev = bdatItem->getITM_HanaRoleStrengthRev(property.id);
  property.powEtherRev = bdatItem->getITM_HanaRolePowEtherRev(property.id);
  property.dexRev = bdatItem->getITM_HanaRoleDexRev(property.id);
  property.agilityRev = bdatItem->getITM_HanaRoleAgilityRev(property.id);
  property.luckRev = bdatItem->getITM_HanaRoleLuckRev(property.id);
}

bool GfItemUtil::getProperty(ItemProperty &property, u32 item, u32 shop) {
  property.clear();
  ItemType::Type type;
  u32 index;
  if (!GfDataItem::getItemType(type, index, item)) {
    return property.flags.test(ItemProperty::FLAG_VALID);
  }

  property.flags.set(ItemProperty::FLAG_VALID);
  property.id = item;
  property.index = index;
  property.type = type;
  property.count = getItemBoxCount(item);
  property.enableStock = getEnableStock(item);
  property.time = getItemTime(item);
  GfDataItem::getName(property.bdat, property.nameTextId, item);
  GfDataItem::getCaption(property.bdat, property.captionTextId, item);
  getPrice(property.price, item, shop);
  property.rarity = GfDataItem::getRarity(item);
  property.flags.set(ItemProperty::FLAG_NO_SELL, !GfDataItem::isEnableSell(item));

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
  return property.flags.test(ItemProperty::FLAG_VALID);
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

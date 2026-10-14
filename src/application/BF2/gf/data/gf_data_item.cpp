#include "gf/data/gf_data_item.h"
#include "bdat.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_PRECIOUS_NO_MULTIPLE = 0xc793,
  FLAG_CRYSTAL_LIST_NO_MULTIPLE = 0xc775,
};

enum {
  ITEM_HOMURA_COOK_FIRST = 0x9d44,
  ITEM_HOMURA_COOK_LAST = 0x9d4c,
  ITEM_MUSUBI_COOK_FIRST = 0x9d4d,
  ITEM_MUSUBI_COOK_LAST = 0x9d50,
  ITEM_TUKI_FIRST = 0x9d62,
  ITEM_TUKI_LAST = 0x9d66,
  ITEM_MUSUBI_COOK_EXTRA = 0x9d71,
  ITEM_MAY_FIRST = 0x9d73,
  ITEM_MAY_LAST = 0x9d77,
};

constexpr f32 SECONDS_PER_MINUTE = 60.0f;

bool GfDataItem::getName(u8 *&bdat, u32 &textId, u32 item) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  bdat = nullptr;
  textId = 0;

  ItemType::Type type = getItemType(item);

  switch (type) {
  case ItemType::PC_WPN_CHIP:
    if (bdatItem->getPcWpnChipsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getPcWpnChipName(item);
    bdat = GfBdatMsg::getFpPcWpnChip();
    break;

  case ItemType::PC_EQUIP:
    if (bdatItem->getPcEquipsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getPcEquipName(item);
    bdat = GfBdatMsg::getFpPcEquip();
    break;

  case ItemType::EQUIP_ORB:
    if (bdatItem->getEquipOrbsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getEquipOrbName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  case ItemType::PC_WPN:
    textId = bdatItem->getPcWpnName(item);
    bdat = GfBdatMsg::getFpPcWpn();
    break;

  case ItemType::SALVAGE:
    if (bdatItem->getSalvagesortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getSalvageName(item);
    bdat = GfBdatMsg::getFpSalvage();
    break;

  case ItemType::PRECIOUS:
    if (bdatItem->getPrecioussortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getPreciousName(item);
    bdat = GfBdatMsg::getFpPrecious();
    break;

  case ItemType::COLLECTION_LIST:
    if (bdatItem->getCollectionListsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getCollectionListName(item);
    bdat = GfBdatMsg::getFpCollection();
    break;

  case ItemType::TRESURE:
    if (bdatItem->getTresuresortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getTresureName(item);
    bdat = GfBdatMsg::getFpTresure();
    break;

  case ItemType::EMPTY_ORB:
    if (bdatItem->getEmptyOrbsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getEmptyOrbName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  case ItemType::FAVORITE:
    if (bdatItem->getFavoritesortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getFavoriteName(item);
    bdat = GfBdatMsg::getFpFavorite();
    break;

  case ItemType::CRYSTAL_LIST:
    if (bdatItem->getCrystalListsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getCrystalListName(item);
    bdat = GfBdatMsg::getFpCrystal();
    break;

  case ItemType::BOOSTER:
    if (bdatItem->getBoostersortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getBoosterName(item);
    bdat = GfBdatMsg::getFpBooster();
    break;

  case ItemType::HEAL_POT:
    textId = 0;
    bdat = nullptr;
    break;

  case ItemType::INFO:
    if (bdatItem->getInfosortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getInfoName(item);
    bdat = GfBdatMsg::getFpInfo();
    break;

  case ItemType::EVENT:
    if (bdatItem->getEventsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getEventName(item);
    bdat = GfBdatMsg::getFpEvent();
    break;

  case ItemType::HANA_ROLE:
    if (bdatItem->getITM_HanaRolesortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaRoleName(item);
    bdat = GfBdatMsg::getFpBtlHanaRole();
    break;

  case ItemType::HANA_ATR:
    if (bdatItem->getITM_HanaAtrsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaAtrName(item);
    bdat = GfBdatMsg::getFpBtlHanaAtr();
    break;

  case ItemType::HANA_ARTS_ENH:
    if (bdatItem->getITM_HanaArtsEnhsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaArtsEnhName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  case ItemType::HANA_N_ARTS_SET:
    if (bdatItem->getITM_HanaNArtsSetsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaNArtsSetName(item);
    bdat = GfBdatMsg::getFpBtlHanaNArts();
    break;

  case ItemType::HANA_ASSIST:
    if (bdatItem->getITM_HanaAssistsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaAssistName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  default:
    break;
  }

  return textId != 0 && bdat != nullptr;
}

ItemType::Type GfDataItem::getItemType(u32 item) {
  ItemType::Type type;
  u32 index;
  return getItemType(type, index, item) ? type : ItemType::NONE;
}

bool GfDataItem::getCaption(u8 *&bdat, u32 &textId, u32 item) {
  GfBdatItem *bdatItem = GfBdatItem::get();

  ItemType::Type type = getItemType(item);

  switch (type) {
  case ItemType::SALVAGE:
    textId = bdatItem->getSalvageCaption(item);
    bdat = GfBdatMsg::getFpSalvage();
    break;

  case ItemType::PRECIOUS:
    textId = bdatItem->getPreciousCaption(item);
    bdat = GfBdatMsg::getFpPrecious();
    return true;

  case ItemType::COLLECTION_LIST:
    textId = bdatItem->getCollectionListCaption(item);
    bdat = GfBdatMsg::getFpCollection();
    break;

  case ItemType::TRESURE:
    textId = bdatItem->getTresureCaption(item);
    bdat = GfBdatMsg::getFpTresure();
    break;

  case ItemType::FAVORITE:
    textId = bdatItem->getFavoriteCaption(item);
    bdat = GfBdatMsg::getFpFavorite();
    break;

  case ItemType::BOOSTER:
    textId = bdatItem->getBoosterCaption(item);
    bdat = GfBdatMsg::getFpBooster();
    break;

  case ItemType::INFO:
    textId = bdatItem->getInfoCaption(item);
    bdat = GfBdatMsg::getFpInfo();
    return true;

  case ItemType::EVENT:
    textId = bdatItem->getEventCaption(item);
    bdat = GfBdatMsg::getFpEvent();
    return true;

  default:
    break;
  }

  return textId != 0 && bdat != nullptr;
}

f32 GfDataItem::getFavoriteItemTime(u32 item) { return GfBdatItem::get()->getFavoriteTime(item) * SECONDS_PER_MINUTE; }

u32 GfDataItem::getFavoriteItemType(u32 item) { return GfBdatItem::get()->getFavoriteType(item); }

SDataItemBox *GfDataItem::getItemBox() { return &GfDataManager::getDataGame()->itemBox; }

bool GfDataItem::getItemType(ItemType::Type &type, u32 &index, u32 item) {
  if (item == 0) {
    return false;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  if (item < bdatItem->getPcEquipEnd()) {
    if (GfBdatItem::get()->getPcEquipArmorType(item) == 0) {
      type = ItemType::PC_EQUIP;
    }

    index = item - bdatItem->getPcEquipStart();
  } else if (item < bdatItem->getPcWpnEnd()) {
    type = ItemType::PC_WPN;
    index = item - bdatItem->getPcWpnStart();
  } else if (item < bdatItem->getPcWpnChipEnd()) {
    type = ItemType::PC_WPN_CHIP;
    index = item - bdatItem->getPcWpnChipStart();
  } else if (item < bdatItem->getEmptyOrbEnd()) {
    type = ItemType::EMPTY_ORB;
    index = item - bdatItem->getEmptyOrbStart();
  } else if (item < bdatItem->getEquipOrbEnd()) {
    type = ItemType::EQUIP_ORB;
    index = item - bdatItem->getEquipOrbStart();
  } else if (item < bdatItem->getSalvageEnd()) {
    type = ItemType::SALVAGE;
    index = item - bdatItem->getSalvageStart();
  } else if (item < bdatItem->getPreciousEnd()) {
    type = ItemType::PRECIOUS;
    index = item - bdatItem->getPreciousStart();
  } else if (item < bdatItem->getInfoEnd()) {
    type = ItemType::INFO;
    index = item - bdatItem->getInfoStart();
  } else if (item < bdatItem->getEventEnd()) {
    type = ItemType::EVENT;
    index = item - bdatItem->getEventStart();
  } else if (item < bdatItem->getCollectionListEnd()) {
    type = ItemType::COLLECTION_LIST;
    index = item - bdatItem->getCollectionListStart();
  } else if (item < bdatItem->getTresureEnd()) {
    type = ItemType::TRESURE;
    index = item - bdatItem->getTresureStart();
  } else if (item < bdatItem->getFavoriteEnd()) {
    type = ItemType::FAVORITE;
    index = item - bdatItem->getFavoriteStart();
  } else if (item < bdatItem->getCrystalListEnd()) {
    type = ItemType::CRYSTAL_LIST;
    index = item - bdatItem->getCrystalListStart();
  } else if (item < bdatItem->getBoosterEnd()) {
    type = ItemType::BOOSTER;
    index = item - bdatItem->getBoosterStart();
  } else if (item < bdatItem->getHealPotEnd()) {
    type = ItemType::HEAL_POT;
    index = item - bdatItem->getHealPotStart();
  } else if (item < bdatItem->getITM_HanaRoleEnd()) {
    type = ItemType::HANA_ROLE;
    index = item - bdatItem->getITM_HanaRoleStart();
  } else if (item < bdatItem->getITM_HanaAtrEnd()) {
    type = ItemType::HANA_ATR;
    index = item - bdatItem->getITM_HanaAtrStart();
  } else if (item < bdatItem->getITM_HanaArtsEnhEnd()) {
    type = ItemType::HANA_ARTS_ENH;
    index = item - bdatItem->getITM_HanaArtsEnhStart();
  } else if (item < bdatItem->getITM_HanaNArtsSetEnd()) {
    type = ItemType::HANA_N_ARTS_SET;
    index = item - bdatItem->getITM_HanaNArtsSetStart();
  } else if (item < bdatItem->getITM_HanaAssistEnd()) {
    type = ItemType::HANA_ASSIST;
    index = item - bdatItem->getITM_HanaAssistStart();
  } else {
    return false;
  }

  index++;
  return true;
}

bool GfDataItem::isEnableSell(u32 item) {
  ItemType::Type type = getItemType(item);
  GfBdatItem *bdatItem = GfBdatItem::get();
  bool enableSell = true;
  switch (type) {
  case ItemType::PC_WPN_CHIP:
    enableSell = !bdatItem->isPcWpnChipFlagNoSell(item);
    break;
  case ItemType::PC_EQUIP:
    enableSell = !bdatItem->isPcEquipFlagNoSell(item);
    break;
  case ItemType::EQUIP_ORB:
    enableSell = !bdatItem->isEquipOrbFlagNoSell(item);
    break;
  case ItemType::SALVAGE:
    enableSell = bdatItem->getSalvageNoSell(item) == 0;
    break;
  case ItemType::COLLECTION_LIST:
  case ItemType::TRESURE:
  case ItemType::FAVORITE:
  case ItemType::BOOSTER:
    break;
  case ItemType::EMPTY_ORB:
    enableSell = !bdatItem->isEmptyOrbFlagNoSell(item);
    break;
  case ItemType::CRYSTAL_LIST:
    enableSell = bdatItem->getCrystalListNoMultiple(item) == 0;
    break;
  default:
    enableSell = false;
    break;
  }

  return enableSell;
}

const char *GfDataItem::getName(u32 item) {
  u8 *bdat;
  u32 textId;
  const char *name = getName(bdat, textId, item) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (name == nullptr) {
    name = "";
  }

  return name;
}

const char *GfDataItem::getCaption(u32 item) {
  u8 *bdat;
  u32 textId;
  const char *caption = getCaption(bdat, textId, item) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (caption == nullptr) {
    caption = "";
  }

  return caption;
}

u32 GfDataItem::getItemStartID(ItemType::Type type) {
  u32 start;
  u32 end;
  return getItemBdatCount(start, end, type) ? start : 0;
}

bool GfDataItem::getItemBdatCount(u32 &start, u32 &end, ItemType::Type type) {
  start = 0;
  end = 0;

  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (type) {
  case ItemType::PC_WPN_CHIP:
    end = bdatItem->getPcWpnChipEnd();
    start = bdatItem->getPcWpnChipStart();
    break;
  case ItemType::PC_EQUIP:
    end = bdatItem->getPcEquipEnd();
    start = bdatItem->getPcEquipStart();
    break;
  case ItemType::EQUIP_ORB:
    end = bdatItem->getEquipOrbEnd();
    start = bdatItem->getEquipOrbStart();
    break;
  case ItemType::SALVAGE:
    end = bdatItem->getSalvageEnd();
    start = bdatItem->getSalvageStart();
    break;
  case ItemType::PRECIOUS:
    end = bdatItem->getPreciousEnd();
    start = bdatItem->getPreciousStart();
    break;
  case ItemType::COLLECTION_LIST:
    end = bdatItem->getCollectionListEnd();
    start = bdatItem->getCollectionListStart();
    break;
  case ItemType::TRESURE:
    end = bdatItem->getTresureEnd();
    start = bdatItem->getTresureStart();
    break;
  case ItemType::EMPTY_ORB:
    end = bdatItem->getEmptyOrbEnd();
    start = bdatItem->getEmptyOrbStart();
    break;
  case ItemType::FAVORITE:
    end = bdatItem->getFavoriteEnd();
    start = bdatItem->getFavoriteStart();
    break;
  case ItemType::CRYSTAL_LIST:
    end = bdatItem->getCrystalListEnd();
    start = bdatItem->getCrystalListStart();
    break;
  case ItemType::BOOSTER:
    end = bdatItem->getBoosterEnd();
    start = bdatItem->getBoosterStart();
    break;
  case ItemType::INFO:
    end = bdatItem->getInfoEnd();
    start = bdatItem->getInfoStart();
    break;
  case ItemType::EVENT:
    end = bdatItem->getEventEnd();
    start = bdatItem->getEventStart();
    break;
  case ItemType::HANA_ROLE:
    end = bdatItem->getITM_HanaRoleEnd();
    start = bdatItem->getITM_HanaRoleStart();
    break;
  case ItemType::HANA_ATR:
    end = bdatItem->getITM_HanaAtrEnd();
    start = bdatItem->getITM_HanaAtrStart();
    break;
  case ItemType::HANA_ARTS_ENH:
    end = bdatItem->getITM_HanaArtsEnhEnd();
    start = bdatItem->getITM_HanaArtsEnhStart();
    break;
  case ItemType::HANA_N_ARTS_SET:
    end = bdatItem->getITM_HanaNArtsSetEnd();
    start = bdatItem->getITM_HanaNArtsSetStart();
    break;
  case ItemType::HANA_ASSIST:
    end = bdatItem->getITM_HanaAssistEnd();
    start = bdatItem->getITM_HanaAssistStart();
    break;
  default:
    return false;
  }

  return true;
}

u32 GfDataItem::getItemBdatCount(ItemType::Type type) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  switch (type) {
  case ItemType::PC_WPN_CHIP:
    return bdatItem->getPcWpnChipEnd() - bdatItem->getPcWpnChipStart();
  case ItemType::PC_EQUIP:
    return bdatItem->getPcEquipEnd() - bdatItem->getPcEquipStart();
  case ItemType::EQUIP_ORB:
    return bdatItem->getEquipOrbEnd() - bdatItem->getEquipOrbStart();
  case ItemType::PC_WPN:
    return bdatItem->getPcWpnEnd() - bdatItem->getPcWpnStart();
  case ItemType::SALVAGE:
    return bdatItem->getSalvageEnd() - bdatItem->getSalvageStart();
  case ItemType::PRECIOUS:
    return bdatItem->getPreciousEnd() - bdatItem->getPreciousStart();
  case ItemType::COLLECTION_LIST:
    return bdatItem->getCollectionListEnd() - bdatItem->getCollectionListStart();
  case ItemType::TRESURE:
    return bdatItem->getTresureEnd() - bdatItem->getTresureStart();
  case ItemType::EMPTY_ORB:
    return bdatItem->getEmptyOrbEnd() - bdatItem->getEmptyOrbStart();
  case ItemType::FAVORITE:
    return bdatItem->getFavoriteEnd() - bdatItem->getFavoriteStart();
  case ItemType::CRYSTAL_LIST:
    return bdatItem->getCrystalListEnd() - bdatItem->getCrystalListStart();
  case ItemType::BOOSTER:
    return bdatItem->getBoosterEnd() - bdatItem->getBoosterStart();
  case ItemType::HEAL_POT:
    return bdatItem->getHealPotEnd() - bdatItem->getHealPotStart();
  case ItemType::INFO:
    return bdatItem->getInfoEnd() - bdatItem->getInfoStart();
  case ItemType::EVENT:
    return bdatItem->getEventEnd() - bdatItem->getEventStart();
  case ItemType::HANA_ROLE:
    return bdatItem->getITM_HanaRoleEnd() - bdatItem->getITM_HanaRoleStart();
  case ItemType::HANA_ATR:
    return bdatItem->getITM_HanaAtrEnd() - bdatItem->getITM_HanaAtrStart();
  case ItemType::HANA_ARTS_ENH:
    return bdatItem->getITM_HanaArtsEnhEnd() - bdatItem->getITM_HanaArtsEnhStart();
  case ItemType::HANA_N_ARTS_SET:
    return bdatItem->getITM_HanaNArtsSetEnd() - bdatItem->getITM_HanaNArtsSetStart();
  case ItemType::HANA_ASSIST:
    return bdatItem->getITM_HanaAssistEnd() - bdatItem->getITM_HanaAssistStart();
  default:
    return 0;
  }
}

u32 GfDataItem::getPrice(u32 item) {
  ItemType::Type type = getItemType(item);
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 price = 0;
  switch (type) {
  case ItemType::PC_WPN_CHIP:
    price = bdatItem->getPcWpnChipPrice(item);
    break;
  case ItemType::PC_EQUIP:
    price = bdatItem->getPcEquipPrice(item);
    break;
  case ItemType::EQUIP_ORB:
    price = bdatItem->getEquipOrbPrice(item);
    break;
  case ItemType::SALVAGE:
    price = bdatItem->getSalvagePrice(item);
    break;
  case ItemType::PRECIOUS:
    price = bdatItem->getPreciousPrice(item);
    break;
  case ItemType::COLLECTION_LIST:
    price = bdatItem->getCollectionListPrice(item);
    break;
  case ItemType::TRESURE:
    price = bdatItem->getTresurePrice(item);
    break;
  case ItemType::EMPTY_ORB:
    price = bdatItem->getEmptyOrbPrice(item);
    break;
  case ItemType::FAVORITE:
    price = bdatItem->getFavoritePrice(item);
    break;
  case ItemType::CRYSTAL_LIST:
    price = bdatItem->getCrystalListPrice(item);
    break;
  case ItemType::BOOSTER:
    price = bdatItem->getBoosterPrice(item);
    break;
  case ItemType::INFO:
    price = bdatItem->getInfoPrice(item);
    break;
  default:
    break;
  }

  return price;
}

u32 GfDataItem::getRarity(u32 item) {
  ItemType::Type type = getItemType(item);
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 rarity = 0;
  switch (type) {
  case ItemType::PC_WPN_CHIP:
    rarity = bdatItem->getPcWpnChipRarity(item);
    break;
  case ItemType::PC_EQUIP:
    rarity = bdatItem->getPcEquipRarity(item);
    break;
  case ItemType::EQUIP_ORB:
    rarity = bdatItem->getEquipOrbRarity(item);
    break;
  case ItemType::SALVAGE:
    rarity = bdatItem->getSalvageRarity(item);
    break;
  case ItemType::COLLECTION_LIST:
    rarity = bdatItem->getCollectionListRarity(item);
    break;
  case ItemType::TRESURE:
    rarity = bdatItem->getTresureRarity(item);
    break;
  case ItemType::EMPTY_ORB:
    rarity = bdatItem->getEmptyOrbRarity(item);
    break;
  case ItemType::FAVORITE:
    rarity = bdatItem->getFavoriteRarity(item);
    break;
  case ItemType::CRYSTAL_LIST:
    rarity = bdatItem->getCrystalListRarity(item);
    break;
  case ItemType::BOOSTER:
    rarity = bdatItem->getBoosterRarity(item);
    break;
  default:
    break;
  }

  return rarity;
}

u32 GfDataItem::getCategory(u32 item) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 category = 0;
  switch (getItemType(item)) {
  case ItemType::PRECIOUS:
  case ItemType::CRYSTAL_LIST:
    category = bdatItem->getPreciousCategory(item);
    break;
  case ItemType::COLLECTION_LIST:
    category = bdatItem->getCollectionListCategory(item);
    break;
  case ItemType::TRESURE:
    category = bdatItem->getTresureCategory(item);
    break;
  case ItemType::FAVORITE:
    category = bdatItem->getFavoriteCategory(item);
    break;
  case ItemType::BOOSTER:
    category = bdatItem->getBoosterCategory(item);
    break;
  default:
    break;
  }

  return category;
}

ItemType::Type GfDataItem::getTypeByItemCategory(u32 category) {
  if (category < 4) {
    return ItemType::CRYSTAL_LIST;
  }

  if (category < 12) {
    return ItemType::COLLECTION_LIST;
  }

  if (category < 24) {
    return ItemType::FAVORITE;
  }

  if (category < 28) {
    return ItemType::TRESURE;
  }

  if (category < 30) {
    return ItemType::PRECIOUS;
  }

  return ItemType::NONE;
}

bool GfDataItem::isNoMultiple(u32 item) {
  ItemType::Type type = getItemType(item);
  if (type == ItemType::CRYSTAL_LIST) {
    u32 noMultiple = GfBdatItem::get()->getCrystalListNoMultiple(item);
    if (noMultiple == 0) {
      return false;
    }

    return GfGameFlag::getLocal(1, FLAG_CRYSTAL_LIST_NO_MULTIPLE + noMultiple) != 0;
  }

  if (type == ItemType::PRECIOUS) {
    u32 noMultiple = GfBdatItem::get()->getPreciousNoMultiple(item);
    if (noMultiple == 0) {
      return false;
    }

    return GfGameFlag::getLocal(1, FLAG_PRECIOUS_NO_MULTIPLE + noMultiple) != 0;
  }

  return false;
}

void GfDataItem::setNoMultiple(u32 item, bool noMultiple) {
  ItemType::Type type = getItemType(item);
  if (type == ItemType::CRYSTAL_LIST) {
    u32 noMultipleIndex = GfBdatItem::get()->getCrystalListNoMultiple(item);
    if (noMultipleIndex == 0) {
      return;
    }

    GfGameFlag::setLocal(1, FLAG_CRYSTAL_LIST_NO_MULTIPLE + noMultipleIndex, noMultiple);
    return;
  }

  if (type == ItemType::PRECIOUS) {
    u32 noMultipleIndex = GfBdatItem::get()->getPreciousNoMultiple(item);
    if (noMultipleIndex == 0) {
      return;
    }

    GfGameFlag::setLocal(1, FLAG_PRECIOUS_NO_MULTIPLE + noMultipleIndex, noMultiple);
  }
}

bool GfDataItem::isFavoriteCategoryFood(u32 category) { return category >= FAVORITE_CATEGORY_FOOD_FIRST && category <= FAVORITE_CATEGORY_FOOD_LAST; }

bool GfDataItem::isHomuraCookItem(u32 item) { return item >= ITEM_HOMURA_COOK_FIRST && item <= ITEM_HOMURA_COOK_LAST; }

bool GfDataItem::isMusubiCookItem(u32 item) {
  switch (item) {
  case ITEM_MUSUBI_COOK_FIRST:
  case ITEM_MUSUBI_COOK_FIRST + 1:
  case ITEM_MUSUBI_COOK_FIRST + 2:
  case ITEM_MUSUBI_COOK_LAST:
  case ITEM_MUSUBI_COOK_EXTRA:
    return true;
  default:
    return false;
  }
}

bool GfDataItem::isMayItem(u32 item) { return item >= ITEM_MAY_FIRST && item <= ITEM_MAY_LAST; }

bool GfDataItem::isTukiItem(u32 item) { return item >= ITEM_TUKI_FIRST && item <= ITEM_TUKI_LAST; }

} // namespace gf

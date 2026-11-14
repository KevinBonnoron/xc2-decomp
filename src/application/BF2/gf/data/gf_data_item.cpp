#include "gf/data/gf_data_item.h"

#include "bdat.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_time.h"

namespace gf {

enum {
  FLAG_UNKNOWN_51091 = 0xc793, // Inferred role: flag precious no multiple; original name unknown.
  FLAG_UNKNOWN_51061 = 0xc775, // Inferred role: flag crystal list no multiple; original name unknown.
};

enum {
  ITEM_UNKNOWN_40260 = 0x9d44, // Inferred role: item homura cook first; original name unknown.
  ITEM_UNKNOWN_40268 = 0x9d4c, // Inferred role: item homura cook last; original name unknown.
  ITEM_UNKNOWN_40269 = 0x9d4d, // Inferred role: item musubi cook first; original name unknown.
  ITEM_UNKNOWN_40272 = 0x9d50, // Inferred role: item musubi cook last; original name unknown.
  ITEM_UNKNOWN_40290 = 0x9d62, // Inferred role: item tuki first; original name unknown.
  ITEM_UNKNOWN_40294 = 0x9d66, // Inferred role: item tuki last; original name unknown.
  ITEM_UNKNOWN_40305 = 0x9d71, // Inferred role: item musubi cook extra; original name unknown.
  ITEM_UNKNOWN_40307 = 0x9d73, // Inferred role: item may first; original name unknown.
  ITEM_UNKNOWN_40311 = 0x9d77, // Inferred role: item may last; original name unknown.
};

bool GfDataItem::getName(u8 *&bdat, u32 &textId, u32 item) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  bdat = nullptr;
  textId = 0;

  ItemType::Type type = getItemType(item);

  switch (type) {
  case ItemType::ITEM_TYPE_UNKNOWN_1:
    if (bdatItem->getPcWpnChipsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getPcWpnChipName(item);
    bdat = GfBdatMsg::getFpPcWpnChip();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_2:
    if (bdatItem->getPcEquipsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getPcEquipName(item);
    bdat = GfBdatMsg::getFpPcEquip();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_3:
    if (bdatItem->getEquipOrbsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getEquipOrbName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_4:
    textId = bdatItem->getPcWpnName(item);
    bdat = GfBdatMsg::getFpPcWpn();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_5:
    if (bdatItem->getSalvagesortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getSalvageName(item);
    bdat = GfBdatMsg::getFpSalvage();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_6:
    if (bdatItem->getPrecioussortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getPreciousName(item);
    bdat = GfBdatMsg::getFpPrecious();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_7:
    if (bdatItem->getCollectionListsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getCollectionListName(item);
    bdat = GfBdatMsg::getFpCollection();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_8:
    if (bdatItem->getTresuresortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getTresureName(item);
    bdat = GfBdatMsg::getFpTresure();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_9:
    if (bdatItem->getEmptyOrbsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getEmptyOrbName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_10:
    if (bdatItem->getFavoritesortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getFavoriteName(item);
    bdat = GfBdatMsg::getFpFavorite();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_11:
    if (bdatItem->getCrystalListsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getCrystalListName(item);
    bdat = GfBdatMsg::getFpCrystal();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_12:
    if (bdatItem->getBoostersortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getBoosterName(item);
    bdat = GfBdatMsg::getFpBooster();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_13:
    textId = 0;
    bdat = nullptr;
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_14:
    if (bdatItem->getInfosortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getInfoName(item);
    bdat = GfBdatMsg::getFpInfo();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_15:
    if (bdatItem->getEventsortJP(item) == 0) {
      break;
    }

    textId = bdatItem->getEventName(item);
    bdat = GfBdatMsg::getFpEvent();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_16:
    if (bdatItem->getITM_HanaRolesortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaRoleName(item);
    bdat = GfBdatMsg::getFpBtlHanaRole();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_17:
    if (bdatItem->getITM_HanaAtrsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaAtrName(item);
    bdat = GfBdatMsg::getFpBtlHanaAtr();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_18:
    if (bdatItem->getITM_HanaArtsEnhsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaArtsEnhName(item);
    bdat = GfBdatMsg::getFpOrb();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_19:
    if (bdatItem->getITM_HanaNArtsSetsortJP(item) == 0) {
      break;
    }

    textId = GfBdatItem::get()->getITM_HanaNArtsSetName(item);
    bdat = GfBdatMsg::getFpBtlHanaNArts();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_20:
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
  return getItemType(type, index, item) ? type : ItemType::ITEM_TYPE_UNKNOWN_0;
}

bool GfDataItem::getCaption(u8 *&bdat, u32 &textId, u32 item) {
  GfBdatItem *bdatItem = GfBdatItem::get();

  ItemType::Type type = getItemType(item);

  switch (type) {
  case ItemType::ITEM_TYPE_UNKNOWN_5:
    textId = bdatItem->getSalvageCaption(item);
    bdat = GfBdatMsg::getFpSalvage();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_6:
    textId = bdatItem->getPreciousCaption(item);
    bdat = GfBdatMsg::getFpPrecious();
    return true;

  case ItemType::ITEM_TYPE_UNKNOWN_7:
    textId = bdatItem->getCollectionListCaption(item);
    bdat = GfBdatMsg::getFpCollection();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_8:
    textId = bdatItem->getTresureCaption(item);
    bdat = GfBdatMsg::getFpTresure();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_10:
    textId = bdatItem->getFavoriteCaption(item);
    bdat = GfBdatMsg::getFpFavorite();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_12:
    textId = bdatItem->getBoosterCaption(item);
    bdat = GfBdatMsg::getFpBooster();
    break;

  case ItemType::ITEM_TYPE_UNKNOWN_14:
    textId = bdatItem->getInfoCaption(item);
    bdat = GfBdatMsg::getFpInfo();
    return true;

  case ItemType::ITEM_TYPE_UNKNOWN_15:
    textId = bdatItem->getEventCaption(item);
    bdat = GfBdatMsg::getFpEvent();
    return true;

  default:
    break;
  }

  return textId != 0 && bdat != nullptr;
}

f32 GfDataItem::getFavoriteItemTime(u32 item) { return GfBdatItem::get()->getFavoriteTime(item) * static_cast<f32>(SECONDS_UNKNOWN_60); }

u32 GfDataItem::getFavoriteItemType(u32 item) { return GfBdatItem::get()->getFavoriteType(item); }

ItemBox *GfDataItem::getItemBox() { return &GfDataManager::getDataGame()->unknowne98d8; }

bool GfDataItem::getItemType(ItemType::Type &type, u32 &index, u32 item) {
  if (item == 0) {
    return false;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  if (item < bdatItem->getPcEquipEnd()) {
    if (GfBdatItem::get()->getPcEquipArmorType(item) == 0) {
      type = ItemType::ITEM_TYPE_UNKNOWN_2;
    }

    index = item - bdatItem->getPcEquipStart();
  } else if (item < bdatItem->getPcWpnEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_4;
    index = item - bdatItem->getPcWpnStart();
  } else if (item < bdatItem->getPcWpnChipEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_1;
    index = item - bdatItem->getPcWpnChipStart();
  } else if (item < bdatItem->getEmptyOrbEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_9;
    index = item - bdatItem->getEmptyOrbStart();
  } else if (item < bdatItem->getEquipOrbEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_3;
    index = item - bdatItem->getEquipOrbStart();
  } else if (item < bdatItem->getSalvageEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_5;
    index = item - bdatItem->getSalvageStart();
  } else if (item < bdatItem->getPreciousEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_6;
    index = item - bdatItem->getPreciousStart();
  } else if (item < bdatItem->getInfoEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_14;
    index = item - bdatItem->getInfoStart();
  } else if (item < bdatItem->getEventEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_15;
    index = item - bdatItem->getEventStart();
  } else if (item < bdatItem->getCollectionListEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_7;
    index = item - bdatItem->getCollectionListStart();
  } else if (item < bdatItem->getTresureEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_8;
    index = item - bdatItem->getTresureStart();
  } else if (item < bdatItem->getFavoriteEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_10;
    index = item - bdatItem->getFavoriteStart();
  } else if (item < bdatItem->getCrystalListEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_11;
    index = item - bdatItem->getCrystalListStart();
  } else if (item < bdatItem->getBoosterEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_12;
    index = item - bdatItem->getBoosterStart();
  } else if (item < bdatItem->getHealPotEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_13;
    index = item - bdatItem->getHealPotStart();
  } else if (item < bdatItem->getITM_HanaRoleEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_16;
    index = item - bdatItem->getITM_HanaRoleStart();
  } else if (item < bdatItem->getITM_HanaAtrEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_17;
    index = item - bdatItem->getITM_HanaAtrStart();
  } else if (item < bdatItem->getITM_HanaArtsEnhEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_18;
    index = item - bdatItem->getITM_HanaArtsEnhStart();
  } else if (item < bdatItem->getITM_HanaNArtsSetEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_19;
    index = item - bdatItem->getITM_HanaNArtsSetStart();
  } else if (item < bdatItem->getITM_HanaAssistEnd()) {
    type = ItemType::ITEM_TYPE_UNKNOWN_20;
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
  case ItemType::ITEM_TYPE_UNKNOWN_1:
    enableSell = !bdatItem->isPcWpnChipFlagNoSell(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_2:
    enableSell = !bdatItem->isPcEquipFlagNoSell(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_3:
    enableSell = !bdatItem->isEquipOrbFlagNoSell(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_5:
    enableSell = bdatItem->getSalvageNoSell(item) == 0;
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_7:
  case ItemType::ITEM_TYPE_UNKNOWN_8:
  case ItemType::ITEM_TYPE_UNKNOWN_10:
  case ItemType::ITEM_TYPE_UNKNOWN_12:
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_9:
    enableSell = !bdatItem->isEmptyOrbFlagNoSell(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_11:
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
  case ItemType::ITEM_TYPE_UNKNOWN_1:
    end = bdatItem->getPcWpnChipEnd();
    start = bdatItem->getPcWpnChipStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_2:
    end = bdatItem->getPcEquipEnd();
    start = bdatItem->getPcEquipStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_3:
    end = bdatItem->getEquipOrbEnd();
    start = bdatItem->getEquipOrbStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_5:
    end = bdatItem->getSalvageEnd();
    start = bdatItem->getSalvageStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_6:
    end = bdatItem->getPreciousEnd();
    start = bdatItem->getPreciousStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_7:
    end = bdatItem->getCollectionListEnd();
    start = bdatItem->getCollectionListStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_8:
    end = bdatItem->getTresureEnd();
    start = bdatItem->getTresureStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_9:
    end = bdatItem->getEmptyOrbEnd();
    start = bdatItem->getEmptyOrbStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_10:
    end = bdatItem->getFavoriteEnd();
    start = bdatItem->getFavoriteStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_11:
    end = bdatItem->getCrystalListEnd();
    start = bdatItem->getCrystalListStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_12:
    end = bdatItem->getBoosterEnd();
    start = bdatItem->getBoosterStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_14:
    end = bdatItem->getInfoEnd();
    start = bdatItem->getInfoStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_15:
    end = bdatItem->getEventEnd();
    start = bdatItem->getEventStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_16:
    end = bdatItem->getITM_HanaRoleEnd();
    start = bdatItem->getITM_HanaRoleStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_17:
    end = bdatItem->getITM_HanaAtrEnd();
    start = bdatItem->getITM_HanaAtrStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_18:
    end = bdatItem->getITM_HanaArtsEnhEnd();
    start = bdatItem->getITM_HanaArtsEnhStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_19:
    end = bdatItem->getITM_HanaNArtsSetEnd();
    start = bdatItem->getITM_HanaNArtsSetStart();
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_20:
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
  case ItemType::ITEM_TYPE_UNKNOWN_1:
    return bdatItem->getPcWpnChipEnd() - bdatItem->getPcWpnChipStart();
  case ItemType::ITEM_TYPE_UNKNOWN_2:
    return bdatItem->getPcEquipEnd() - bdatItem->getPcEquipStart();
  case ItemType::ITEM_TYPE_UNKNOWN_3:
    return bdatItem->getEquipOrbEnd() - bdatItem->getEquipOrbStart();
  case ItemType::ITEM_TYPE_UNKNOWN_4:
    return bdatItem->getPcWpnEnd() - bdatItem->getPcWpnStart();
  case ItemType::ITEM_TYPE_UNKNOWN_5:
    return bdatItem->getSalvageEnd() - bdatItem->getSalvageStart();
  case ItemType::ITEM_TYPE_UNKNOWN_6:
    return bdatItem->getPreciousEnd() - bdatItem->getPreciousStart();
  case ItemType::ITEM_TYPE_UNKNOWN_7:
    return bdatItem->getCollectionListEnd() - bdatItem->getCollectionListStart();
  case ItemType::ITEM_TYPE_UNKNOWN_8:
    return bdatItem->getTresureEnd() - bdatItem->getTresureStart();
  case ItemType::ITEM_TYPE_UNKNOWN_9:
    return bdatItem->getEmptyOrbEnd() - bdatItem->getEmptyOrbStart();
  case ItemType::ITEM_TYPE_UNKNOWN_10:
    return bdatItem->getFavoriteEnd() - bdatItem->getFavoriteStart();
  case ItemType::ITEM_TYPE_UNKNOWN_11:
    return bdatItem->getCrystalListEnd() - bdatItem->getCrystalListStart();
  case ItemType::ITEM_TYPE_UNKNOWN_12:
    return bdatItem->getBoosterEnd() - bdatItem->getBoosterStart();
  case ItemType::ITEM_TYPE_UNKNOWN_13:
    return bdatItem->getHealPotEnd() - bdatItem->getHealPotStart();
  case ItemType::ITEM_TYPE_UNKNOWN_14:
    return bdatItem->getInfoEnd() - bdatItem->getInfoStart();
  case ItemType::ITEM_TYPE_UNKNOWN_15:
    return bdatItem->getEventEnd() - bdatItem->getEventStart();
  case ItemType::ITEM_TYPE_UNKNOWN_16:
    return bdatItem->getITM_HanaRoleEnd() - bdatItem->getITM_HanaRoleStart();
  case ItemType::ITEM_TYPE_UNKNOWN_17:
    return bdatItem->getITM_HanaAtrEnd() - bdatItem->getITM_HanaAtrStart();
  case ItemType::ITEM_TYPE_UNKNOWN_18:
    return bdatItem->getITM_HanaArtsEnhEnd() - bdatItem->getITM_HanaArtsEnhStart();
  case ItemType::ITEM_TYPE_UNKNOWN_19:
    return bdatItem->getITM_HanaNArtsSetEnd() - bdatItem->getITM_HanaNArtsSetStart();
  case ItemType::ITEM_TYPE_UNKNOWN_20:
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
  case ItemType::ITEM_TYPE_UNKNOWN_1:
    price = bdatItem->getPcWpnChipPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_2:
    price = bdatItem->getPcEquipPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_3:
    price = bdatItem->getEquipOrbPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_5:
    price = bdatItem->getSalvagePrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_6:
    price = bdatItem->getPreciousPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_7:
    price = bdatItem->getCollectionListPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_8:
    price = bdatItem->getTresurePrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_9:
    price = bdatItem->getEmptyOrbPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_10:
    price = bdatItem->getFavoritePrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_11:
    price = bdatItem->getCrystalListPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_12:
    price = bdatItem->getBoosterPrice(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_14:
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
  case ItemType::ITEM_TYPE_UNKNOWN_1:
    rarity = bdatItem->getPcWpnChipRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_2:
    rarity = bdatItem->getPcEquipRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_3:
    rarity = bdatItem->getEquipOrbRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_5:
    rarity = bdatItem->getSalvageRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_7:
    rarity = bdatItem->getCollectionListRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_8:
    rarity = bdatItem->getTresureRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_9:
    rarity = bdatItem->getEmptyOrbRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_10:
    rarity = bdatItem->getFavoriteRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_11:
    rarity = bdatItem->getCrystalListRarity(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_12:
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
  case ItemType::ITEM_TYPE_UNKNOWN_6:
  case ItemType::ITEM_TYPE_UNKNOWN_11:
    category = bdatItem->getPreciousCategory(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_7:
    category = bdatItem->getCollectionListCategory(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_8:
    category = bdatItem->getTresureCategory(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_10:
    category = bdatItem->getFavoriteCategory(item);
    break;
  case ItemType::ITEM_TYPE_UNKNOWN_12:
    category = bdatItem->getBoosterCategory(item);
    break;
  default:
    break;
  }

  return category;
}

ItemType::Type GfDataItem::getTypeByItemCategory(u32 category) {
  if (category < 4) {
    return ItemType::ITEM_TYPE_UNKNOWN_11;
  }

  if (category < 12) {
    return ItemType::ITEM_TYPE_UNKNOWN_7;
  }

  if (category < 24) {
    return ItemType::ITEM_TYPE_UNKNOWN_10;
  }

  if (category < 28) {
    return ItemType::ITEM_TYPE_UNKNOWN_8;
  }

  if (category < 30) {
    return ItemType::ITEM_TYPE_UNKNOWN_6;
  }

  return ItemType::ITEM_TYPE_UNKNOWN_0;
}

bool GfDataItem::isNoMultiple(u32 item) {
  ItemType::Type type = getItemType(item);
  if (type == ItemType::ITEM_TYPE_UNKNOWN_11) {
    u32 noMultiple = GfBdatItem::get()->getCrystalListNoMultiple(item);
    if (noMultiple == 0) {
      return false;
    }

    return GfGameFlag::getLocal(1, FLAG_UNKNOWN_51061 + noMultiple) != 0;
  }

  if (type == ItemType::ITEM_TYPE_UNKNOWN_6) {
    u32 noMultiple = GfBdatItem::get()->getPreciousNoMultiple(item);
    if (noMultiple == 0) {
      return false;
    }

    return GfGameFlag::getLocal(1, FLAG_UNKNOWN_51091 + noMultiple) != 0;
  }

  return false;
}

void GfDataItem::setNoMultiple(u32 item, bool noMultiple) {
  ItemType::Type type = getItemType(item);
  if (type == ItemType::ITEM_TYPE_UNKNOWN_11) {
    u32 noMultipleIndex = GfBdatItem::get()->getCrystalListNoMultiple(item);
    if (noMultipleIndex == 0) {
      return;
    }

    GfGameFlag::setLocal(1, FLAG_UNKNOWN_51061 + noMultipleIndex, noMultiple);
    return;
  }

  if (type == ItemType::ITEM_TYPE_UNKNOWN_6) {
    u32 noMultipleIndex = GfBdatItem::get()->getPreciousNoMultiple(item);
    if (noMultipleIndex == 0) {
      return;
    }

    GfGameFlag::setLocal(1, FLAG_UNKNOWN_51091 + noMultipleIndex, noMultiple);
  }
}

bool GfDataItem::isFavoriteCategoryFood(u32 category) { return category >= FAVORITE_CATEGORY_FOOD_UNKNOWN_12 && category <= FAVORITE_CATEGORY_FOOD_UNKNOWN_17; }

bool GfDataItem::isHomuraCookItem(u32 item) { return item >= ITEM_UNKNOWN_40260 && item <= ITEM_UNKNOWN_40268; }

bool GfDataItem::isMusubiCookItem(u32 item) {
  switch (item) {
  case ITEM_UNKNOWN_40269:
  case ITEM_UNKNOWN_40269 + 1:
  case ITEM_UNKNOWN_40269 + 2:
  case ITEM_UNKNOWN_40272:
  case ITEM_UNKNOWN_40305:
    return true;
  default:
    return false;
  }
}

bool GfDataItem::isMayItem(u32 item) { return item >= ITEM_UNKNOWN_40307 && item <= ITEM_UNKNOWN_40311; }

bool GfDataItem::isTukiItem(u32 item) { return item >= ITEM_UNKNOWN_40290 && item <= ITEM_UNKNOWN_40294; }

} // namespace gf

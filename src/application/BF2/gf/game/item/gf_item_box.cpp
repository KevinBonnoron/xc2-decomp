#include "gf/game/item/gf_item_box.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_time.h"
#include "gf/util/gf_item_util.h"

namespace gf {

enum {
  ITEM_TYPE_LIMIT = 64,
  ITEM_SERIAL_MASK = 0x3ffffff,
};

namespace _gfit {

GfItemBox *s_pItemBox;
GfPoolItemBox *s_pItemBoxP;

} // namespace _gfit

static ITEM_BOX_INDEX getItemBoxIndex(ItemType::Type type) {
  switch (type) {
  case ItemType::PC_WPN_CHIP:
    return ITEM_BOX_INDEX_PC_WPN_CHIP;
  case ItemType::PC_EQUIP:
    return ITEM_BOX_INDEX_PC_EQUIP;
  case ItemType::EQUIP_ORB:
    return ITEM_BOX_INDEX_EQUIP_ORB;
  case ItemType::SALVAGE:
    return ITEM_BOX_INDEX_SALVAGE;
  case ItemType::PRECIOUS:
    return ITEM_BOX_INDEX_PRECIOUS;
  case ItemType::COLLECTION_LIST:
    return ITEM_BOX_INDEX_COLLECTION_LIST;
  case ItemType::TRESURE:
    return ITEM_BOX_INDEX_TRESURE;
  case ItemType::EMPTY_ORB:
    return ITEM_BOX_INDEX_EMPTY_ORB;
  case ItemType::FAVORITE:
    return ITEM_BOX_INDEX_FAVORITE;
  case ItemType::CRYSTAL_LIST:
    return ITEM_BOX_INDEX_CRYSTAL_LIST;
  case ItemType::BOOSTER:
    return ITEM_BOX_INDEX_BOOSTER;
  case ItemType::INFO:
    return ITEM_BOX_INDEX_INFO;
  case ItemType::EVENT:
    return ITEM_BOX_INDEX_EVENT;
  case ItemType::HANA_ROLE:
    return ITEM_BOX_INDEX_HANA_ROLE;
  case ItemType::HANA_ATR:
    return ITEM_BOX_INDEX_HANA_ATR;
  case ItemType::HANA_ARTS_ENH:
    return ITEM_BOX_INDEX_HANA_ARTS_ENH;
  case ItemType::HANA_N_ARTS_SET:
    return ITEM_BOX_INDEX_HANA_N_ARTS_SET;
  case ItemType::HANA_ASSIST:
    return ITEM_BOX_INDEX_HANA_ASSIST;
  default:
    return ITEM_BOX_INDEX_NONE;
  }
}

template <u32 N>
static void setItems(GfItemBoxBase *itemBoxBase, ItemBox *itemBox, u32 index, SDataItemInfo (&items)[N], u32 maxStock, bool isMulti) {
  itemBoxBase->setItemTypeInfo(
      itemBox, index, static_cast<GfItemInfo *>(items), static_cast<GfItemInfo *>(items + N), N, sizeof(GfItemInfo), maxStock, isMulti);
}

item_iterator item_iterator::operator++() {
  GfItemInfo *last = box->getItemTypeInfo(type)->last;
  if (current != last) {
    do {
      current = reinterpret_cast<GfItemInfo *>(reinterpret_cast<u8 *>(current) + itemSize);
    } while (current != last && current->index != 0 && current->getType() != type);
  }
  return *this;
}

item_iterator GfItemBoxBase::end(ItemType::Type type) {
  ItemTypeInfo *info = getItemTypeInfo(type);
  return item_iterator(this, info->last, info->itemSize, info->isMulti, type);
}

ItemType::Type GfItemInfo::getType() const { return static_cast<ItemType::Type>(type); }

GfItemBoxBase::GfItemBoxBase() : mItemBox(nullptr) {}

void GfItemBoxBase::setItemBox(ItemBox *itemBox, bool isClear) {
  mItemBox = itemBox;
  if (itemBox == nullptr) {
    return;
  }

  if (isClear) {
    __builtin_memset(itemBox, 0, sizeof(ItemBox));
  }
  setItems(this, itemBox, ITEM_BOX_INDEX_PC_WPN_CHIP, itemBox->pcWpnChips, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_PC_EQUIP, itemBox->pcEquips, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_EQUIP_ORB, itemBox->equipOrbs, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_SALVAGE, itemBox->salvages, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_PRECIOUS, itemBox->preciouses, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_INFO, itemBox->infos, 1, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_EVENT, itemBox->events, 1, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_COLLECTION_LIST, itemBox->collectionLists, 999, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_TRESURE, itemBox->tresures, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_EMPTY_ORB, itemBox->emptyOrbs, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_FAVORITE, itemBox->favorites, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_CRYSTAL_LIST, itemBox->crystalLists, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_BOOSTER, itemBox->boosters, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ROLE, itemBox->hanaRoles, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ATR, itemBox->hanaAtrs, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ARTS_ENH, itemBox->hanaArtsEnhs, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_N_ARTS_SET, itemBox->hanaNArtsSets, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ASSIST, itemBox->hanaAssists, 1, false);
}

void GfItemBoxBase::setItemTypeInfo(ItemBox *itemBox, u32 index, GfItemInfo *first, GfItemInfo *last, u32 capacity, u32 itemSize, u32 maxStock,
                                    bool isMulti) {
  ItemTypeInfo &info = mItemTypeInfos[index];
  info.first = first;
  info.last = last;
  info.capacity = capacity;
  info.itemSize = itemSize;
  info.maxStock = maxStock;
  info.isMulti = isMulti;
  setSerialInfo(itemBox, index);
}

void GfItemBoxBase::setupSerial(ItemBox *itemBox) {
  if (itemBox == nullptr) {
    return;
  }

  for (u32 index = ITEM_BOX_INDEX_PC_WPN_CHIP; index < ITEM_BOX_INDEX_NUM; index++) {
    setSerialInfo(itemBox, index);
  }
}

void GfItemBoxBase::setSerialInfo(ItemBox *itemBox, u32 index) { mItemTypeInfos[index].serial = &itemBox->serials[index]; }

ItemTypeInfo *GfItemBoxBase::getItemTypeInfo(ItemType::Type type) { return &mItemTypeInfos[getItemBoxIndex(type)]; }

const ItemTypeInfo *GfItemBoxBase::getItemTypeInfo(ItemType::Type type) const { return &mItemTypeInfos[getItemBoxIndex(type)]; }

item_iterator GfItemBoxBase::begin(ItemType::Type type) {
  if (type >= ITEM_TYPE_LIMIT) {
    return item_iterator(nullptr, nullptr, 0, false, type);
  }

  ItemTypeInfo *info = getItemTypeInfo(type);
  item_iterator it(this, info->first, info->itemSize, info->isMulti, type);
  item_iterator last = end(type);
  for (; it != last; ++it) {
    if (it->index == 0 || it->getType() == type) {
      return it;
    }
  }
  return last;
}

bool GfItemBoxBase::isMulti(ItemType::Type type) { return getItemTypeInfo(type)->isMulti; }

void GfItemBoxBase::setEquipFlag(u32 item, GfItemHandle handle, bool isEquip) {
  if (item == 0) {
    return;
  }

  GfItemInfo *info = findItemHandle(item, handle);
  if (info != nullptr) {
    info->isEquip = isEquip;
  }
}

GfItemInfo *GfItemBoxBase::findItemHandle(u32 item, GfItemHandle handle) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->getType() == type && it->index == index && it->getHandle().value == handle.value) {
      return &*it;
    }
  }
  return nullptr;
}

GfItemHandle GfItemInfo::getHandle() const {
  GfItemHandle handle;
  handle.bits.type = type;
  handle.bits.serial = serial;
  return handle;
}

u32 GfItemBoxBase::getSerial(ItemType::Type type) { return *getItemTypeInfo(type)->serial; }

u32 GfItemBoxBase::updateSerialLocal(ItemType::Type type) {
  u32 *serial = getItemTypeInfo(type)->serial;
  u32 next = (*serial + 1) & ITEM_SERIAL_MASK;
  if (next == 0) {
    next++;
  }
  *serial = next;
  return next;
}

void GfItemBoxBase::setSerial(ItemType::Type type, u32 serial) {
  ItemTypeInfo *info = getItemTypeInfo(type);
  *info->serial = serial & ITEM_SERIAL_MASK;
}

bool GfItemBoxBase::findSerial(ItemType::Type type, u32 serial) {
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->index != 0 && it->serial == serial) {
      return true;
    }
  }
  return false;
}

void GfItemBoxBase::clear() {
  for (u32 type = ItemType::PC_WPN_CHIP; type <= ItemType::HANA_ASSIST; type++) {
    ItemType::Type itemType = static_cast<ItemType::Type>(type);
    for (item_iterator it = begin(itemType), last = end(itemType); it != last; ++it) {
      *it = GfItemInfo();
    }
  }
}

GfItemInfo *GfItemBoxBase::findItem(u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->getType() == type && it->index == index) {
      return &*it;
    }
  }
  return nullptr;
}

void GfItemInfo::setType(ItemType::Type type) { this->type = type; }

bool GfItemBoxBase::canAddItem(u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  u32 stock = GfItemUtil::getEnableStock(item);
  if (getItemBoxIndex(type) == ITEM_BOX_INDEX_NONE) {
    return false;
  }

  item_iterator it = begin(type);
  GfItemInfo *last = getItemTypeInfo(type)->last;
  if (isMulti(type)) {
    for (; it.current != last; ++it) {
      if (it->index != 0 && it->index == index && it->getType() == type) {
        return it->count < stock;
      }
    }
  }

  for (it = begin(type); it.current != last; ++it) {
    if (it->index == 0) {
      return true;
    }
  }
  return false;
}

void GfItemBoxBase::makeItem(GfItemInfo &info, u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  info = GfItemInfo();
  if (GfFieldTime::get() != nullptr) {
    GfFieldTime::get()->getGameTime();
  }
  info.type = type;
  info.index = index;
  info.count = 1;
  info.time = 0;
}

int GfItemBoxBase::countItem(u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  int count = 0;
  item_iterator it = begin(type);
  item_iterator last = end(type);
  if (item != 0) {
    for (; it != last; ++it) {
      if (it->index != 0 && it->index == index && it->getType() == type) {
        count += it->count;
      }
    }
  }
  return count;
}

int GfItemBoxBase::countItemCategory(ItemType::Type type) {
  int count = 0;
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->index != 0) {
      count += it->count;
    }
  }
  return count;
}

int GfItemBoxBase::maxStockItem(u32 item) {
  if (item == 0) {
    return 0;
  }

  ItemType::Type type = GfDataItem::getItemType(item);
  ItemTypeInfo *info = getItemTypeInfo(type);
  if (!isMulti(type)) {
    return info->capacity;
  }
  return info->maxStock;
}

u32 GfItemBoxBase::getItemTime(u32 item) {
  if (item == 0) {
    return 0;
  }

  GfItemInfo *info = findItem(item);
  return info != nullptr ? info->time : 0;
}

u32 GfItemBoxBase::getItemTime(u32 item, GfItemHandle handle) {
  if (item == 0) {
    return 0;
  }

  GfItemInfo *info = findItemHandle(item, handle);
  return info != nullptr ? info->time : 0;
}

bool GfItemBoxBase::existItem(u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  item_iterator it = begin(type);
  item_iterator last = end(type);
  if (item != 0) {
    for (; it != last; ++it) {
      if (it->index != 0 && it->index == index && it->getType() == type) {
        return true;
      }
    }
  }
  return false;
}

u32 GfItemBoxBase::getBoxIndex(const GfItemInfo *info) {
  if (info == nullptr || info->index == 0) {
    return -1;
  }

  ItemTypeInfo *typeInfo = getItemTypeInfo(info->getType());
  return static_cast<u64>(reinterpret_cast<const u8 *>(info) - reinterpret_cast<const u8 *>(typeInfo->first)) / typeInfo->itemSize;
}

GfItemInfo *GfItemBoxBase::getItem(ItemType::Type type, u32 index) {
  ItemTypeInfo *info = getItemTypeInfo(type);
  if (info->first == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<GfItemInfo *>(reinterpret_cast<u8 *>(info->first) + info->itemSize * index);
}

void GfItemBoxBase::removeItem(GfItemInfo *info) {
  if (info != nullptr) {
    *info = GfItemInfo();
  }
}

int GfItemBoxBase::getFreeSlotCount(ItemType::Type type) {
  int count = 0;
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->index == 0) {
      count++;
    }
  }
  return count;
}

u32 GfItemBoxBase::getFreeStackCount(u32 item) {
  ItemType::Type type = GfDataItem::getItemType(item);
  if (isMulti(type)) {
    ItemTypeInfo *info = getItemTypeInfo(type);
    int count = countItem(item);
    if (count != 0) {
      return info->maxStock - count;
    }
    if (getFreeSlotCount(type) != 0) {
      return info->maxStock;
    }
  } else if (getFreeSlotCount(type) != 0) {
    return getItemTypeInfo(type)->maxStock;
  }
  return 0;
}

GfItemInfo::GfItemInfo() {
  index = 0;
  type = 0;
  count = 0;
  _00_29 = 0;
  isEquip = 0;
  _00_31 = 0;
  time = 0;
  serial = 0;
  _08_26 = 0;
}

GfItemInfo::GfItemInfo(const GfItemInfo &other) : SDataItemInfo(other) {}

u16 GfItemInfo::getMaxStock() const {
  ItemType::Type itemType = getType();
  if (itemType == ItemType::NONE) {
    return 0;
  }
  return GfItemBox::get()->getItemTypeInfo(itemType)->maxStock;
}

u16 GfItemInfo::getItemID() const { return GfDataItem::getItemStartID(getType()) + index - 1; }

void GfItemInfo::setItemID(u16 item) { index = item - GfDataItem::getItemStartID(getType()); }

GfItemHandle GfItemBox::addItem(u32 item) {
  GfItemHandle handle(0);
  if (get()->GfItemBoxBase::addItem(item, handle)) {
    GfEvent::callItemAdd(item, 1);
    return handle;
  }

  ItemType::Type type = GfDataItem::getItemType(item);
  if (get()->isMulti(type) || !GfPoolItemBox::get()->addItem(item, handle)) {
    handle = GfItemHandle(0);
  }
  return handle;
}

bool GfItemBox::addItem(u32 item, u32 count) {
  int itemCount = get()->countItem(item);
  if (GfItemUtil::getEnableStock(item) - itemCount < count) {
    return false;
  }

  GfItemBox *itemBox = get();
  for (u32 i = 0; i < count; i++) {
    GfItemHandle handle(0);
    if (!itemBox->canAddItem(item) || !itemBox->GfItemBoxBase::addItem(item, handle)) {
      return false;
    }
  }
  return true;
}

bool GfItemBox::decItem(u32 item, u32 count) {
  if (count == 0) {
    return false;
  }
  return get()->GfItemBoxBase::decItem(item, count);
}

bool GfItemBox::decItemForNewGame(u32 item, u32 count) {
  if (count == 0) {
    return false;
  }
  return get()->GfItemBoxBase::decItem(item, count);
}

void GfPoolItemBox::initialize(ItemBox *itemBox) {
  get()->setItemBox(&get()->mPoolItemBox, true);
  get()->setupSerial(itemBox);
}

} // namespace gf

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

template <u32 N> static void setItems(GfItemBoxBase *itemBoxBase, ItemBox *itemBox, u32 index, SDataItemInfo (&items)[N], u32 maxStock, bool isMulti) {
  itemBoxBase->setItemTypeInfo(itemBox, index, static_cast<GfItemInfo *>(items), static_cast<GfItemInfo *>(items + N), N, sizeof(GfItemInfo), maxStock, isMulti);
}

item_iterator item_iterator::operator++() {
  GfItemInfo *last = unknown00->getItemTypeInfo(unknown18)->unknown08;
  if (unknown08 != last) {
    do {
      unknown08 = reinterpret_cast<GfItemInfo *>(reinterpret_cast<u8 *>(unknown08) + unknown10);
    } while (unknown08 != last && unknown08->unknown00_0 != 0 && unknown08->getType() != unknown18);
  }
  return *this;
}

item_iterator GfItemBoxBase::end(ItemType::Type type) {
  ItemTypeInfo *info = getItemTypeInfo(type);
  return item_iterator(this, info->unknown08, info->unknown22, info->unknown10, type);
}

ItemType::Type GfItemInfo::getType() const { return static_cast<ItemType::Type>(m_type); }

GfItemBoxBase::GfItemBoxBase() : unknown300(nullptr) {}

void GfItemBoxBase::setItemBox(ItemBox *itemBox, bool isClear) {
  unknown300 = itemBox;
  if (itemBox == nullptr) {
    return;
  }

  if (isClear) {
    __builtin_memset(itemBox, 0, sizeof(ItemBox));
  }
  setItems(this, itemBox, ITEM_BOX_INDEX_PC_WPN_CHIP, itemBox->unknown00, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_PC_EQUIP, itemBox->unknown960, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_EQUIP_ORB, itemBox->unknown3390, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_SALVAGE, itemBox->unknown4b00, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_PRECIOUS, itemBox->unknown5460, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_INFO, itemBox->unknown6bd0, 1, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_EVENT, itemBox->unknown7530, 1, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_COLLECTION_LIST, itemBox->unknown79e0, 999, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_TRESURE, itemBox->unknown9150, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_EMPTY_ORB, itemBox->unknown9ab0, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_FAVORITE, itemBox->unknownb220, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_CRYSTAL_LIST, itemBox->unknownc990, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_BOOSTER, itemBox->unknownd2f0, 99, true);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ROLE, itemBox->unknowndc50, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ATR, itemBox->unknowne5b0, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ARTS_ENH, itemBox->unknownef10, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_N_ARTS_SET, itemBox->unknownf870, 1, false);
  setItems(this, itemBox, ITEM_BOX_INDEX_HANA_ASSIST, itemBox->unknown101d0, 1, false);
}

void GfItemBoxBase::setItemTypeInfo(ItemBox *itemBox, u32 index, GfItemInfo *first, GfItemInfo *last, u32 capacity, u32 itemSize, u32 maxStock, bool isMulti) {
  ItemTypeInfo &info = unknown08[index];
  info.unknown00 = first;
  info.unknown08 = last;
  info.unknown20 = capacity;
  info.unknown22 = itemSize;
  info.unknown24 = maxStock;
  info.unknown10 = isMulti;
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

void GfItemBoxBase::setSerialInfo(ItemBox *itemBox, u32 index) { unknown08[index].unknown18 = &itemBox->unknown122a0[index]; }

ItemTypeInfo *GfItemBoxBase::getItemTypeInfo(ItemType::Type type) { return &unknown08[getItemBoxIndex(type)]; }

const ItemTypeInfo *GfItemBoxBase::getItemTypeInfo(ItemType::Type type) const { return &unknown08[getItemBoxIndex(type)]; }

item_iterator GfItemBoxBase::begin(ItemType::Type type) {
  if (type >= ITEM_TYPE_LIMIT) {
    return item_iterator(nullptr, nullptr, 0, false, type);
  }

  ItemTypeInfo *info = getItemTypeInfo(type);
  item_iterator it(this, info->unknown00, info->unknown22, info->unknown10, type);
  item_iterator last = end(type);
  for (; it != last; ++it) {
    if (it->unknown00_0 == 0 || it->getType() == type) {
      return it;
    }
  }
  return last;
}

bool GfItemBoxBase::isMulti(ItemType::Type type) { return getItemTypeInfo(type)->unknown10; }

void GfItemBoxBase::setEquipFlag(u32 item, GfItemHandle handle, bool isEquip) {
  if (item == 0) {
    return;
  }

  GfItemInfo *info = findItemHandle(item, handle);
  if (info != nullptr) {
    info->unknown03_6 = isEquip;
  }
}

GfItemInfo *GfItemBoxBase::findItemHandle(u32 item, GfItemHandle handle) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->getType() == type && it->unknown00_0 == index && it->getHandle().value == handle.value) {
      return &*it;
    }
  }
  return nullptr;
}

GfItemHandle GfItemInfo::getHandle() const {
  GfItemHandle handle;
  handle.bits.unknown00_0 = m_type;
  handle.bits.unknown00_6 = unknown08_0;
  return handle;
}

u32 GfItemBoxBase::getSerial(ItemType::Type type) { return *getItemTypeInfo(type)->unknown18; }

u32 GfItemBoxBase::updateSerialLocal(ItemType::Type type) {
  u32 *serial = getItemTypeInfo(type)->unknown18;
  u32 next = (*serial + 1) & ITEM_SERIAL_MASK;
  if (next == 0) {
    next++;
  }
  *serial = next;
  return next;
}

void GfItemBoxBase::setSerial(ItemType::Type type, u32 serial) {
  ItemTypeInfo *info = getItemTypeInfo(type);
  *info->unknown18 = serial & ITEM_SERIAL_MASK;
}

bool GfItemBoxBase::findSerial(ItemType::Type type, u32 serial) {
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->unknown00_0 != 0 && it->unknown08_0 == serial) {
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
    if (it->getType() == type && it->unknown00_0 == index) {
      return &*it;
    }
  }
  return nullptr;
}

void GfItemInfo::setType(ItemType::Type type) { this->m_type = type; }

bool GfItemBoxBase::canAddItem(u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  u32 stock = GfItemUtil::getEnableStock(item);
  if (getItemBoxIndex(type) == ITEM_BOX_INDEX_NONE) {
    return false;
  }

  item_iterator it = begin(type);
  GfItemInfo *last = getItemTypeInfo(type)->unknown08;
  if (isMulti(type)) {
    for (; it.unknown08 != last; ++it) {
      if (it->unknown00_0 != 0 && it->unknown00_0 == index && it->getType() == type) {
        return it->unknown02_3 < stock;
      }
    }
  }

  for (it = begin(type); it.unknown08 != last; ++it) {
    if (it->unknown00_0 == 0) {
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
  info.m_type = type;
  info.unknown00_0 = index;
  info.unknown02_3 = 1;
  info.unknown04 = 0;
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
      if (it->unknown00_0 != 0 && it->unknown00_0 == index && it->getType() == type) {
        count += it->unknown02_3;
      }
    }
  }
  return count;
}

GfItemHandle GfItemBoxBase::getNoEquipItemHandle(u32 item) {
  if (item != 0) {
    ItemType::Type type;
    u32 index;
    GfDataItem::getItemType(type, index, item);
    for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
      if (it->getType() == type && it->unknown00_0 == index && !it->unknown03_6) {
        return it->getHandle();
      }
    }
  }
  return GfItemHandle(0);
}

int GfItemBoxBase::countItemCategory(ItemType::Type type) {
  int count = 0;
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->unknown00_0 != 0) {
      count += it->unknown02_3;
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
    return info->unknown20;
  }
  return info->unknown24;
}

u32 GfItemBoxBase::getItemTime(u32 item) {
  if (item == 0) {
    return 0;
  }

  GfItemInfo *info = findItem(item);
  return info != nullptr ? info->unknown04 : 0;
}

u32 GfItemBoxBase::getItemTime(u32 item, GfItemHandle handle) {
  if (item == 0) {
    return 0;
  }

  GfItemInfo *info = findItemHandle(item, handle);
  return info != nullptr ? info->unknown04 : 0;
}

bool GfItemBoxBase::existItem(u32 item) {
  ItemType::Type type;
  u32 index;
  GfDataItem::getItemType(type, index, item);
  item_iterator it = begin(type);
  item_iterator last = end(type);
  if (item != 0) {
    for (; it != last; ++it) {
      if (it->unknown00_0 != 0 && it->unknown00_0 == index && it->getType() == type) {
        return true;
      }
    }
  }
  return false;
}

u32 GfItemBoxBase::getBoxIndex(const GfItemInfo *info) {
  if (info == nullptr || info->unknown00_0 == 0) {
    return -1;
  }

  ItemTypeInfo *typeInfo = getItemTypeInfo(info->getType());
  return static_cast<u64>(reinterpret_cast<const u8 *>(info) - reinterpret_cast<const u8 *>(typeInfo->unknown00)) / typeInfo->unknown22;
}

GfItemInfo *GfItemBoxBase::getItem(ItemType::Type type, u32 index) {
  ItemTypeInfo *info = getItemTypeInfo(type);
  if (info->unknown00 == nullptr) {
    return nullptr;
  }
  return reinterpret_cast<GfItemInfo *>(reinterpret_cast<u8 *>(info->unknown00) + info->unknown22 * index);
}

void GfItemBoxBase::removeItem(GfItemInfo *info) {
  if (info != nullptr) {
    *info = GfItemInfo();
  }
}

int GfItemBoxBase::getFreeSlotCount(ItemType::Type type) {
  int count = 0;
  for (item_iterator it = begin(type), last = end(type); it != last; ++it) {
    if (it->unknown00_0 == 0) {
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
      return info->unknown24 - count;
    }
    if (getFreeSlotCount(type) != 0) {
      return info->unknown24;
    }
  } else if (getFreeSlotCount(type) != 0) {
    return getItemTypeInfo(type)->unknown24;
  }
  return 0;
}

GfItemInfo::GfItemInfo() {
  unknown00_0 = 0;
  m_type = 0;
  unknown02_3 = 0;
  _00_29 = 0;
  unknown03_6 = 0;
  _00_31 = 0;
  unknown04 = 0;
  unknown08_0 = 0;
  _08_26 = 0;
}

GfItemInfo::GfItemInfo(const GfItemInfo &other) : SDataItemInfo(other) {}

u16 GfItemInfo::getMaxStock() const {
  ItemType::Type itemType = getType();
  if (itemType == ItemType::NONE) {
    return 0;
  }
  return GfItemBox::get()->getItemTypeInfo(itemType)->unknown24;
}

u16 GfItemInfo::getItemID() const { return GfDataItem::getItemStartID(getType()) + unknown00_0 - 1; }

void GfItemInfo::setItemID(u16 item) { unknown00_0 = item - GfDataItem::getItemStartID(getType()); }

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
  get()->setItemBox(&get()->unknown310, true);
  get()->setupSerial(itemBox);
}

} // namespace gf

#pragma once
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

class GfItemInfo : public SDataItemInfo {
public:
  ItemType::Type getType() const;
  GfItemHandle getHandle() const;
  void setType(ItemType::Type type);
  GfItemInfo();
  GfItemInfo(const GfItemInfo &other);
  u16 getMaxStock() const;
  u16 getItemID() const;
  void setItemID(u16 item);
};

static_assert(sizeof(GfItemInfo) == 0x0c, "");

class GfItemBoxBase;

class item_iterator {
public:
  item_iterator(GfItemBoxBase *box, GfItemInfo *current, u32 itemSize, bool isMulti, ItemType::Type type)
      : unknown00(box), unknown08(current), unknown10(itemSize), unknown14(isMulti), unknown18(type) {}

  item_iterator operator++();
  GfItemInfo &operator*() const { return *unknown08; }
  GfItemInfo *operator->() const { return unknown08; }
  bool operator!=(const item_iterator &other) const { return unknown08 != other.unknown08; }

  GfItemBoxBase *unknown00; // Inferred role: box; original member name unknown.
  GfItemInfo *unknown08;    // Inferred role: current; original member name unknown.
  u32 unknown10;            // Inferred role: item size; original member name unknown.
  bool unknown14;           // Inferred role: multi; original member name unknown.
  ItemType::Type unknown18; // Inferred role: type; original member name unknown.
};

static_assert(offsetof(item_iterator, unknown10) == 0x10, "");
static_assert(offsetof(item_iterator, unknown14) == 0x14, "");
static_assert(offsetof(item_iterator, unknown18) == 0x18, "");
static_assert(sizeof(item_iterator) == 0x20, "");

struct ItemTypeInfo {
  ItemTypeInfo() : unknown00(nullptr), unknown08(nullptr), unknown10(false), unknown18(nullptr), unknown20(0), unknown22(0), unknown24(0) {}

  GfItemInfo *unknown00; // Inferred role: first; original member name unknown.
  GfItemInfo *unknown08; // Inferred role: last; original member name unknown.
  bool unknown10;        // Inferred role: multi; original member name unknown.
  u32 *unknown18;        // Inferred role: serial; original member name unknown.
  u16 unknown20;         // Inferred role: capacity; original member name unknown.
  u16 unknown22;         // Inferred role: item size; original member name unknown.
  u16 unknown24;         // Inferred role: max stock; original member name unknown.
};

static_assert(offsetof(ItemTypeInfo, unknown10) == 0x10, "");
static_assert(offsetof(ItemTypeInfo, unknown18) == 0x18, "");
static_assert(offsetof(ItemTypeInfo, unknown20) == 0x20, "");
static_assert(offsetof(ItemTypeInfo, unknown24) == 0x24, "");
static_assert(sizeof(ItemTypeInfo) == 0x28, "");

class GfItemBoxBase {
public:
  item_iterator end(ItemType::Type type);
  GfItemBoxBase();
  void setItemBox(ItemBox *itemBox, bool isClear);
  void setItemTypeInfo(ItemBox *itemBox, u32 index, GfItemInfo *first, GfItemInfo *last, u32 capacity, u32 itemSize, u32 maxStock, bool isMulti);
  void setupSerial(ItemBox *itemBox);
  void setSerialInfo(ItemBox *itemBox, u32 index);
  ItemTypeInfo *getItemTypeInfo(ItemType::Type type);
  const ItemTypeInfo *getItemTypeInfo(ItemType::Type type) const;
  item_iterator begin(ItemType::Type type);
  bool isMulti(ItemType::Type type);
  void setEquipFlag(u32 item, GfItemHandle handle, bool isEquip);
  GfItemInfo *findItemHandle(u32 item, GfItemHandle handle);
  GfItemHandle getNoEquipItemHandle(u32 item);
  u32 getSerial(ItemType::Type type);
  u32 updateSerialLocal(ItemType::Type type);
  void setSerial(ItemType::Type type, u32 serial);
  bool findSerial(ItemType::Type type, u32 serial);
  void clear();
  GfItemInfo *findItem(u32 item);
  bool addItem(u32 item, GfItemHandle &handle);
  bool canAddItem(u32 item);
  bool decItem(u32 item, u32 count);
  static void makeItem(GfItemInfo &info, u32 item);
  int countItem(u32 item);
  int countItemWithoutEquip(u32 item);
  int countItemCategory(ItemType::Type type);
  int maxStockItem(u32 item);
  u32 getItemTime(u32 item);
  u32 getItemTime(u32 item, GfItemHandle handle);
  bool existItem(u32 item);
  u32 getBoxIndex(const GfItemInfo *info);
  GfItemInfo *getItem(ItemType::Type type, u32 index);
  void removeItem(GfItemInfo *info);
  int getFreeSlotCount(ItemType::Type type);
  u32 getFreeStackCount(u32 item);
  virtual ~GfItemBoxBase() {}

  ItemTypeInfo unknown08[ITEM_BOX_INDEX_NUM]; // Inferred role: item type infos; original member name unknown.
  ItemBox *unknown300;                        // Inferred role: item box; original member name unknown.
};

static_assert(offsetof(GfItemBoxBase, unknown08) == 0x008, "");
static_assert(offsetof(GfItemBoxBase, unknown300) == 0x300, "");
static_assert(sizeof(GfItemBoxBase) == 0x308, "");

class GfItemBox : public mm::mtl::PtrSingleton<GfItemBox>, public GfItemBoxBase {
public:
  static GfItemHandle addItem(u32 item);
  static bool addItem(u32 item, u32 count);
  static bool decItem(u32 item, u32 count);
  static bool decItemForNewGame(u32 item, u32 count);
};

static_assert(sizeof(GfItemBox) == 0x310, "");

class GfPoolItemBox : public mm::mtl::PtrSingleton<GfPoolItemBox>, public GfItemBoxBase {
public:
  GfPoolItemBox() : unknown310() {}

  static void initialize(ItemBox *itemBox);

  ItemBox unknown310; // Inferred role: pool item box; original member name unknown.
};

static_assert(offsetof(GfPoolItemBox, unknown310) == 0x310, "");
static_assert(sizeof(GfPoolItemBox) == 0x12600, "");

namespace _gfit {

extern GfItemBox *s_pItemBox;
extern GfPoolItemBox *s_pItemBoxP;

} // namespace _gfit

} // namespace gf

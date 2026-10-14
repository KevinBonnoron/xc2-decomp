#pragma once
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfItemBoxBase {
public:
  virtual ~GfItemBoxBase();
  bool isMulti(ItemType::Type type);
  void setEquipFlag(u32 item, GfItemHandle handle, bool isEquip);
  GfItemHandle getNoEquipItemHandle(u32 item);
  int countItem(u32 item);
  int countItemWithoutEquip(u32 item);
  int countItemCategory(ItemType::Type type);
  int maxStockItem(u32 item);
  u32 getItemTime(u32 item);
  u32 getItemTime(u32 item, GfItemHandle handle);
};

class GfItemBox : public mm::mtl::PtrSingleton<GfItemBox>, public GfItemBoxBase {
public:
  static bool addItem(u32 item, u32 count);
  static bool decItem(u32 item, u32 count);
  static void decItemForNewGame(u32 item, u32 count);
};

} // namespace gf

#pragma once
#include <stddef.h>

#include "gf/gf_allocator.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gf {

class IGfMenuReferenceItem : public mm::mtl::ReferenceObject {
public:
  virtual void getItem(MenuItemInfo &info) const = 0;
};

class GfMenuReferenceItem : public IGfMenuReferenceItem {
public:
  void getItem(MenuItemInfo &info) const override;

  // Inferred helper: allocates an empty reference item; original name unknown.
  // __LINE__ must be 57 as in the original header: it is the line argument of operator new.
#line 57
  static GfMenuReferenceItem *unknown001() { return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuReferenceItem; }

  MenuItemInfo unknown0c; // Inferred role: item; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceItem, unknown0c) == 0x0c, "");

class GfMenuReferenceDriverEquipItem : public IGfMenuReferenceItem {
public:
  void getItem(MenuItemInfo &info) const override;

  u32 unknown0c; // Inferred role: reference driver index; original member name unknown.
  u32 unknown10; // Inferred role: equip slot; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceDriverEquipItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceDriverEquipItem, unknown10) == 0x10, "");

class GfMenuReferenceDriverFavoriteItem : public IGfMenuReferenceItem {
public:
  void getItem(MenuItemInfo &info) const override;

  u32 unknown0c; // Inferred role: reference driver index; original member name unknown.
  int unknown10; // Inferred role: favorite item index; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceDriverFavoriteItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceDriverFavoriteItem, unknown10) == 0x10, "");

class GfMenuReferenceBladeEquipItem : public IGfMenuReferenceItem {
public:
  GfMenuReferenceBladeEquipItem(u32 blade, u32 slot) : unknown0c(blade), unknown10(slot) {}
  void getItem(MenuItemInfo &info) const override;

  u32 unknown0c; // Inferred role: reference blade index; original member name unknown.
  u32 unknown10; // Inferred role: equip orb slot; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceBladeEquipItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceBladeEquipItem, unknown10) == 0x10, "");

// Inferred helper: allocates a reference blade equip item; original name unknown.
// __LINE__ must be 172 as in the original header: it is the line argument of operator new.
#line 172
inline GfMenuReferenceBladeEquipItem *unknown161(u32 blade, u32 slot) { return new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfMenuReferenceBladeEquipItem(blade, slot); }

class GfMenuReferenceBladeFavoriteItem : public IGfMenuReferenceItem {
public:
  void getItem(MenuItemInfo &info) const override;

  u32 unknown0c; // Inferred role: reference blade index; original member name unknown.
  int unknown10; // Inferred role: favorite item index; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceBladeFavoriteItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceBladeFavoriteItem, unknown10) == 0x10, "");

} // namespace gf

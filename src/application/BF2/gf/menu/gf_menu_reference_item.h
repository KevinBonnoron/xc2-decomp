#pragma once
#include <stddef.h>

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
  void getItem(MenuItemInfo &info) const override;

  u32 unknown0c; // Inferred role: reference blade index; original member name unknown.
  u32 unknown10; // Inferred role: equip orb slot; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceBladeEquipItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceBladeEquipItem, unknown10) == 0x10, "");

class GfMenuReferenceBladeFavoriteItem : public IGfMenuReferenceItem {
public:
  void getItem(MenuItemInfo &info) const override;

  u32 unknown0c; // Inferred role: reference blade index; original member name unknown.
  int unknown10; // Inferred role: favorite item index; original member name unknown.
};

static_assert(offsetof(GfMenuReferenceBladeFavoriteItem, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuReferenceBladeFavoriteItem, unknown10) == 0x10, "");

} // namespace gf

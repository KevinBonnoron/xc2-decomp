#pragma once
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuBladeInfo {
  u32 blade;
  u32 creator;
};

static_assert(sizeof(MenuBladeInfo) == 0x8, "");

class GfMenuBladeList : public ui::UIListInfo<MenuBladeInfo> {
public:
  GfMenuBladeList();
  ~GfMenuBladeList() override;
  static GfMenuBladeList *create();
  void sort(u32 type, bool ascending);
  static bool sortTimeAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortTimeDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortNameDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortNameAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortRarityAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortRarityDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortWeaponAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortWeaponDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortAttrAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortAttrDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortCreatorAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortCreatorDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortGenderDescending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  static bool sortGenderAscending(const MenuBladeInfo &info, const MenuBladeInfo &other);
  void updateOwner();
};

static_assert(sizeof(GfMenuBladeList) == 0x70, "");

} // namespace gf

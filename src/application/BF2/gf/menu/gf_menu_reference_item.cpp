#include "gf/menu/gf_menu_reference_item.h"

#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/list/gf_menu_field_skill_list.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_array.h"

namespace gf {

void GfMenuReferenceItem::getItem(MenuItemInfo &info) const { info = unknown0c; }

void GfMenuReferenceFs::getFs(MenuFieldSkill &fs) const { fs = unknown0c; }

void GfMenuReferenceQuest::getQuest(QuestID &quest) const { quest = unknown0c; }

void GfMenuReferenceDriverEquipItem::getItem(MenuItemInfo &info) const {
  u32 driver = GfMenuReference::getReferenceDriverID(unknown0c);
  if (driver != 0) {
    DataParamAcc acc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
    if (unknown10 == 0) {
      info.unknown00 = ItemType::PC_EQUIP;
      info.unknown04 = acc.getEquipAcce(0, false);
      info.unknown08 = 1;
    }
  }
}

void GfMenuReferenceDriverFavoriteItem::getItem(MenuItemInfo &info) const {
  u32 driver = GfMenuReference::getReferenceDriverID(unknown0c);
  if (driver != 0) {
    info.unknown04 = GfDataDriver::getFavorite(driver, static_cast<FAVORITE>(unknown10 + FAVORITE_ITEM_0));
    info.unknown00 = GfItemUtil::getType(info.unknown04);
    info.unknown08 = 1;
  }
}

void GfMenuReferenceBladeEquipItem::getItem(MenuItemInfo &info) const {
  u32 blade = GfMenuReference::getReferenceBladeID(unknown0c);
  if (blade != 0) {
    DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
    if (unknown10 < 3) {
      mm::mtl::FixedArray<u16, 3> orbs;
      acc.getEquipOrb(orbs, false);
      info.unknown00 = ItemType::EQUIP_ORB;
      info.unknown04 = orbs[unknown10];
      info.unknown08 = 1;
    }
  }
}

void GfMenuReferenceBladeFavoriteItem::getItem(MenuItemInfo &info) const {
  u32 blade = GfMenuReference::getReferenceBladeID(unknown0c);
  if (blade != 0) {
    DataParamAcc acc(OBJECT_TYPE_BLADE, blade, GIMMICK_TYPE_NONE);
    u32 bladeId = 0;
    if (acc.isValid()) {
      bladeId = acc.getBdatId();
    }
    info.unknown04 = GfDataBlade::getFavorite(bladeId, static_cast<FAVORITE>(unknown10 + FAVORITE_ITEM_0));
    info.unknown00 = GfItemUtil::getType(info.unknown04);
    info.unknown08 = 1;
  }
}

} // namespace gf

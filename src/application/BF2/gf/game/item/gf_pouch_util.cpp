#include "gf/game/item/gf_pouch_util.h"

#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_id.h"
#include "gf/event/gf_event.h"
#include "gf/game/item/gf_item_box.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"

namespace gf {

// Inferred role: achievement statistics ids; original enum and enumerator names unknown.
enum unknown001 {
  unknown001_19 = 0x13,
};

// Inferred role: consumes the favorite item of a pouch and starts its effect, or empties the pouch when the item is gone; no game symbol, original name unknown.
static bool unknown002(u32 driver, u32 slot, SDataPouch &pouch) {
  int count = GfItemBox::get()->countItem(pouch.unknown04);
  u32 item = pouch.unknown04;
  if (count == 0) {
    SCOM_POPUP::createPouch(driver, item, 0);
    pouch.unknown04 = 0;
    pouch.unknown00 = 0.0f;
    GfDataDriver::setPouchData(driver, slot, pouch);
    return false;
  }
  if (GfItemBox::decItem(item, 1)) {
    GfEvent::callItemAdd(item, -1);
  }
  SCOM_ITEM_USE::create(pouch.unknown04, driver);
  f32 time = GfDataItem::getFavoriteItemTime(pouch.unknown04);
  if (time <= 0.0f) {
    time = 180.0f;
  }
  pouch.unknown00 = time;
  u32 trustPoint = GfBdatItem::get()->getFavoriteTrustPoint(pouch.unknown04);
  if (trustPoint != 0) {
    for (int i = 0; i < GfDataDriver::getMaxSetBladeNum(driver); i++) {
      u32 blade = GfDataDriver::getBlade(driver, i);
      if (blade != 0) {
        SCOM_ADD_TRUST::create(blade, trustPoint);
      }
    }
  }
  GfDataDriver::setPouchData(driver, slot, pouch);
  return true;
}

void GfPouchUtil::updatePouch(u32 driver, u32 slot, const SDataPouch &pouch, const fw::UpdateInfo &info) {
  if (pouch.unknown04 != 0) {
    SDataPouch updated = pouch;
    updated.unknown00 -= info.unknown04;
    if (updated.unknown00 <= 0.0f && unknown002(driver, slot, updated)) {
      SCOM_POPUP::createPouch(driver, pouch.unknown04, 1);
    }
    GfDataDriver::setPouchData(driver, slot, updated);
  }
}

void GfPouchUtil::setPouch(u32 driver, u32 slot, const SDataPouch &pouch) {
  SDataPouch updated = pouch;
  if (pouch.unknown04 != 0) {
    u32 item = updated.unknown04;
    GfDataDriver::setUsedFavoriteItemForPouch(driver, item);
    int count = GfDataDriver::getMaxSetBladeNum(driver);
    for (int i = 0; i < count; i++) {
      GfDataBlade::setUsedFavoriteItemForPouch(GfDataDriver::getBlade(driver, i), item);
    }
    SCOM_ACHIEV_INC::addTotalCount(unknown001_19, 1);
    SCOM_ACHIEV_INC::create(unknown001_19, 1, 0);
    updated.unknown00 = 0.0f;
    unknown002(driver, slot, updated);
  } else {
    updated.unknown00 = 0.0f;
  }
}

bool GfPouchUtil::isExistOpenItem() { return GfItemBox::get()->countItem(ITEM_UNKNOWN_62D9) != 0; }

void GfPouchUtil::setTimeUpForDebug(u32 driver, u32 slot) {
  SDataPouch pouch = *GfDataDriver::getPouchData(driver, slot);
  if (pouch.unknown00 > 0.0f) {
    pouch.unknown00 = 0.0f;
    setPouch(driver, slot, pouch);
  }
}

void GfPouchUtil::execOpen(u32 driver) {
  if (GfItemBox::get()->countItem(ITEM_UNKNOWN_62D9) != 0) {
    SDataPouch pouch = *GfDataDriver::getPouchData(driver, 0);
    u32 slot = 0;
    if (pouch._06 != 0) {
      slot = 1;
      pouch = *GfDataDriver::getPouchData(driver, 1);
      if (pouch._06 != 0) {
        slot = 2;
        pouch = *GfDataDriver::getPouchData(driver, 2);
        if (pouch._06 != 0) {
          return;
        }
      }
    }
    pouch._06 = 1;
    GfDataDriver::setPouchData(driver, slot, pouch);
    if (GfItemBox::decItem(ITEM_UNKNOWN_62D9, 1)) {
      GfEvent::callItemAdd(ITEM_UNKNOWN_62D9, -1);
    }
  }
}

bool GfPouchUtil::isEnableOpen(u32 driver) {
  for (u32 slot = 0; slot < 3; slot++) {
    if (GfDataDriver::getPouchData(driver, slot)->_06 == 0) {
      return true;
    }
  }
  return false;
}

u8 GfPouchUtil::getOpenCount(u32 driver) {
  u8 count = 0;
  for (u32 slot = 0; slot < 3; slot++) {
    if (GfDataDriver::getPouchData(driver, slot)->_06 != 0) {
      count++;
    }
  }
  return count;
}

} // namespace gf

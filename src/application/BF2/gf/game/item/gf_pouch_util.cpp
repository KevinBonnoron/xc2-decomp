#include "gf/game/item/gf_pouch_util.h"

#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_item_id.h"
#include "gf/event/gf_event.h"
#include "gf/game/item/gf_item_box.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"

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

bool GfPouchUtil::isExistOpenItem() { return GfItemBox::get()->countItem(ITEM_UNKNOWN_25305) != 0; }

void GfPouchUtil::setTimeUpForDebug(u32 driver, u32 slot) {
  SDataPouch pouch = GfDataDriver::getPouchData(driver, slot);
  if (pouch.unknown00 > 0.0f) {
    pouch.unknown00 = 0.0f;
    setPouch(driver, slot, pouch);
  }
}

void GfPouchUtil::execOpen(u32 driver) {
  if (GfItemBox::get()->countItem(ITEM_UNKNOWN_25305) != 0) {
    SDataPouch pouch = GfDataDriver::getPouchData(driver, 0);
    u32 slot = 0;
    if (pouch._06 != 0) {
      slot = 1;
      pouch = GfDataDriver::getPouchData(driver, 1);
      if (pouch._06 != 0) {
        slot = 2;
        pouch = GfDataDriver::getPouchData(driver, 2);
        if (pouch._06 != 0) {
          return;
        }
      }
    }
    pouch._06 = 1;
    GfDataDriver::setPouchData(driver, slot, pouch);
    if (GfItemBox::decItem(ITEM_UNKNOWN_25305, 1)) {
      GfEvent::callItemAdd(ITEM_UNKNOWN_25305, -1);
    }
  }
}

bool GfPouchUtil::isEnableOpen(u32 driver) {
  for (u32 slot = 0; slot < 3; slot++) {
    if (GfDataDriver::getPouchData(driver, slot)._06 == 0) {
      return true;
    }
  }
  return false;
}

u32 GfPouchUtil::getOpenCount(u32 driver) {
  u8 count = 0;
  for (u32 slot = 0; slot < 3; slot++) {
    if (GfDataDriver::getPouchData(driver, slot)._06 != 0) {
      count++;
    }
  }
  return count;
}

// Inferred role: favorite bonus of one favorite slot: half for the right category, one more for the right item (inlined six times by unknown004); original name unknown.
static f32 unknown003(const SDataPouch &pouch, u32 category, u32 favoriteItem) {
  f32 bonus = 0.0f;
  if (pouch.unknown04 != 0) {
    bonus = GfBdatItem::get()->getFavoriteCategory(pouch.unknown04) == category ? 0.5f : 0.0f;
    if (pouch.unknown04 == favoriteItem) {
      bonus += 1.0f;
    }
  }
  return bonus;
}

// Inferred role: builds the effect of a favorite item: its type and a factor of 1 plus the bonuses of the drivers of the party and their blades; no game symbol (0x7100363290), original name unknown.
static void unknown004(PouchEffect &effect, const SDataPouch &pouch) {
  effect.unknown00 = GfDataItem::getFavoriteItemType(pouch.unknown04);
  effect.unknown04 = 1.0f;
  GfBdatChrDr *chrDr = GfBdatChrDr::get();
  for (u32 member = 0; member < 3; member++) {
    u32 driver = GfDataParty::getDriver(member);
    if (driver != 0) {
      effect.unknown04 += unknown003(pouch, chrDr->getChrDrFavoriteCategory(driver, 0), chrDr->getChrDrFavoriteItem(driver, 0));
      effect.unknown04 += unknown003(pouch, chrDr->getChrDrFavoriteCategory(driver, 1), chrDr->getChrDrFavoriteItem(driver, 1));
      int count = GfDataDriver::getMaxSetBladeNum(driver);
      for (int i = 0; i < count; i++) {
        u32 blade = GfDataDriver::getBlade(driver, i);
        if (blade != 0) {
          SDataBlade &dataBlade = GfDataBlade::getSDataBlade(blade);
          effect.unknown04 += unknown003(pouch, dataBlade.unknown666[0].unknown00, dataBlade.unknown666[0].unknown02);
          effect.unknown04 += unknown003(pouch, dataBlade.unknown666[1].unknown00, dataBlade.unknown666[1].unknown02);
        }
      }
    }
  }
}

// Reference evidence: no game call site of getPouch or getPouchData tests the result for null (they dereference it, copy it or pass it as a `const SDataPouch &`),
// getPouchData returns an element of the driver record that getSDataDriver gives by reference, and the game's getPouch (0x7100363038: stp, bl getPouchData, ldp, ret)
// is not a tail call, which clang 3.9 only produces when a returned reference is involved (a pointer returned by a pointer returning callee is a plain `b`).
SDataPouch &GfPouchUtil::getPouch(u32 driver, u32 slot) { return GfDataDriver::getPouchData(driver, slot); }

bool GfPouchUtil::getEffect(mm::mtl::FixedVector<PouchEffect, 3> &effects, u32 driver) {
  for (u32 slot = 0; slot < 3; slot++) {
    SDataPouch &pouch = GfDataDriver::getPouchData(driver, slot);
    if (pouch.unknown04 == 0) {
      continue;
    }
    if (pouch._06 == 0) {
      return false;
    }
    PouchEffect effect;
    unknown004(effect, pouch);
    effects.push_back(effect);
  }
  return effects.size() != 0;
}

bool GfPouchUtil::getEffect(mm::mtl::FixedVector<PouchEffect, 3> &effects, u32 driver, u32 slot) {
  SDataPouch &pouch = GfDataDriver::getPouchData(driver, slot);
  if (pouch.unknown04 == 0 || pouch._06 == 0) {
    return false;
  }
  PouchEffect effect;
  unknown004(effect, pouch);
  effects.push_back(effect);
  return effects.size() != 0;
}

} // namespace gf

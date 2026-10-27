#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/scom/gf_scom_achiev.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
struct MsgObjectNotifyDamage;

// Inferred role: achievement statistics ids; original enum and enumerator names unknown.
enum unknown001 {
  unknown001_32 = 0x20,
  unknown001_33 = 0x21,
  unknown001_57 = 0x39,
  unknown001_59 = 0x3b,
};

void GfAchievStats::checkBuyItemFromShop(u32 item, u32 count, u32 shop, u32 money) {
  SCOM_ACHIEV_INC::addTotalCount(unknown001_32, count);
  SCOM_ACHIEV_INC::create(unknown001_32, count, 0);
  SCOM_ACHIEV_INC::addTotalCount(unknown001_57, money);
  SCOM_ACHIEV_INC::create(unknown001_57, money, 0);
}

void GfAchievStats::checkSellItemFromShop(u32 item, u32 count, u32 shop, u32 money) {
  SCOM_ACHIEV_INC::addTotalCount(unknown001_33, count);
  SCOM_ACHIEV_INC::create(unknown001_33, count, 0);
  SCOM_ACHIEV_INC::addTotalCount(unknown001_59, money);
  SCOM_ACHIEV_INC::create(unknown001_59, money, 0);
}

void GfAchievStats::checkFallLength(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &) {}

u32 GfAchievStats::checkMove(u32 move, u32) { return move; }

} // namespace gf

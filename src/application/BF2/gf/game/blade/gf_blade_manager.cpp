#include "gf/game/blade/gf_blade_manager.h"

#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_blade_create.h"
#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/util/gf_item_util.h"
#include "ml/rand.h"

namespace gf {

namespace _gfdbm {

u32 s_outofname = 1;

} // namespace _gfdbm

constexpr u32 RARE_BLADE_APPEAR_TYPE_COUNT = 5;

GfBladeManager::GfBladeManager(const GfSetupParam &param) {
  _gfdbm::s_outofname = 1;
  initialize(param);
}

void GfBladeManager::initialize(const GfSetupParam &) { unknown08 = true; }

GfBladeManager::~GfBladeManager() {}

void GfBladeManager::build(const GfSetupParam &param) {
  // __LINE__ must be 146 as in the original file: its value changes the instruction order.
#line 146
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfBladeManager(param);
}

void GfBladeManager::destroy() {
  GfBladeManager *bladeManager = get();
  bladeManager->finalize();
  delete bladeManager;
}

void GfBladeManager::finalize() { unknown08 = false; }

bool GfBladeManager::isInitialized() {
  GfBladeManager *bladeManager = get();
  return bladeManager != nullptr ? bladeManager->unknown08 : false;
}

void GfBladeManager::setupGame() {
  if (GfDataBladeCreate::getRareBladeAppearType() != 0) {
    return;
  }

  GfDataBladeCreate::setRareBladeAppearType(ml::mtRand(RARE_BLADE_APPEAR_TYPE_COUNT) + 1);
  GfDataBladeCreate::resetAssureCount();
}

int GfBladeManager::getRandom(u32 max) { return ml::mtRand(max); }

f32 GfBladeManager::getRandomF1() { return ml::mtRandf2(); }

bool GfBladeManager::isBindRareBladeCrystal(u32 item) {
  if (item == 0 || GfItemUtil::getType(item) != ItemType::CRYSTAL_LIST) {
    return false;
  }

  return GfBdatItem::get() != nullptr && GfBdatItem::get()->getCrystalListBladeID(item) != 0;
}

} // namespace gf

#include "gf/game/blade/gf_blade_manager.h"

#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_blade_create.h"
#include "gf/data/gf_data_idea.h"
#include "gf/data/gf_data_item.h"
#include "gf/game/blade/gf_blade_create.h"
#include "gf/gf_allocator.h"
#include "gf/util/gf_item_util.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace _gfdbm {

u32 s_outofname = 1;

} // namespace _gfdbm

constexpr u32 RARE_BLADE_APPEAR_TYPE_UNKNOWN_5 = 5; // Inferred role: rare blade appear type count; original name unknown.

GfBladeManager::GfBladeManager(const GfSetupParam &param) {
  _gfdbm::s_outofname = 1;
  initialize(param);
}

void GfBladeManager::initialize(const GfSetupParam &) { unknown08 = true; }

GfBladeManager::~GfBladeManager() {}

void GfBladeManager::build(const GfSetupParam &param) {
  // __LINE__ must be 146 as in the original file: its value changes the instruction order.
#line 146
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBladeManager(param);
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

  GfDataBladeCreate::setRareBladeAppearType(ml::mtRand(RARE_BLADE_APPEAR_TYPE_UNKNOWN_5) + 1);
  GfDataBladeCreate::resetAssureCount();
}

int GfBladeManager::getRandom(u32 max) { return ml::mtRand(max); }

f32 GfBladeManager::getRandomF1() { return ml::mtRandf2(); }

bool GfBladeManager::isBindRareBladeCrystal(u32 item) {
  if (item == 0 || GfItemUtil::getType(item) != ItemType::ITEM_TYPE_UNKNOWN_11) {
    return false;
  }

  return GfBdatItem::get() != nullptr && GfBdatItem::get()->getCrystalListBladeID(item) != 0;
}

// The game compiles GfBladeCreate in this unit: its functions (0x71003011a0 to 0x7100303c54, with their unnamed helpers up to 0x7100306d74) follow
// GfBladeManager::isBindRareBladeCrystal (0x7100301148) and precede this unit's deferred PtrSingleton<GfBladeManager> destructors (0x7100306d74).
void GfBladeCreate::clear() { GfBladeCreateInfo::clear(); }

void GfBladeCreate::setupDriver(u32 driver) { unknown00 = driver; }

bool GfBladeCreate::setupCoreCrystal(u32 crystal) {
  if (!GfItemUtil::isValidCrystal(crystal)) {
    return false;
  }
  unknown04 = crystal;
  return true;
}

void GfBladeCreate::setupAddBooster(u32 booster) {
  unknown08.push_back(booster);
  int idea = GfBdatItem::get()->getBoosterIdea(booster);
  u32 category = GfBdatItem::get()->getBoosterCategory(booster);
  unknown210.setLevel(category, unknown210.unknown00[category].unknown04 + idea);
}

bool GfBladeCreate::isEnableAddBlade() const { return GfDataBlade::getEnableCountForCreateBlade() != 0; }

bool GfBladeCreate::isResultRare() const { return unknown244 || unknowna4c != 0; }

bool GfBladeCreate::getResultBlade(SDataBlade &blade) const {
  if (!unknowna3a) {
    return false;
  }
  setupSDataBlade(blade, *this);
  return true;
}

} // namespace gf

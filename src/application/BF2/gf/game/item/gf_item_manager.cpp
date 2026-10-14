#include "gf/game/item/gf_item_manager.h"
#include "gf/data/gf_data_item.h"
#include "gf/game/item/gf_item_box.h"
#include "gf/gf_allocator.h"

namespace gf {

GfItemManager::GfItemManager(const GfSetupParam &param) : mInitialized(false) { initialize(param); }

void GfItemManager::initialize(const GfSetupParam &) {
  _gfit::s_pItemBox = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfItemBox;
  _gfit::s_pItemBoxP = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfPoolItemBox;
  clear();
  mInitialized = true;
}

GfItemManager::~GfItemManager() {}

void GfItemManager::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfItemManager(param); }

void GfItemManager::destroy() {
  GfItemManager *itemManager = get();
  itemManager->finalize();
  delete itemManager;
}

void GfItemManager::finalize() {
  if (_gfit::s_pItemBox != nullptr) {
    delete _gfit::s_pItemBox;
    _gfit::s_pItemBox = nullptr;
  }
  if (_gfit::s_pItemBoxP != nullptr) {
    delete _gfit::s_pItemBoxP;
    _gfit::s_pItemBoxP = nullptr;
  }
  mInitialized = false;
}

bool GfItemManager::isInitialized() {
  GfItemManager *itemManager = get();
  if (itemManager == nullptr) {
    return false;
  }
  return itemManager->mInitialized;
}

void GfItemManager::clear() {
  ItemBox *itemBox = GfDataItem::getItemBox();
  GfItemBox::get()->setItemBox(itemBox, true);
  GfPoolItemBox::initialize(GfDataItem::getItemBox());
}

} // namespace gf

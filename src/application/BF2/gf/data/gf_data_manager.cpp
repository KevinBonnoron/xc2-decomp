#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_store.h"

namespace gf {

SDataGame *GfDataManager::getDataGame() { return &GfDataStore::getDataGame(); }

} // namespace gf

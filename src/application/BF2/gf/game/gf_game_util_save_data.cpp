#include "gf/game/gf_game_util_save_data.h"

#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_system.h"
#include "gf/field/gf_real_time.h"

namespace gf {

void GfGameUtilSaveData::getSaveData(SDataSystem &dataSystem) {
  const SDataSystem *source = GfDataManager::getDataSystem();
  dataSystem.unknown00 = source->unknown00;
  dataSystem.unknown08 = source->unknown08;
}

} // namespace gf

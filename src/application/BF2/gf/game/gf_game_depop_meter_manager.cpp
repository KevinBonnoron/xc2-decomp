#include "gf/game/gf_game_depop_meter_manager.h"

namespace gf {

void GfGameDepopMeterManager::dispose() {
  if (get() != nullptr) {
    delete get();
  }
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameDepopMeterManager>::~PtrSingleton();

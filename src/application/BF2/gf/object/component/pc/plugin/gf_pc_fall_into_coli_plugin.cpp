#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"

#include "gf/game/gf_game_search_obj.h"

namespace gf {
namespace pc {

FallIntoColiPlugin::FallIntoColiPlugin() : unknown0c(0.0f), unknown10(0.0f) {}

FallIntoColiPlugin::~FallIntoColiPlugin() {}

void FallIntoColiPlugin::cleanup(GfComBehaviorPc &) {
  if (unknown18 != INVALID_SEARCH_OBJ) {
    GfGameSearchObj::destroyObj(unknown18);
    unknown18 = INVALID_SEARCH_OBJ;
  }
}

void FallIntoColiPlugin::onActivate() {
  unknown0c = 0.0f;
  unknown10 = 0.0f;
}

void FallIntoColiPlugin::onDeactivate() { GfGameSearchObj::setEnable(unknown18, false); }

} // namespace pc
} // namespace gf

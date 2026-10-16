#include "gf/object/component/pc/plugin/gf_pc_fall_into_coli_plugin.h"

#include "gf/game/gf_game_search_obj.h"

namespace gf {
namespace pc {

FallIntoColiPlugin::FallIntoColiPlugin() : searchTimer(0.0f), stayTimer(0.0f) {}

FallIntoColiPlugin::~FallIntoColiPlugin() {}

void FallIntoColiPlugin::cleanup(GfComBehaviorPc &) {
  if (searchObj != INVALID_SEARCH_OBJ) {
    GfGameSearchObj::destroyObj(searchObj);
    searchObj = INVALID_SEARCH_OBJ;
  }
}

void FallIntoColiPlugin::onActivate() {
  searchTimer = 0.0f;
  stayTimer = 0.0f;
}

void FallIntoColiPlugin::onDeactivate() { GfGameSearchObj::setEnable(searchObj, false); }

} // namespace pc
} // namespace gf

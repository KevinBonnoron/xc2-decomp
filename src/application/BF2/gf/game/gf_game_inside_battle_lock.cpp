#include "gf/game/gf_game_inside_battle_lock.h"

namespace gf {

void GfGameInsideBattleLock::destroy() { delete get(); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfGameInsideBattleLock>::~PtrSingleton();

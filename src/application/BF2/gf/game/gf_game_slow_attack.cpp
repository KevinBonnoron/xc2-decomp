#include "gf/game/gf_game_slow_attack.h"

#include "gf/game/gf_game_speed.h"

namespace gf {

f32 GfSlowAttack::getPlaySpeed() const { return GfGameSpeed::getPlaySpeed(); }

} // namespace gf

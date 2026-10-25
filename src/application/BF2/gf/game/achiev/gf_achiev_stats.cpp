#include "gf/game/achiev/gf_achiev_manager.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
struct MsgObjectNotifyDamage;

void GfAchievStats::checkFallLength(GF_OBJ_HANDLE *, const MsgObjectNotifyDamage &) {}

u32 GfAchievStats::checkMove(u32 move, u32) { return move; }

} // namespace gf

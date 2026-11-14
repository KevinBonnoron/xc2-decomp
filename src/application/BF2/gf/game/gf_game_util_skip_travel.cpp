#include "gf/game/gf_game_util_skip_travel.h"

#include "gf/request/gf_req_command.h"

namespace gf {

void GfGameUtilSkipTravel::execSkipTravel(u32 mapjump) {
  if (isEnableSkipTravel(mapjump)) {
    GfMapjumpInfo info(mapjump);
    GfReqCommand::reqMapjump(info);
  }
}

} // namespace gf

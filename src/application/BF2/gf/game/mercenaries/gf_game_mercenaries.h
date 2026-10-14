#pragma once
#include "types.h"

namespace gf {

class GfGameMercenaries {
public:
  static void cancelMission(u32 mission);
  static void clearTeamMember(u32 team);
};

} // namespace gf

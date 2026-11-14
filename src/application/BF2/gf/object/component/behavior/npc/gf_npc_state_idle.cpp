#include "gf/object/component/behavior/npc/gf_npc_state_idle.h"

#include "fw/fw_update_info.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixstr.h"

namespace gf {
namespace npc {

void StateIdle::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  if (unknown18.unknown00 != unknown020 && !unknown18.unknown08.empty()) {
    unknown18.update(info.unknown04);
    if (!unknown18.unknown34) {
      return;
    }

    if (unknown18.unknown35) {
      behavior->init(false);
    }
  }

  int stateId = behavior->getNexStateId();
  if (stateId != -1) {
    reqState(stateId);
  }
}

} // namespace npc
} // namespace gf

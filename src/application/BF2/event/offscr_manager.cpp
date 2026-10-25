#include "event/offscr_manager.h"

#include "event/manager.h"
#include "ml/scn.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

OffscrManager::OffscrManager() {
  for (u32 i = 0; i < SCREEN_COUNT; i++) {
    unknown10[i] = nullptr;
  }
}

void OffscrManager::clear() {
  for (u32 i = 1; i < SCREEN_COUNT; i++) {
    if (unknown10[i] != nullptr) {
      ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
      parmAcc.deleteAddRenderView(unknown10[i]);
      delete unknown10[i];
      unknown10[i] = nullptr;
    }
  }
}

bool OffscrManager::isScreenExist(u32 screenID) const { return unknown10[screenID] != nullptr; }

void OffscrManager::OnEventProc(MSG_TYPE type) {
  if (type == MSG_TYPE_CLEAR) {
    clear();
  }
}

} // namespace event

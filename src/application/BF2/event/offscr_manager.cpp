#include "event/offscr_manager.h"

#include "event/manager.h"
#include "ml/ml_mem.h"
#include "ml/scn.h"
#include "mm_math/mm_pnt.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_render_dr_sys.h"
#include "scn/scn_render_dr_sys_parm_acc.h"

namespace event {

OffscrManager::OffscrManager() {
  for (u32 i = 0; i < SCREEN_COUNT; i++) {
    unknown10[i] = nullptr;
  }
}

void OffscrManager::createScreen(u32 screenID) {
  if (screenID != 0 && unknown10[screenID] == nullptr) {
    ml::ScnRenderDrViewCtrl *view = new (ml::MlMem::getProductMem(), nullptr, 0, 4, false) ml::ScnRenderDrViewCtrl;
    view->unknown2c = 1.0f;
    view->unknown30 = 1.0f;
    view->unknown00 = mm::Pnt<int>(256, 256);
    view->unknown08 = screenID - 1;
    view->unknown20 = nullptr;
    view->unknown28 = false;
    view->unknown34 = false;
    view->unknown35 = false;
    view->unknown14 = 0;
    view->unknown18 = 0;
    view->unknown0c = 0;
    view->unknown10 = 0;
    view->unknown1c = true;
    ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
    parmAcc.createAddRenderView(view);
    unknown10[screenID] = view;
  }
}

void OffscrManager::clear() {
  for (u32 i = 1; i < SCREEN_COUNT; i++) {
    if (unknown10[i] != nullptr) {
      ml::ScnRenderDrSysParmAcc parmAcc(Manager::get()->getScn()->unknown38, 0);
      parmAcc.deleteAddRenderView(unknown10[i]);
      if (unknown10[i] != nullptr) {
        delete unknown10[i];
        unknown10[i] = nullptr;
      }
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

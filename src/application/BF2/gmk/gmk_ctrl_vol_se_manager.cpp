#include "gmk/gmk_ctrl_vol_se.h"
#include "mm_mtl/intrusive_list.h"
#include "types.h"

namespace gmk {

void GmkCtrlVolSeManager::update(f32 deltaTime) {
  GmkCtrlVolSeManager *manager = get();
  manager->unknown20 = true;
  for (mm::mtl::IntrusiveList<GmkCtrlVolSe>::iterator it = manager->unknown08.begin(); it != manager->unknown08.end(); ++it) {
    it->update(deltaTime);
  }
  manager = get();
  manager->unknown20 = false;
  for (mm::mtl::IntrusiveList<GmkCtrlVolSe>::iterator it = manager->unknown08.begin(); it != get()->unknown08.end(); ++it) {
    if (it.get()->isPlayEnd()) {
      it = get()->unknown08.erase(it);
      --it;
    }
  }
}

} // namespace gmk

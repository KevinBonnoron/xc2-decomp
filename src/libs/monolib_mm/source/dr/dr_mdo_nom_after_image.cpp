#include "dr/dr_mdo_nom_after_image.h"

#include "dr/dr_man.h"
#include "dr/dr_mdo_ctl_nom.h"
#include "mtl/mem_manager.h"

namespace ml {

DrMdoNomAfterImage::DrMdoNomAfterImage() : unknown54(false), unknownd4(0) {
  unknown00 = nullptr;
  unknown08 = 0;
  unknown0a = 0;
  unknown20 = 0;
}

DrMdoNomAfterImage::~DrMdoNomAfterImage() { release(); }

void DrMdoNomAfterImage::release() {
  if (unknown08 != 0) {
    for (int i = 0; i < unknown08; i++) {
      unknown00[i].unknown10->setDeleteCall(DrMan::s_nDblStockIdx);
    }
    unknown08 = 0;
    if (unknown00 != nullptr) {
      mtl::MemManager::deallocate(unknown00, 0, false);
      unknown00 = nullptr;
    }
  }
}

u32 DrMdoNomAfterImage::isReleaseCall() const { return unknown20 & (1 << DrMan::s_nDblMemIdx); }

void DrMdoNomAfterImage::releaseCall() { unknown20 |= 1 << DrMan::s_nDblStockIdx; }

} // namespace ml

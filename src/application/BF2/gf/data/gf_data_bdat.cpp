#include "gf/data/gf_data_bdat.h"
#include "fw/fw_bdat_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

bool GfDataBdat::isInitialized() { return get() != nullptr && get()->mInitialized; }

bool GfDataBdat::loadBdat(const char *name, u32 bdat) {
  mm::mtl::FixStr<64> path;
  path.format("%s.bdat", name);
  return fw::BdatManager::loadBdat(bdat, getAllocator(ALLOCATOR_BDAT)->getMemHandle(), path.c_str());
}

bool GfDataBdat::isBdatLoading(u32 bdat) const { return !fw::BdatManager::isEnableBdat(bdat); }

void GfDataBdat::destroyBdat(u32 bdat) { fw::BdatManager::unregistBdat(bdat); }

u8 *GfDataBdat::getFP(u32 bdat) { return bdat < BDAT_COUNT ? get()->mFps[bdat] : nullptr; }

void GfDataBdat::gevReloadBdat(RELOAD_BDAT reload, u32 value) {
  if (reload == RELOAD_BDAT_ALL) {
    for (IDataBdat **listener = mListeners.begin(); listener != mListeners.end(); ++listener) {
      (*listener)->reloadBdat();
    }
  }
}

u32 GfDataBdat::getReloadCount() { return get()->mReloadCount; }

} // namespace gf

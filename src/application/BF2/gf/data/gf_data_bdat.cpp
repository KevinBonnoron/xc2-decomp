#include "gf/data/gf_data_bdat.h"

#include "fw/fw_bdat_manager.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace gf {

namespace _gfbdat {
extern const char *s_aszGfBdatName[];
}

constexpr u32 BDAT_LOOKAT = 15;

GfDataBdat::~GfDataBdat() {}

void GfDataBdat::destroy() {
  GfDataBdat *dataBdat = get();
  dataBdat->finalize();
  delete dataBdat;
}

void GfDataBdat::finalize() {
  for (IDataBdat **listener = unknownd00.begin(); listener != unknownd00.end(); ++listener) {
    if (*listener != nullptr) {
      delete *listener;
      *listener = nullptr;
    }
  }

  releaseBdatInfo();
  destroyBdat(BDAT_LOOKAT);
  GfEvent::removeEventCallback(this);
  unknowncfc = false;
}

bool GfDataBdat::isInitialized() { return get() != nullptr && get()->unknowncfc; }

bool GfDataBdat::loadBdat(const char *name, u32 bdat) {
  mm::mtl::FixStr<64> path;
  path.format("%s.bdat", name);
  return fw::BdatManager::loadBdat(bdat, getAllocator(ALLOCATOR_BDAT)->getMemHandle(), path.c_str());
}

bool GfDataBdat::isBdatLoading(u32 bdat) const { return !fw::BdatManager::isEnableBdat(bdat); }

void GfDataBdat::setupBdatInfo() {
  GfDataBdat *dataBdat = get();
  releaseBdatInfo();
  for (u32 bdat = 0; bdat < BDAT_COUNT; bdat++) {
    dataBdat->unknown10[bdat] = fw::BdatManager::getFp(_gfbdat::s_aszGfBdatName[bdat]);
  }

  dataBdat->unknowncf8++;
}

void GfDataBdat::releaseBdatInfo() {
  GfDataBdat *dataBdat = get();
  for (u32 bdat = 0; bdat < BDAT_COUNT; bdat++) {
    dataBdat->unknown10[bdat] = nullptr;
  }
}

void GfDataBdat::destroyBdat(u32 bdat) { fw::BdatManager::unregistBdat(bdat); }

u8 *GfDataBdat::getFP(u32 bdat) { return bdat < BDAT_COUNT ? get()->unknown10[bdat] : nullptr; }

void GfDataBdat::gevReloadBdat(RELOAD_BDAT reload, u32 value) {
  if (reload == RELOAD_BDAT_ALL) {
    for (IDataBdat **listener = unknownd00.begin(); listener != unknownd00.end(); ++listener) {
      (*listener)->reloadBdat();
    }
  }
}

u32 GfDataBdat::getReloadCount() { return get()->unknowncf8; }

} // namespace gf

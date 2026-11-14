#include "gf/data/gf_data_bdat.h"

#include "fw/fw_bdat_manager.h"
#include "gf/data/gf_bdat_bgm.h"
#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrbl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_lookat.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_bdat_shop.h"
#include "gf/data/gf_bdat_unique_motion.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace gf {

namespace _gfbdat {
extern const char *s_aszGfBdatName[];
}

constexpr u32 BDAT_UNKNOWN_15 = 15; // Inferred role: bdat lookat; original name unknown.

GfDataBdat::GfDataBdat(const GfSetupParam &param) : unknowncf8(0), unknowncfc(false) { initialize(param); }

void GfDataBdat::build(const GfSetupParam &param) {
// __LINE__ of the operator new call is 0x1f7 in the game.
#line 503
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfDataBdat(param);
}

void GfDataBdat::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  loadBdat("lookat", BDAT_UNKNOWN_15);
  while (isBdatLoading(BDAT_UNKNOWN_15)) {
    GfSleep(1);
  }
  setupBdatInfo();
// __LINE__ of the first operator new call is 0x223 in the game.
#line 547
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatQuest());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatBlade());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatItem());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatCond());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatMaplist());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatChrDr());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatChrBl());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatBgm());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatChrEnArrange());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatChrEnParam());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatRsc());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatBtl());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatMsg());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatLookAt());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatShop());
  unknownd00.push_back(new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfBdatUniqueMotion());
  unknowncfc = true;
}

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
  destroyBdat(BDAT_UNKNOWN_15);
  GfEvent::removeEventCallback(this);
  unknowncfc = false;
}

bool GfDataBdat::isInitialized() { return get() != nullptr && get()->unknowncfc; }

bool GfDataBdat::loadBdat(const char *name, u32 bdat) {
  mm::mtl::FixStr<64> path;
  path.format("%s.bdat", name);
  return fw::BdatManager::loadBdat(bdat, getAllocator(ALLOCATOR_UNKNOWN_4)->getMemHandle(), path.c_str());
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
  if (reload == RELOAD_BDAT_UNKNOWN_1) {
    for (IDataBdat **listener = unknownd00.begin(); listener != unknownd00.end(); ++listener) {
      (*listener)->bdatRefresh();
    }
  }
}

u32 GfDataBdat::getReloadCount() { return get()->unknowncf8; }

} // namespace gf

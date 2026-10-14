#pragma once
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GfSetupParam;

class IDataBdat {
public:
  virtual ~IDataBdat() {}
  virtual void reloadBdat() = 0;
};

class GfDataBdat : public mm::mtl::PtrSingleton<GfDataBdat>, public IGfEvent {
public:
  GfDataBdat(const GfSetupParam &param);
  virtual ~GfDataBdat();
  void initialize(const GfSetupParam &param);
  void gevReloadBdat(RELOAD_BDAT reload, u32 value) override;

  static void build(const GfSetupParam &param);
  static void destroy();
  static bool isInitialized();
  bool loadBdat(const char *name, u32 bdat);
  bool isBdatLoading(u32 bdat) const;
  void destroyBdat(u32 bdat);
  static u8 *getFP(u32 bdat);
  static u32 getReloadCount();

private:
  static const u32 BDAT_COUNT = 0x19d;

  u8 *mFps[BDAT_COUNT];
  u32 mReloadCount;
  bool mInitialized;
  mm::mtl::FixedVector<IDataBdat *, 128> mListeners;

  friend struct GfDataBdatLayout;
};

struct GfDataBdatLayout {
  static_assert(offsetof(GfDataBdat, mFps) == 0x10, "");
  static_assert(offsetof(GfDataBdat, mReloadCount) == 0xcf8, "");
  static_assert(offsetof(GfDataBdat, mInitialized) == 0xcfc, "");
  static_assert(offsetof(GfDataBdat, mListeners) == 0xd00, "");
  static_assert(sizeof(GfDataBdat) == 0x1108, "");
};

} // namespace gf

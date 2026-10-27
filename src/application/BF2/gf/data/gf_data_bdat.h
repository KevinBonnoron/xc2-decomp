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
  virtual void bdatRefresh() = 0;
};

class GfDataBdat : public mm::mtl::PtrSingleton<GfDataBdat>, public IGfEvent {
public:
  GfDataBdat(const GfSetupParam &param);
  virtual ~GfDataBdat();
  void initialize(const GfSetupParam &param);
  void gevReloadBdat(RELOAD_BDAT reload, u32 value) override;

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  bool loadBdat(const char *name, u32 bdat);
  bool isBdatLoading(u32 bdat) const;
  void destroyBdat(u32 bdat);
  static void setupBdatInfo();
  static void releaseBdatInfo();
  static u8 *getFP(u32 bdat);
  static u32 getReloadCount();

private:
  static const u32 BDAT_COUNT = 0x19d;

  u8 *unknown10[BDAT_COUNT];                         // Inferred role: fps; original member name unknown.
  u32 unknowncf8;                                    // Inferred role: reload count; original member name unknown.
  bool unknowncfc;                                   // Inferred role: initialized; original member name unknown.
  mm::mtl::FixedVector<IDataBdat *, 128> unknownd00; // Inferred role: listeners; original member name unknown.

  friend struct GfDataBdatLayout;
};

struct GfDataBdatLayout {
  static_assert(offsetof(GfDataBdat, unknown10) == 0x10, "");
  static_assert(offsetof(GfDataBdat, unknowncf8) == 0xcf8, "");
  static_assert(offsetof(GfDataBdat, unknowncfc) == 0xcfc, "");
  static_assert(offsetof(GfDataBdat, unknownd00) == 0xd00, "");
  static_assert(sizeof(GfDataBdat) == 0x1108, "");
};

} // namespace gf

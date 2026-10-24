#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_LP_HANDLE;
struct GfSetupParam;

class GfLayerPause : public mm::mtl::PtrSingleton<GfLayerPause> {
public:
  GfLayerPause(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfLayerPause();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  static void gevPause(u32 resumeBits, u32 pauseBits);
  static void destroyLayerPause(GF_LP_HANDLE *&handle);
  static GF_LP_HANDLE *setLayerPause(u32 layer);
  static void destroyLayerPause();
  static bool isLayerPause(u32 layer);

private:
  u32 *getPauseBits(u32 section) {
    switch (section) {
    case 0:
      return &unknown1c;
    case 1:
      return &unknown10;
    case 4:
      return &unknown0c;
    case 7:
      return &unknown14;
    case 10:
      return &unknown18;
    }
    return nullptr;
  }

  bool unknown08;          // Inferred role: initialized; original member name unknown.
  u32 unknown0c;           // Inferred role: section 4 pause bits; original member name unknown.
  u32 unknown10;           // Inferred role: section 1 pause bits; original member name unknown.
  u32 unknown14;           // Inferred role: section 7 pause bits; original member name unknown.
  u32 unknown18;           // Inferred role: section 10 pause bits; original member name unknown.
  u32 unknown1c;           // Inferred role: section 0 pause bits; original member name unknown.
  GF_LP_HANDLE *unknown20; // Inferred role: section 4 handle; original member name unknown.
  GF_LP_HANDLE *unknown28; // Inferred role: section 0 handle; original member name unknown.
  GF_LP_HANDLE *unknown30; // Inferred role: section 1 handle; original member name unknown.
  GF_LP_HANDLE *unknown38; // Inferred role: section 7 handle; original member name unknown.
  GF_LP_HANDLE *unknown40; // Inferred role: section 10 handle; original member name unknown.
};

static_assert(sizeof(GfLayerPause) == 0x48, "");

} // namespace gf

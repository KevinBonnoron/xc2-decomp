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
      return &section0PauseBits;
    case 1:
      return &section1PauseBits;
    case 4:
      return &section4PauseBits;
    case 7:
      return &section7PauseBits;
    case 10:
      return &section10PauseBits;
    }
    return nullptr;
  }

  bool initialized;
  u32 section4PauseBits;
  u32 section1PauseBits;
  u32 section7PauseBits;
  u32 section10PauseBits;
  u32 section0PauseBits;
  GF_LP_HANDLE *section4Handle;
  GF_LP_HANDLE *section0Handle;
  GF_LP_HANDLE *section1Handle;
  GF_LP_HANDLE *section7Handle;
  GF_LP_HANDLE *section10Handle;
};

static_assert(sizeof(GfLayerPause) == 0x48, "");

} // namespace gf

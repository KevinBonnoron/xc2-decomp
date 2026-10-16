#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfBladeManager : public mm::mtl::PtrSingleton<GfBladeManager> {
public:
  GfBladeManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfBladeManager();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void setupGame();
  static int getRandom(u32 max);
  static f32 getRandomF1();
  static bool isBindRareBladeCrystal(u32 item);

  bool initialized;
};

static_assert(offsetof(GfBladeManager, initialized) == 0x08, "");
static_assert(sizeof(GfBladeManager) == 0x10, "");

} // namespace gf

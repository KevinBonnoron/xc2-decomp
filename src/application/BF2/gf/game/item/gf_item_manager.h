#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

struct GfSetupParam;

class GfItemManager : public mm::mtl::PtrSingleton<GfItemManager> {
public:
  GfItemManager(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfItemManager();

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void clear();

  bool unknown08; // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(GfItemManager) == 0x10, "");

} // namespace gf

#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

class GfFileSizePool : public mm::mtl::PtrSingleton<GfFileSizePool> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  void update();
  u64 requestFileSize(const char *path);
  void recalcFileSizeCache(u64 handle, const char *path);
  bool getFileSize(int &size, u64 handle) const;
};

} // namespace gf

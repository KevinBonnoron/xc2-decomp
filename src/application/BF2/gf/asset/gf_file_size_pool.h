#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfFileSizePool : public mm::mtl::PtrSingleton<GfFileSizePool> {
public:
  u64 requestFileSize(const char *path);
  void recalcFileSizeCache(u64 handle, const char *path);
  bool getFileSize(int &size, u64 handle) const;
};

} // namespace gf

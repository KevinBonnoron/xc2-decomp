#pragma once
#include "fw/fw_render_resource.h"
#include "types.h"
#include <stddef.h>

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace event {

class PackHeader;

class StmPackHeader {
public:
  StmPackHeader();
  virtual ~StmPackHeader();
  void destroy();
  void create(mtl::ALLOC_HANDLE handle, const char *path);
  const char *getPath(size_t index) const;
  u32 getPrio(size_t index) const;
  size_t getDataOfs(size_t index) const;
  size_t getDataSize(size_t index) const;
  size_t getCount() const;
  bool isLoading() const;
  bool isFailure() const;

private:
  const PackHeader *getHeader() const { return static_cast<const PackHeader *>(unknown08->getAssetData()); }

  fw::RenderResource *unknown08; // Inferred role: resource; original member name unknown.
};

static_assert(sizeof(StmPackHeader) == 0x10, "");

} // namespace event

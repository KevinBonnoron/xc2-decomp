#pragma once
#include <stddef.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "grlib/cglib_mem_pool.h"
#include "nvn/nvn.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibTextureBuffer;

// Layout evidence: constructor 0x71007b2a24 (stores at 0x0, 0x8, 0x18, 0x30, 0x38 and 0x40), setup 0x71007b2c20
// (CGLibMemPool at 0x28, texture pool at 0x48) and the destructor 0x71007b2b48 which releases the pool and the
// fixed allocator table.
class CGLibTexDescriptor_plf : public CGLibBuffFixAlloc {
public:
  ~CGLibTexDescriptor_plf() {}
  void bindTexture(const CGLibTextureBuffer &texture, int textureId, int imageId);
  int setTexture(const CGLibTextureBuffer &texture);
  int setImage(const CGLibTextureBuffer &texture);

  CGLibMemPool unknown28;   // Inferred role: descriptor memory pool; original member name unknown.
  NVNtexturePool unknown48; // Inferred role: texture pool; original member name unknown.
};

static_assert(offsetof(CGLibTexDescriptor_plf, unknown28) == 0x28, "");
static_assert(offsetof(CGLibTexDescriptor_plf, unknown48) == 0x48, "");
static_assert(sizeof(CGLibTexDescriptor_plf) == 0x68, "");

class CGLibTexDescriptor : public CGLibTexDescriptor_plf {
public:
  CGLibTexDescriptor();
  ~CGLibTexDescriptor();
  void release();
  int setup(void *buffer, u32 num);
  int setup(mtl::ALLOC_HANDLE handle, u32 num);
  int setup(CGLibMemPool &memPool, u32 offset, u32 num);
  void reset();
  void bind();
};

static_assert(sizeof(CGLibTexDescriptor) == 0x68, "");

} // namespace grlib

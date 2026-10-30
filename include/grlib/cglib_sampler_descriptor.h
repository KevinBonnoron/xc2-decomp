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

class CGLibSampler;
class CGLibSamplerParam;

// Layout evidence: CGLibSamplerParam::setupResource 0x710079e59c and CGLibCtlTexture::setTexture 0x71007ab474 call
// bindSampler and setSampler on the sampler descriptor plus 0x28, and bindSampler 0x71007b3180 registers the sampler
// in the sampler pool at its offset 0x20 (offset 0x48 of CGLibSamplerDescriptor).
class CGLibSamplerDescriptor_plf {
public:
  void bindSampler(const CGLibSamplerParam &param, int samplerId);
  int setSampler(const CGLibSampler &sampler);

  CGLibMemPool unknown00;   // Inferred role: descriptor memory pool; original member name unknown.
  NVNsamplerPool unknown20; // Inferred role: sampler pool; original member name unknown.
};

static_assert(offsetof(CGLibSamplerDescriptor_plf, unknown20) == 0x20, "");
static_assert(sizeof(CGLibSamplerDescriptor_plf) == 0x40, "");

// Layout evidence: constructor 0x71007b2e44 (stores at 0x0, 0x8, 0x18, 0x30, 0x38 and 0x40), setup 0x71007b3020
// (CGLibMemPool at 0x28, sampler pool at 0x48) and release 0x71007b2f34.
class CGLibSamplerDescriptor : public CGLibBuffFixAlloc, public CGLibSamplerDescriptor_plf {
public:
  CGLibSamplerDescriptor();
  ~CGLibSamplerDescriptor();
  void release();
  int setup(void *buffer, u32 num);
  int setup(mtl::ALLOC_HANDLE handle, u32 num);
  int setup(CGLibMemPool &memPool, u32 offset, u32 num);
  void reset();
  void bind();
};

static_assert(sizeof(CGLibSamplerDescriptor) == 0x68, "");

} // namespace grlib

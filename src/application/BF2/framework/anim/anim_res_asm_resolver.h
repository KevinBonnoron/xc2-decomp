#pragma once
#include <stddef.h>

#include "anm/anm_mirror_mapper.h"
#include "anm/anm_res_resolver.h"
#include "anm/anm_simple_mapper.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace arc {
class CArcData;
} // namespace arc

namespace anm {
class Skeleton;
} // namespace anm

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class AnimResAsmResolver : public anm::ResResolver {
public:
  AnimResAsmResolver(mm::mtl::IAllocator &allocator);
  ~AnimResAsmResolver();
  const anm::Binding *importBinding(const char *name, u32 id) const override;
  void restoreBinding(const char *name, u32 id) const override;
  const anm::Skeleton *getSkekelton() const override;
  anm::MirrorMapper *getMirrorMapper() const override;
  anm::SimpleMapper *getSimpleMapper() const override;

  mm::mtl::Vector<arc::CArcData> unknown08; // Inferred role: archives of the animation packs; original member name unknown.
  const anm::Skeleton *unknown30;           // Inferred role: skeleton; original member name unknown.
  anm::MirrorMapper *unknown38;             // Inferred role: mirror mapper; original member name unknown.
  anm::SimpleMapper *unknown40;             // Inferred role: simple mapper; original member name unknown.
  mm::mtl::IAllocator *unknown48;           // Inferred role: allocator of the mappers; original member name unknown.
};

static_assert(offsetof(AnimResAsmResolver, unknown08) == 0x08, "");
static_assert(offsetof(AnimResAsmResolver, unknown30) == 0x30, "");
static_assert(offsetof(AnimResAsmResolver, unknown38) == 0x38, "");
static_assert(offsetof(AnimResAsmResolver, unknown40) == 0x40, "");
static_assert(offsetof(AnimResAsmResolver, unknown48) == 0x48, "");

} // namespace fw

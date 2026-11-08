#include "framework/anim/anim_res_asm_resolver.h"

#include "anm/anm_mirror_mapper.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_simple_mapper.h"
#include "arc/arc_data.h"

namespace fw {

AnimResAsmResolver::AnimResAsmResolver(mm::mtl::IAllocator &allocator) : unknown08(&allocator), unknown30(nullptr), unknown38(nullptr), unknown40(nullptr), unknown48(&allocator) {}

AnimResAsmResolver::~AnimResAsmResolver() {
  anm::unknown001(unknown38);
  anm::unknown001(unknown40);
}

const anm::Skeleton *AnimResAsmResolver::getSkekelton() const { return unknown30; }

anm::MirrorMapper *AnimResAsmResolver::getMirrorMapper() const { return unknown38; }

anm::SimpleMapper *AnimResAsmResolver::getSimpleMapper() const { return unknown40; }

} // namespace fw

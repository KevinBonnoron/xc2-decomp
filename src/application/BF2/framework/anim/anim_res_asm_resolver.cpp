#include "framework/anim/anim_res_asm_resolver.h"

#include "anm/anm_animation_importer.h"
#include "anm/anm_mirror_mapper.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_simple_mapper.h"
#include "arc/arc_data.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep

namespace fw {

AnimResAsmResolver::AnimResAsmResolver(mm::mtl::IAllocator &allocator) : unknown08(&allocator), m_skekelton(nullptr), m_mirrorMapper(nullptr), m_simpleMapper(nullptr), unknown48(&allocator) {}

AnimResAsmResolver::~AnimResAsmResolver() {
  anm::unknown001(m_mirrorMapper);
  anm::unknown001(m_simpleMapper);
}

const anm::Binding *AnimResAsmResolver::importBinding(const char *name, u32 id) const {
  if (name != nullptr && unknown08[id].unknown00 != nullptr) {
    void *data = unknown08[id].getFileAdr(name);
    if (data != nullptr) {
      return anm::AnimationImporter::import(data);
    }
  }
  return nullptr;
}

const anm::Skeleton *AnimResAsmResolver::getSkekelton() const { return m_skekelton; }

anm::MirrorMapper *AnimResAsmResolver::getMirrorMapper() const { return m_mirrorMapper; }

anm::SimpleMapper *AnimResAsmResolver::getSimpleMapper() const { return m_simpleMapper; }

} // namespace fw

// The game instantiates these where AnimResAsmResolver::resolvePackFiles uses them, calling CArcData::CArcData(void *) out of line:
// they cannot sit in arc_data.cpp, which defines that constructor and would inline it.
template void mm::mtl::Vector<arc::CArcData>::extend(size_t, size_t);
template void mm::mtl::Vector<arc::CArcData>::resize(size_t);

#include "anm/anm_binding.h"

#include "anm/anm_animation.h"

namespace anm {

Binding::Binding(mm::mtl::IAllocator *pAllocator) : ReferenceObject(pAllocator) {}

Binding::~Binding() { unknown001(m_pAnimation); }

} // namespace anm

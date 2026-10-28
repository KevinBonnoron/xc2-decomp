#include "anm/anm_binding.h"

#include <new>

#include "anm/anm_animation.h"

namespace anm {

Binding::Binding(mm::mtl::IAllocator *pAllocator) : ReferenceObject(pAllocator) {}

Binding::Binding(const SerialiseArg &arg) : ReferenceObject(arg), m_indexTable(arg), unknown30(arg) {
  ExtraBinding *elements = unknown30.m_pElements;
  for (u32 i = 0; i < unknown30.size(); i++) {
    new (&elements[i]) ExtraBinding(arg);
  }
}

Binding::~Binding() { unknown001(m_pAnimation); }

} // namespace anm

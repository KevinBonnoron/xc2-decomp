#include "anm/anm_control.h"

#include "anm/anm_animation.h"
#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_util.h"
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

Control::Control(const Binding *pBinding, mm::mtl::IAllocator *pAllocator)
    : ReferenceObject(pAllocator), m_pBinding(pBinding), unknown20(pAllocator), unknown48(0.0f), unknown4c(1.0f), unknown50(1.0f), unknown58(0), unknown60(nullptr) {
  MM_ASSERT(pBinding);
  pBinding->addRef();
  u32 count = m_pBinding->m_indexTable.size();
  unknown20.reserve(count);
  for (u32 i = 0; i < count; i++) {
    if (m_pBinding->m_indexTable[i] == -1) {
      unknown20.push_back(0.0f);
    } else {
      unknown20.push_back(1.0f);
    }
  }
  unknown54 = m_pBinding->m_pAnimation->unknown28 * (m_pBinding->m_pAnimation->unknown2c - 1);
}

Control::~Control() { unknown001(m_pBinding); }

void Control::sampleTrucks(u32 count, QsTransform *transforms) const {
  MM_ASSERT(count == m_pBinding->m_indexTable.size());
  m_pBinding->m_pAnimation->sampleTrucks(unknown48, *m_pBinding, transforms);
}

bool Control::sampleExtraTrucks(u16 slot, u32 count, f32 *values) {
  MM_ASSERT(m_pBinding);
  if (m_pBinding->unknown30.size() != 0) {
    const ExtraBinding &extraBinding = m_pBinding->unknown30[slot];
    if (extraBinding.unknown08.size() == count) {
      const unknown002 *extraTruck = extraBinding.unknown00;
      if (extraTruck == nullptr) {
        return false;
      }
      extraTruck->sampleTrucks(unknown48, *m_pBinding, extraBinding, count, values);
      return true;
    }
  }
  return false;
}

void Control::getDeltaExtractMotion(f32 time, QsTransform *transform) const {
  MM_ASSERT(m_pBinding);
  const Animation *pAnimation = m_pBinding->m_pAnimation;
  MM_ASSERT(pAnimation);
  pAnimation->getDeltaExtractMotion(unknown48, time, pAnimation->unknown22 == PLAY_MODE_LOOP, transform);
}

const char *Control::getName() const {
  MM_ASSERT(m_pBinding);
  const Animation *pAnimation = m_pBinding->m_pAnimation;
  MM_ASSERT(pAnimation);
  return pAnimation->unknown18;
}

} // namespace anm

template void mm::mtl::Vector<f32>::expand(size_t, size_t);

#include "anm/anm_control.h"

#include <algorithm>
#include <math.h>

#include "anm/anm_animation.h"
#include "anm/anm_array-inl.h"
#include "anm/anm_array.h"
#include "anm/anm_binding.h"
#include "anm/anm_extra_truck.h"
#include "anm/anm_util.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_math.h"

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

struct CmpAnnotetion {
  bool operator()(const Annotetion &annotation, f32 frame) const { return annotation.unknown00 < frame; }
};

void Control::procAnnotetionCallBack(f32 time, f32 deltaTime, bool includeStart) {
  if (unknown60 == nullptr) {
    return;
  }
  const Animation *pAnimation = m_pBinding->m_pAnimation;
  if (pAnimation->unknown38 == 0) {
    return;
  }
  f32 frame = pAnimation->unknown24 * time;
  ArrayIterartor<const Annotetion> found = std::lower_bound(ArrayIterartor<const Annotetion>(static_cast<const Annotetion *>(pAnimation->unknown30)),
                                                            ArrayIterartor<const Annotetion>(static_cast<const Annotetion *>(pAnimation->unknown30) + pAnimation->unknown38),
                                                            frame,
                                                            CmpAnnotetion());
  ArrayIterartor<const Annotetion> last(static_cast<const Annotetion *>(pAnimation->unknown30) + pAnimation->unknown38);
  ArrayIterartor<const Annotetion> it = found;
  if (includeStart) {
    while (it != last && found->unknown00 == frame) {
      unknown60->unknown00(&*it);
      ++it;
    }
  }
  f32 end = calcLocalTimeInternal(time + deltaTime) * pAnimation->unknown24;
  f32 lastFrame = pAnimation->unknown2c;
  f32 endFrame = end < lastFrame ? end : lastFrame;
  for (; found != last && frame < found->unknown00 && found->unknown00 <= endFrame; ++found) {
    unknown60->unknown00(&*found);
  }
  if (frame > end) {
    for (ArrayIterartor<const Annotetion> p(static_cast<const Annotetion *>(pAnimation->unknown30)); p != last && p->unknown00 <= end; ++p) {
      unknown60->unknown00(&*p);
    }
  }
}

void Control::update(f32 deltaTime) {
  unknown48 += unknown50 * deltaTime;
  unknown48 = calcLocalTimeInternal(unknown48);
}

f32 Control::calcLocalTimeInternal(f32 time) {
  if (m_pBinding->m_pAnimation->unknown22 == PLAY_MODE_LOOP) {
    f32 localTime = fmodf(time, unknown54);
    if (localTime < 0.0f) {
      localTime = localTime + unknown54;
    }
    return localTime;
  }
  return mm::clamp(time, 0.0f, unknown54);
}

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

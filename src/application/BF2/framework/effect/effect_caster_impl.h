#pragma once
#include "framework/effect/effect_caster.h"
#include "framework/memory/framework_memory.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

// The game defines create in this header (the line argument 196 and the file name of its operator new call, 1.0.0: 0x710016aadc).
#line 195
EffectCasterSend *EffectCasterSend::create(EffectCasterBase *caster, mm::mtl::IAllocator *allocator, u32 count) {
  EffectCasterSend *send = new (allocator, 16, __FILE__, __LINE__) EffectCasterSend(allocator);
  if (send != nullptr) {
    send->m_caster = caster;
    send->unknown18[0].reserve(count, 16);
    send->unknown18[1].reserve(count, 16);
    // The game pushes an entry it never writes (an uninitialised stack buffer copied into both vectors, 1.0.0: 0x710016aadc).
    MtxAndName data;
    for (u32 i = count; i != 0; i--) {
      send->unknown18[0].push_back(data);
      send->unknown18[1].push_back(data);
    }
  }
  return send;
}

} // namespace fw

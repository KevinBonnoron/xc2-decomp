#pragma once
#include <stddef.h>

#include "framework/effect/effect_caster.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace gf {

class GfComEffectCaster;

// Layout evidence: GfComEffectCaster::setupCaster (0x71005062c4) allocates 0xb0 bytes with the vtable gf::EffectCaster (_ZTVN2gf12EffectCasterE, 0x710119ba20, loaded through the GOT slot
// 0x71011c2700), derived from fw::EffectCasterBase. EffectCaster::update (0x710050a77c) reads the matrix at 0x60 and multiplies it into the point transforms, EffectCaster::postUpdate (0x710050adf0)
// calls apply and applyEvent of the owner at 0x58 and copies the matrix at 0x60 into fw::EffectManager when the byte at 0xa0 is set, and GfComEffectCaster::getEfpMatrix (0x7100507848) multiplies a
// point transform with the matrix. The virtual overrides update, postUpdate and the destructor (D0 0x710050ae80) are not declared: none of them is matched yet.
class EffectCaster : public fw::EffectCasterBase {
public:
  u8 _48[0x58 - 0x48];
  GfComEffectCaster *unknown58; // Inferred role: owner component; original member name unknown.
  mm::Mat44 unknown60;          // Inferred role: root matrix of the caster; original member name unknown.
  bool unknowna0;               // Inferred role: copy the matrix into the effect manager; original member name unknown.
  u8 _a1[0xb0 - 0xa1];
};

static_assert(offsetof(EffectCaster, unknown58) == 0x58, "");
static_assert(offsetof(EffectCaster, unknown60) == 0x60, "");
static_assert(offsetof(EffectCaster, unknowna0) == 0xa0, "");
static_assert(sizeof(EffectCaster) == 0xb0, "");

} // namespace gf

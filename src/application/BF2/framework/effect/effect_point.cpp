#include "framework/effect/effect_caster.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/delegate.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/hash.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {

EffectPoint::~EffectPoint() {
  for (u32 i = 0; i < unknown10.size(); i++) {
    unknown88(unknown10[i].unknown80.c_str());
  }
  unknown10.destroy();
  unknown38.destroy();
}

int EffectPoint::getPointCount() const { return unknown10.size(); }

int EffectPoint::getPointIndex(const char *name) const {
  if (unknown10.size() != 0) {
    u32 hash = mm::mtl::hashStrCrc(name);
    for (u32 i = 0; i < unknown10.size(); i++) {
      if (hash == unknown10[i].unknown7c && __builtin_strcmp(name, unknown10[i].unknown58.c_str()) == 0) {
        return i;
      }
    }
  }

  return -1;
}

const char *EffectPoint::getPointName(int index) const {
  if (index < 0 || index >= getPointCount()) {
    return nullptr;
  }

  return unknown10[index].unknown58.c_str();
}

const mm::Mat44 &EffectPoint::getPointTransform(int index) const {
  if (index < 0 || index >= getPointCount()) {
    return mm::Mat44::identity;
  }

  return unknown38[index];
}

const mm::Vec3 &EffectPoint::getScale(int index) const {
  if (index < 0 || index >= getPointCount()) {
    return mm::Vec3::unit;
  }

  return unknown10[index].unknown40;
}

bool EffectPoint::isDirty(u32 index) { return unknown10[index].unknowna8; }

void EffectPoint::setDirty(u32 index, bool isDirty) {
  if (index < getPointCount()) {
    unknown10[index].unknowna8 = isDirty;
  }
}

const char *EffectPoint::getParentName(const char *name) {
  for (u32 i = 0; i < unknown10.size(); i++) {
    if (__builtin_strcmp(unknown10[i].unknown58.c_str(), name) == 0) {
      return unknown10[i].unknown80.c_str();
    }
  }

  return nullptr;
}

mm::Mat44 EffectPoint::getOffset(const char *name) {
  mm::Mat44 matrix;
  for (u32 i = 0; i < unknown10.size(); i++) {
    if (__builtin_strcmp(unknown10[i].unknown58.c_str(), name) == 0) {
      matrix.unknown006(unknown10[i].unknown00);
      return matrix;
    }
  }

  matrix = mm::Mat44::identity;
  return matrix;
}

} // namespace fw

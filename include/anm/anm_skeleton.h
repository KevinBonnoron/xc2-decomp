#pragma once
#include <stddef.h>
#include <string.h>

#include "anm/anm_array-inl.h"
#include "types.h"

namespace anm {

class Skeleton {
public:
  static const u16 INVALID_BONE = 0xffff;

  struct Bone {
    const char *name;
    u8 _08[0x10 - 0x08];
  };

  u16 getBoneID(const char *name) const {
    for (u32 i = 0; i < bones.size(); i++) {
      if (strcmp(name, bones[i].name) == 0) {
        return i;
      }
    }

    return INVALID_BONE;
  }

  u8 _00[0x30 - 0x00];
  Array<Bone> bones;
};

static_assert(sizeof(Skeleton::Bone) == 0x10, "");
static_assert(offsetof(Skeleton, bones) == 0x30, "");

} // namespace anm

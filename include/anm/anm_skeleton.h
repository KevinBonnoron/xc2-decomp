#pragma once
#include <stddef.h>
#include <string.h>

#include "anm/anm_array-inl.h"
#include "anm/anm_reference_object.h"
#include "types.h"

namespace anm {

class ExtraTruckSlot;
struct QsTransform;

class Skeleton : public ReferenceObject {
public:
  static const u16 INVALID_BONE = 0xffff;

  struct Bone {
    const char *unknown00; // Inferred role: name; original member name unknown.
    u8 _08[0x10 - 0x08];
  };

  u16 getBoneID(const char *name) const {
    for (u32 i = 0; i < unknown30.size(); i++) {
      if (strcmp(name, unknown30[i].unknown00) == 0) {
        return i;
      }
    }

    return INVALID_BONE;
  }

  u16 getExtraTruckSlotID(const char *name) const;

  u8 _18[0x20 - 0x18];
  Array<s16> unknown20;            // Inferred role: parent bone indices; original member name unknown.
  Array<Bone> unknown30;           // Inferred role: bones; original member name unknown.
  Array<QsTransform> unknown40;    // Inferred role: reference pose; original member name unknown.
  Array<ExtraTruckSlot> unknown50; // Inferred role: extra truck slots; original member name unknown.
};

static_assert(sizeof(Skeleton::Bone) == 0x10, "");
static_assert(offsetof(Skeleton, unknown20) == 0x20, "");
static_assert(offsetof(Skeleton, unknown30) == 0x30, "");
static_assert(offsetof(Skeleton, unknown40) == 0x40, "");
static_assert(offsetof(Skeleton, unknown50) == 0x50, "");

} // namespace anm

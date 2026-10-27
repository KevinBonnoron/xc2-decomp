#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gmk {

class GmkSet;

class GmkForm {
public:
  struct CreateInfo {
    GmkSet *unknown00; // Inferred role: gmk set; original member name unknown.
    u32 unknown08;     // Inferred role: gmk index; original member name unknown.
    bool unknown0c;    // Inferred role: event form; original member name unknown.
  };

  static const u32 MAX_NUM = 6;

  explicit GmkForm(const CreateInfo *info);
  bool create(const CreateInfo &info);
  bool create(const mm::Vec3 &position, f32 rotationY);
  template <typename FORM_PC, typename FORM_PCNPC> bool create(const FORM_PC &formPc);
  void dispose();
  void getPosRotY(mm::Vec3 &position, f32 &rotationY, u32 index) const;
  void validatePosRotY();
  void apply(f32 snapDistance);

  u32 unknown00;               // Inferred role: number of members; original member name unknown.
  mm::Vec3 unknown10[MAX_NUM]; // Inferred role: positions; original member name unknown.
  f32 unknown70[MAX_NUM];      // Inferred role: rotations around Y; original member name unknown.
  u8 _88[0x90 - 0x88];
};

static_assert(offsetof(GmkForm, unknown10) == 0x10, "");
static_assert(offsetof(GmkForm, unknown70) == 0x70, "");
static_assert(sizeof(GmkForm) == 0x90, "");

} // namespace gmk

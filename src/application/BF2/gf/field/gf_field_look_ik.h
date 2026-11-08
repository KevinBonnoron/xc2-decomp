#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {

struct GF_OBJ_HANDLE;

class GfFieldLookIk {
public:
  GfFieldLookIk(GF_OBJ_HANDLE *handle);
  ~GfFieldLookIk() { dispose(); }
  void create(GF_OBJ_HANDLE *handle);
  void create(GF_OBJ_HANDLE *handle, const CBdatWrapper &bdat, int id);
  void dispose();
  void update(f32 deltaTime);
  template <typename T> void updateIkSolver(T &solver);
  bool isCondMatched() const;
  bool isCondMatched(const mm::Vec3 &target) const;
  bool findTargetPos(mm::Vec3 &position) const;
  bool findPos(mm::Vec3 &position) const;

  GF_OBJ_HANDLE *unknown00 = INVALID_HANDLE; // Inferred role: object; original member name unknown.
  u32 unknown08 = 3;                         // Inferred role: slot of the look solver in the ik solver vector; original member name unknown.
  f32 unknown0c = 5.0f;                      // Inferred role: distance range; original member name unknown.
  f32 unknown10 = 2.3561945f;                // Inferred role: horizontal angle range; original member name unknown.
  f32 unknown14 = 1.0471976f;                // Inferred role: vertical angle range; original member name unknown.
  f32 unknown18 = 0.7f;                      // Inferred role: fade time; original member name unknown.
  bool unknown1c = true;                     // Inferred role: enabled; original member name unknown.
  mm::Vec3 unknown20 = mm::Vec3::zero;       // Inferred role: current target; original member name unknown.
  bool unknown30 = false;                    // Inferred role: condition matched; original member name unknown.
};

static_assert(offsetof(GfFieldLookIk, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldLookIk, unknown0c) == 0x0c, "");
static_assert(offsetof(GfFieldLookIk, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldLookIk, unknown14) == 0x14, "");
static_assert(offsetof(GfFieldLookIk, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldLookIk, unknown1c) == 0x1c, "");
static_assert(offsetof(GfFieldLookIk, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldLookIk, unknown30) == 0x30, "");
static_assert(sizeof(GfFieldLookIk) == 0x40, "");

} // namespace gf

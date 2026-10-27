#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrMan;

class DrEnvColiObj {
public:
  DrEnvColiObj(DrMan *man);
  ~DrEnvColiObj();
  void release();
  void setPause(bool isPause);
  bool isPause() const;
  u32 isDeleteCall() const;
  u32 isDeleteAll() const;
  bool envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes);
  bool envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center);
  bool envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes);
  bool envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center);
  bool envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center);

  void *unknown00; // Inferred role: unused data; original member name unknown.
  void *unknown08; // Inferred role: unused data; original member name unknown.
  void *unknown10; // Inferred role: env coli data; original member name unknown.
  u8 _18[0x28 - 0x18];
  void *unknown28;  // Inferred role: unused data; original member name unknown.
  DrMan *unknown30; // Inferred role: dr man; original member name unknown.
  u32 unknown38;    // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrEnvColiObj, unknown10) == 0x10, "");
static_assert(offsetof(DrEnvColiObj, unknown28) == 0x28, "");
static_assert(offsetof(DrEnvColiObj, unknown30) == 0x30, "");
static_assert(offsetof(DrEnvColiObj, unknown38) == 0x38, "");

} // namespace ml

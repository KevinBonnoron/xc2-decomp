#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DrIBLColiAcc {
public:
  bool envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin);
  bool envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin);
};

} // namespace ml

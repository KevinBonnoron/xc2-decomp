#include "dr/dr_ibl_coli_acc.h"

#include "mm_math/mm_vec3.h"

namespace ml {

namespace {

// Inferred role: collision sphere data; original type name unknown.
struct unknown001 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
};

// Inferred role: collision data of a non rotated cylinder; original type name unknown.
struct unknown002 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
  f32 unknown10;    // Inferred role: half height; original member name unknown.
};

// Inferred role: collision data of a non rotated box; original type name unknown.
struct unknown003 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
  f32 unknown10[3]; // Inferred role: half extents; original member name unknown.
};

// Inferred role: collision data of a rotated box or cylinder; original type name unknown.
struct unknown004 {
  f32 unknown00[3][4]; // Inferred role: axes; original member name unknown.
  f32 unknown30[3];    // Inferred role: center; original member name unknown.
  f32 unknown3c;       // Inferred role: radius; original member name unknown.
  f32 unknown40[3];    // Inferred role: half extents; original member name unknown.
};

} // namespace

bool DrIBLColiAcc::envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin) {
  const unknown004 *box = reinterpret_cast<const unknown004 *>(data);
  const f32 *center = box->unknown30;
  f32 dx = position.x - center[0];
  f32 dy = position.y - center[1];
  f32 dz = position.z - center[2];
  f32 radius = box->unknown3c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  f32 a = dx * box->unknown00[0][0] + dy * box->unknown00[1][0] + dz * box->unknown00[2][0];
  if (!(box->unknown40[0] + margin >= a)) {
    return false;
  }
  if (!(-box->unknown40[0] - margin <= a)) {
    return false;
  }
  f32 c = dx * box->unknown00[0][2] + dy * box->unknown00[1][2] + dz * box->unknown00[2][2];
  if (!(box->unknown40[2] + margin >= c)) {
    return false;
  }
  if (!(-box->unknown40[2] - margin <= c)) {
    return false;
  }
  f32 b = dx * box->unknown00[0][1] + dy * box->unknown00[1][1] + dz * box->unknown00[2][1];
  if (!(box->unknown40[1] + margin >= b)) {
    return false;
  }
  return -box->unknown40[1] - margin <= b;
}

bool DrIBLColiAcc::envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin) {
  const unknown001 *sphere = reinterpret_cast<const unknown001 *>(data);
  f32 dx = position.x - sphere->unknown00[0];
  f32 dy = position.y - sphere->unknown00[1];
  f32 dz = position.z - sphere->unknown00[2];
  return dx * dx + dy * dy + dz * dz <= (sphere->unknown0c + margin) * (sphere->unknown0c + margin);
}

bool DrIBLColiAcc::envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin) {
  const unknown004 *cylinder = reinterpret_cast<const unknown004 *>(data);
  const f32 *center = cylinder->unknown30;
  f32 dx = position.x - center[0];
  f32 dy = position.y - center[1];
  f32 dz = position.z - center[2];
  f32 radius = cylinder->unknown3c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  f32 height = dx * cylinder->unknown00[0][1] + dy * cylinder->unknown00[1][1] + dz * cylinder->unknown00[2][1];
  if (!(cylinder->unknown40[1] + margin >= height)) {
    return false;
  }
  if (!(-cylinder->unknown40[1] - margin <= height)) {
    return false;
  }
  f32 a = dx * cylinder->unknown00[0][0] + dy * cylinder->unknown00[1][0] + dz * cylinder->unknown00[2][0];
  f32 b = dx * cylinder->unknown00[0][2] + dy * cylinder->unknown00[1][2] + dz * cylinder->unknown00[2][2];
  f32 limit = cylinder->unknown40[0] + margin;
  return a * a + b * b <= limit * limit;
}

bool DrIBLColiAcc::envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin) {
  const unknown003 *box = reinterpret_cast<const unknown003 *>(data);
  f32 dx = position.x - box->unknown00[0];
  f32 dy = position.y - box->unknown00[1];
  f32 dz = position.z - box->unknown00[2];
  f32 radius = box->unknown0c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  if (!(box->unknown10[0] + margin >= dx)) {
    return false;
  }
  if (!(-box->unknown10[0] - margin <= dx)) {
    return false;
  }
  if (!(box->unknown10[2] + margin >= dz)) {
    return false;
  }
  if (!(-box->unknown10[2] - margin <= dz)) {
    return false;
  }
  if (!(box->unknown10[1] + margin >= dy)) {
    return false;
  }
  return -box->unknown10[1] - margin <= dy;
}

bool DrIBLColiAcc::envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin) {
  const unknown002 *cylinder = reinterpret_cast<const unknown002 *>(data);
  f32 dy = position.y - cylinder->unknown00[1];
  if (!(cylinder->unknown10 + margin >= dy)) {
    return false;
  }
  if (!(-cylinder->unknown10 - margin <= dy)) {
    return false;
  }
  f32 dx = position.x - cylinder->unknown00[0];
  f32 dz = position.z - cylinder->unknown00[2];
  return dx * dx + dz * dz <= (cylinder->unknown0c + margin) * (cylinder->unknown0c + margin);
}

} // namespace ml

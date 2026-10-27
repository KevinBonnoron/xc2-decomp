#include "dr/dr_calc_clip_obj.h"

#include "dr/dr_man.h"
#include "mm_math/mm_vec3.h"

namespace ml {

namespace {

// Inferred role: clip sphere data; original type name unknown.
struct unknown001 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: squared radius; original member name unknown.
};

// Inferred role: clip data of a non rotated cylinder; original type name unknown.
struct unknown002 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: squared radius; original member name unknown.
  f32 unknown10;    // Inferred role: half height; original member name unknown.
};

// Inferred role: clip data of a non rotated box; original type name unknown.
struct unknown003 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: squared radius; original member name unknown.
  f32 unknown10[3]; // Inferred role: half extents; original member name unknown.
};

// Inferred role: clip data of a rotated box or cylinder; original type name unknown.
struct unknown004 {
  f32 unknown00[3][4]; // Inferred role: axes; original member name unknown.
  f32 unknown30[3];    // Inferred role: center; original member name unknown.
  f32 unknown3c;       // Inferred role: squared radius; original member name unknown.
  f32 unknown40[3];    // Inferred role: half extents; original member name unknown.
};

} // namespace

void DrCalcClipObj::release() { unknown3c |= 1 << DrMan::s_nDblStockIdx; }

bool DrCalcClipObj::clipcoli_sphere(const u8 *data, const mm::Vec3 &pos) {
  const unknown001 *sphere = reinterpret_cast<const unknown001 *>(data);
  f32 dx = pos.x - sphere->unknown00[0];
  f32 dy = pos.y - sphere->unknown00[1];
  f32 dz = pos.z - sphere->unknown00[2];
  return dx * dx + dy * dy + dz * dz <= sphere->unknown0c;
}

bool DrCalcClipObj::clipcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &pos) {
  const unknown002 *cylinder = reinterpret_cast<const unknown002 *>(data);
  f32 dy = pos.y - cylinder->unknown00[1];
  if (!(cylinder->unknown10 >= dy && dy >= -cylinder->unknown10)) {
    return false;
  }
  f32 dx = pos.x - cylinder->unknown00[0];
  f32 dz = pos.z - cylinder->unknown00[2];
  return dx * dx + dz * dz <= cylinder->unknown0c;
}

bool DrCalcClipObj::clipcoli_notrot_box(const u8 *data, const mm::Vec3 &pos) {
  const unknown003 *box = reinterpret_cast<const unknown003 *>(data);
  f32 dx = pos.x - box->unknown00[0];
  f32 dy = pos.y - box->unknown00[1];
  f32 dz = pos.z - box->unknown00[2];
  if (!(dx * dx + dy * dy + dz * dz <= box->unknown0c)) {
    return false;
  }
  if (!(box->unknown10[0] >= dx && dx >= -box->unknown10[0])) {
    return false;
  }
  if (!(box->unknown10[2] >= dz && dz >= -box->unknown10[2])) {
    return false;
  }
  if (!(box->unknown10[1] >= dy)) {
    return false;
  }
  return -box->unknown10[1] <= dy;
}

bool DrCalcClipObj::clipcoli_cylinder(const u8 *data, const mm::Vec3 &pos) {
  const unknown004 *cylinder = reinterpret_cast<const unknown004 *>(data);
  f32 dx = pos.x - cylinder->unknown30[0];
  f32 dy = pos.y - cylinder->unknown30[1];
  f32 dz = pos.z - cylinder->unknown30[2];
  if (!(dx * dx + dy * dy + dz * dz <= cylinder->unknown3c)) {
    return false;
  }
  f32 height = dx * cylinder->unknown00[0][1] + dy * cylinder->unknown00[1][1] + dz * cylinder->unknown00[2][1];
  if (!(cylinder->unknown40[1] >= height && height >= -cylinder->unknown40[1])) {
    return false;
  }
  f32 a = dx * cylinder->unknown00[0][0] + dy * cylinder->unknown00[1][0] + dz * cylinder->unknown00[2][0];
  f32 b = dx * cylinder->unknown00[0][2] + dy * cylinder->unknown00[1][2] + dz * cylinder->unknown00[2][2];
  return a * a + b * b <= cylinder->unknown40[0];
}

bool DrCalcClipObj::clipcoli_box(const u8 *data, const mm::Vec3 &pos) {
  const unknown004 *box = reinterpret_cast<const unknown004 *>(data);
  f32 dx = pos.x - box->unknown30[0];
  f32 dy = pos.y - box->unknown30[1];
  f32 dz = pos.z - box->unknown30[2];
  if (!(dx * dx + dy * dy + dz * dz <= box->unknown3c)) {
    return false;
  }
  f32 a = dx * box->unknown00[0][0] + dy * box->unknown00[1][0] + dz * box->unknown00[2][0];
  if (!(box->unknown40[0] >= a && a >= -box->unknown40[0])) {
    return false;
  }
  f32 c = dx * box->unknown00[0][2] + dy * box->unknown00[1][2] + dz * box->unknown00[2][2];
  if (!(box->unknown40[2] >= c && c >= -box->unknown40[2])) {
    return false;
  }
  f32 b = dx * box->unknown00[0][1] + dy * box->unknown00[1][1] + dz * box->unknown00[2][1];
  if (!(box->unknown40[1] >= b)) {
    return false;
  }
  if (!(b >= -box->unknown40[1])) {
    return false;
  }
  return true;
}

} // namespace ml

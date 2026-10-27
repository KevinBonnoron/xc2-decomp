#include "dr/dr_env_coli_obj.h"

#include "dr/dr_env_coli_man.h"
#include "dr/dr_man.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace {

// Inferred role: collision sphere data; original type name unknown.
struct unknown001 {
  u8 _00[0x0c];
  f32 unknown0c; // Inferred role: radius; original member name unknown.
};

// Inferred role: collision data of a non rotated cylinder; original type name unknown.
struct unknown002 {
  u8 _00[0x0c];
  f32 unknown0c; // Inferred role: radius; original member name unknown.
  f32 unknown10; // Inferred role: half height; original member name unknown.
};

// Inferred role: collision data of a non rotated box; original type name unknown.
struct unknown003 {
  u8 _00[0x0c];
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
  f32 unknown10[3]; // Inferred role: half extents; original member name unknown.
};

// Inferred role: collision data of a rotated box or cylinder; original type name unknown.
struct unknown004 {
  u8 _00[0x30];
  f32 unknown30[3]; // Inferred role: center; original member name unknown.
  f32 unknown3c;    // Inferred role: radius; original member name unknown.
  f32 unknown40[3]; // Inferred role: half extents; original member name unknown.
};

} // namespace

DrEnvColiObj::DrEnvColiObj(DrMan *man) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown28(nullptr), unknown30(man), unknown38(0) {}

DrEnvColiObj::~DrEnvColiObj() {
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
}

void DrEnvColiMan::clear() {
  DrEnvColiObj *object = unknown10[0];
  while (object != nullptr) {
    DrEnvColiObj *next = object->unknown08;
    delete object;
    object = next;
  }
  unknown10[0] = nullptr;
  unknown10[1] = nullptr;
  object = unknown20[0];
  while (object != nullptr) {
    DrEnvColiObj *next = object->unknown08;
    delete object;
    object = next;
  }
  unknown20[0] = nullptr;
  unknown20[1] = nullptr;
  object = unknown00[0];
  while (object != nullptr) {
    DrEnvColiObj *next = object->unknown08;
    delete object;
    object = next;
  }
  unknown00[0] = nullptr;
  unknown00[1] = nullptr;
}

void DrEnvColiObj::release() { unknown38 |= 1 << DrMan::s_nDblStockIdx; }

void DrEnvColiObj::setPause(bool isPause) {
  if (isPause) {
    unknown38 |= 4;
  } else {
    unknown38 &= ~4;
  }
}

bool DrEnvColiObj::isPause() const { return (unknown38 >> 2 & 1) != 0; }

u32 DrEnvColiObj::isDeleteCall() const { return unknown38 & (1 << DrMan::s_nDblIdx); }

u32 DrEnvColiObj::isDeleteAll() const { return unknown38 & 3; }

bool DrEnvColiObj::envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes) {
  const unknown004 *box = reinterpret_cast<const unknown004 *>(data);
  f32 cx = box->unknown30[0];
  f32 cy = box->unknown30[1];
  f32 cz = box->unknown30[2];
  f32 dx = position.x - cx;
  f32 dy = position.y - cy;
  f32 dz = position.z - cz;
  f32 radius = box->unknown3c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  f32 a = dx * axes[0].x + dy * axes[0].y + dz * axes[0].z;
  if (!(box->unknown40[0] + margin >= a)) {
    return false;
  }
  if (!(-box->unknown40[0] - margin <= a)) {
    return false;
  }
  f32 c = dx * axes[2].x + dy * axes[2].y + dz * axes[2].z;
  if (!(box->unknown40[2] + margin >= c)) {
    return false;
  }
  if (!(-box->unknown40[2] - margin <= c)) {
    return false;
  }
  f32 b = dx * axes[1].x + dy * axes[1].y + dz * axes[1].z;
  if (!(box->unknown40[1] + margin >= b)) {
    return false;
  }
  return -box->unknown40[1] - margin <= b;
}

bool DrEnvColiObj::envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center) {
  const unknown001 *sphere = reinterpret_cast<const unknown001 *>(data);
  f32 dx = position.x - center->x;
  f32 dy = position.y - center->y;
  f32 dz = position.z - center->z;
  f32 radius = sphere->unknown0c + margin;
  return dx * dx + dy * dy + dz * dz <= radius * radius;
}

bool DrEnvColiObj::envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes) {
  const unknown004 *cylinder = reinterpret_cast<const unknown004 *>(data);
  f32 cx = cylinder->unknown30[0];
  f32 cy = cylinder->unknown30[1];
  f32 cz = cylinder->unknown30[2];
  f32 dx = position.x - cx;
  f32 dy = position.y - cy;
  f32 dz = position.z - cz;
  f32 radius = cylinder->unknown3c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  f32 height = dx * axes[1].x + dy * axes[1].y + dz * axes[1].z;
  if (!(cylinder->unknown40[1] + margin >= height)) {
    return false;
  }
  if (!(-cylinder->unknown40[1] - margin <= height)) {
    return false;
  }
  f32 a = dx * axes[0].x + dy * axes[0].y + dz * axes[0].z;
  f32 b = dx * axes[2].x + dy * axes[2].y + dz * axes[2].z;
  f32 limit = cylinder->unknown40[0] + margin;
  return a * a + b * b <= limit * limit;
}

bool DrEnvColiObj::envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center) {
  const unknown003 *box = reinterpret_cast<const unknown003 *>(data);
  f32 dx = position.x - center->x;
  f32 dy = position.y - center->y;
  f32 dz = position.z - center->z;
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

bool DrEnvColiObj::envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center) {
  const unknown002 *cylinder = reinterpret_cast<const unknown002 *>(data);
  f32 dy = position.y - center->y;
  if (!(cylinder->unknown10 + margin >= dy)) {
    return false;
  }
  if (!(-cylinder->unknown10 - margin <= dy)) {
    return false;
  }
  f32 dx = position.x - center->x;
  f32 dz = position.z - center->z;
  f32 radius = cylinder->unknown0c + margin;
  return dx * dx + dz * dz <= radius * radius;
}

} // namespace ml

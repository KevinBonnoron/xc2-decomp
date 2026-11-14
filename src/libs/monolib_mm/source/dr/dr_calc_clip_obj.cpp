#include "dr/dr_calc_clip_obj.h"

#include "dr/dr_calc_view_work.h"
#include "dr/dr_man.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace {

// Inferred role: clip sphere data; original type name unknown.
struct unknown084 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: squared radius; original member name unknown.
};

// Inferred role: clip data of a non rotated cylinder; original type name unknown.
struct unknown085 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: squared radius; original member name unknown.
  f32 unknown10;    // Inferred role: half height; original member name unknown.
};

// Inferred role: clip data of a non rotated box; original type name unknown.
struct unknown086 {
  f32 unknown00[3]; // Inferred role: center; original member name unknown.
  f32 unknown0c;    // Inferred role: squared radius; original member name unknown.
  f32 unknown10[3]; // Inferred role: half extents; original member name unknown.
};

// Inferred role: clip data of a rotated box or cylinder; original type name unknown.
struct unknown087 {
  f32 unknown00[3][4]; // Inferred role: axes; original member name unknown.
  f32 unknown30[3];    // Inferred role: center; original member name unknown.
  f32 unknown3c;       // Inferred role: squared radius; original member name unknown.
  f32 unknown40[3];    // Inferred role: half extents; original member name unknown.
};

} // namespace

bool (DrCalcClipObj::*DrCalcClipObj::s_pColiCheck[5])(const u8 *data, const mm::Vec3 &pos) = {
    &DrCalcClipObj::clipcoli_box,
    &DrCalcClipObj::clipcoli_sphere,
    &DrCalcClipObj::clipcoli_cylinder,
    &DrCalcClipObj::clipcoli_notrot_box,
    &DrCalcClipObj::clipcoli_notrot_cylinder,
};

void DrCalcClipObj::update(DrCalcViewWork *viewWork, u32 *flags) {
  unknown60 = flags;
  unknown3c &= ~0xc;
  seachTree(unknown20, viewWork->unknown400);
}

DrCalcClipObj::DrCalcClipObj(const void *data, DrMan *man)
    : DrCalcClipMan::unknown009<DrCalcClipObj>(), unknown28(nullptr), unknown3c(0), unknown40(0), unknown42(0), unknown44(0), unknown58(nullptr), unknown60(nullptr) {
  setupClip(static_cast<const u8 *>(data), man);
}

void DrCalcClipObj::setupClip(const u8 *data, DrMan *man) {
  const unknown008 *header = reinterpret_cast<const unknown008 *>(data);
  unknown10 = header;
  unknown18 = reinterpret_cast<const unknown005 *>(data + header->unknown0c);
  unknown20 = reinterpret_cast<const MdsClipListTreeData *>(data + header->unknown3c);
  unknown38 = header->unknown40;
  unknown30 = reinterpret_cast<const unknown007 *>(data + header->unknown48);
  if (unknown58 != nullptr) {
    mtl::MemManager::deallocate(unknown58, 0, false);
    unknown58 = nullptr;
  }
  if (header->unknown4c == 0) {
    unknown28 = nullptr;
  } else {
    unknown28 = reinterpret_cast<const unknown006 *>(reinterpret_cast<const u8 *>(unknown10) + header->unknown50);
    s16 size = (header->unknown4c / 32 + 1) * 4;
    unknown40 = size + (32 - size % 32) % 32;
    unknown58 = static_cast<u32 *>(mtl::MemManager::allocate(man->unknown14, unknown40, 0x20, false, "no name", 0));
  }
}

DrCalcClipObj::~DrCalcClipObj() {
  if (unknown58 != nullptr) {
    mtl::MemManager::deallocate(unknown58, 0, false);
    unknown58 = nullptr;
  }
}

void DrCalcClipObj::release() { unknown3c |= 1 << DrMan::s_nDblStockIdx; }

void DrCalcClipObj::seachTree(const MdsClipListTreeData *node, const mm::Vec3 &position) {
  if (node->unknown00[0] < position.x || node->unknown0c[0] > position.x || node->unknown00[2] < position.z || node->unknown0c[2] > position.z || node->unknown00[1] < position.y ||
      node->unknown0c[1] > position.y) {
    return;
  }
  u32 count = node->unknown20;
  if (count != 0) {
    const u16 *children = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown10) + node->unknown18);
    for (u32 i = 0; i < count; i++) {
      seachTree(unknown20 + children[i], position);
    }
  }
  count = node->unknown22;
  if (count != 0) {
    const u16 *indices = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown10) + node->unknown1c);
    for (u32 i = 0; i < count; i++) {
      const unknown005 *header = unknown18 + indices[i];
      u32 index = indices[i];
      if (!(unknown60[header->unknown04 >> 5] & (1 << (header->unknown04 & 0x1f)))) {
        const unknown007 *group = &unknown30[index];
        if (group->unknown02 == 0 || !(DrMan::getIns()->m_gblIdx[group->unknown02 >> 5] & (1 << (group->unknown02 & 0x1f)))) {
          if ((this->*s_pColiCheck[header->unknown06])(reinterpret_cast<const u8 *>(unknown10) + header->unknown00, position)) {
            unknown60[header->unknown04 >> 5] |= 1 << (header->unknown04 & 0x1f);
            if (unknown28 != nullptr) {
              const unknown006 *flag = &unknown28[header->unknown04];
              if (flag->unknown04 & 8) {
                unknown3c |= 4;
              }
              if (flag->unknown04 & 4) {
                unknown3c |= 8;
              }
            }
          }
        }
      }
    }
  }
}

void DrCalcClipObj::seachCheckTree(const MdsClipListTreeData *node, const mm::Vec3 &position, f32 radius) {
  if (node->unknown00[0] < position.x || node->unknown0c[0] > position.x || node->unknown00[2] < position.z || node->unknown0c[2] > position.z || node->unknown00[1] < position.y ||
      node->unknown0c[1] > position.y) {
    return;
  }
  u32 count = node->unknown20;
  if (count != 0) {
    const u16 *children = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown10) + node->unknown18);
    for (u32 i = 0; i < count; i++) {
      seachCheckTree(unknown20 + children[i], position, radius);
    }
  }
  count = node->unknown22;
  if (count != 0) {
    const u16 *indices = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown10) + node->unknown1c);
    for (u32 i = 0; i < count; i++) {
      const unknown005 *header = unknown18 + indices[i];
      u32 index = indices[i];
      const unknown006 *flag = unknown28 + header->unknown04;
      u32 flagIndex = header->unknown04;
      if (flag->unknown04 & 2) {
        continue;
      }
      if (!(unknown60[flagIndex >> 5] & (1 << (flagIndex & 0x1f)))) {
        continue;
      }
      const unknown007 *group = &unknown30[index];
      if (group->unknown02 != 0 && (DrMan::getIns()->m_gblIdx[group->unknown02 >> 5] & (1 << (group->unknown02 & 0x1f)))) {
        continue;
      }
      if (flag->unknown00 < radius) {
        continue;
      }
      if (flag->unknown06 < unknown42) {
        continue;
      }
      if (unknown58[header->unknown04 >> 5] & (1 << (header->unknown04 & 0x1f))) {
        continue;
      }
      if ((this->*s_pColiCheck[header->unknown06])(reinterpret_cast<const u8 *>(unknown10) + header->unknown00, position) && unknown44 < 8) {
        if (flag->unknown06 > unknown42) {
          unknown44 = 0;
          unknown42 = flag->unknown06;
        }
        unknown46[unknown44++] = header->unknown04;
        unknown58[header->unknown04 >> 5] |= 1 << (header->unknown04 & 0x1f);
      }
    }
  }
}

void DrCalcClipObj::seachOffTree(const MdsClipListTreeData *node, const mm::Vec3 &position, f32 radius) {
  if (node->unknown00[0] < position.x || node->unknown0c[0] > position.x || node->unknown00[2] < position.z || node->unknown0c[2] > position.z || node->unknown00[1] < position.y ||
      node->unknown0c[1] > position.y) {
    return;
  }
  u32 count = node->unknown20;
  if (count != 0) {
    const u16 *children = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown10) + node->unknown18);
    for (u32 i = 0; i < count; i++) {
      seachOffTree(unknown20 + children[i], position, radius);
    }
  }
  count = node->unknown22;
  if (count != 0) {
    const u16 *indices = reinterpret_cast<const u16 *>(reinterpret_cast<const u8 *>(unknown10) + node->unknown1c);
    for (u32 i = 0; i < count; i++, indices++) {
      const unknown005 *header = unknown18 + *indices;
      u32 index = *indices;
      if (!(unknown58[header->unknown04 >> 5] & (1 << (header->unknown04 & 0x1f)))) {
        continue;
      }
      const unknown007 *group = &unknown30[index];
      if (group->unknown02 != 0 && (DrMan::getIns()->m_gblIdx[group->unknown02 >> 5] & (1 << (group->unknown02 & 0x1f)))) {
        continue;
      }
      if (unknown28[header->unknown04].unknown00 < radius) {
        continue;
      }
      if (unknown28[header->unknown04].unknown06 < unknown42) {
        continue;
      }
      if ((this->*s_pColiCheck[header->unknown06])(reinterpret_cast<const u8 *>(unknown10) + header->unknown00, position) && unknown44 > 0) {
        u16 flagIndex = header->unknown04;
        for (s32 j = 0; j < unknown44; j++) {
          if (unknown46[j] == flagIndex) {
            unknown58[flagIndex >> 5] &= ~(1 << (flagIndex & 0x1f));
            break;
          }
        }
      }
    }
  }
}

bool DrCalcClipObj::clipcoli_sphere(const u8 *data, const mm::Vec3 &pos) {
  const unknown084 *sphere = reinterpret_cast<const unknown084 *>(data);
  f32 dx = pos.x - sphere->unknown00[0];
  f32 dy = pos.y - sphere->unknown00[1];
  f32 dz = pos.z - sphere->unknown00[2];
  return dx * dx + dy * dy + dz * dz <= sphere->unknown0c;
}

bool DrCalcClipObj::clipcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &pos) {
  const unknown085 *cylinder = reinterpret_cast<const unknown085 *>(data);
  f32 dy = pos.y - cylinder->unknown00[1];
  if (!(cylinder->unknown10 >= dy && dy >= -cylinder->unknown10)) {
    return false;
  }
  f32 dx = pos.x - cylinder->unknown00[0];
  f32 dz = pos.z - cylinder->unknown00[2];
  return dx * dx + dz * dz <= cylinder->unknown0c;
}

bool DrCalcClipObj::clipcoli_notrot_box(const u8 *data, const mm::Vec3 &pos) {
  const unknown086 *box = reinterpret_cast<const unknown086 *>(data);
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
  const unknown087 *cylinder = reinterpret_cast<const unknown087 *>(data);
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
  const unknown087 *box = reinterpret_cast<const unknown087 *>(data);
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

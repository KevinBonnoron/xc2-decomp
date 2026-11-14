#include <math.h>
#include <string.h>

#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiTreeTop::IDColiTreeTop() {
  unknown160 = 0;
  unknown00 = mm::Vec3(64.0f, 64.0f, 64.0f);
  unknown10 = mm::Vec3(-64.0f, -64.0f, -64.0f);
  unknown20 = mm::Vec3(64.0f, 64.0f, 64.0f);
  unknown30 = mm::Vec3(-64.0f, -64.0f, -64.0f);
  unknown164 = 0;
  updateTree();
}

void IDColiTreeTop::updateTree() {
  memset(unknown130, 0, sizeof(unknown130));
  unknown164 = 0;
  f32 sizeX = unknown20.x - unknown30.x;
  f32 sizeY = unknown20.y - unknown30.y;
  f32 sizeZ = unknown20.z - unknown30.z;
  f32 scale = 1.0f;
  for (s64 level = 0; level < 5; level++) {
    f32 inverse = 1.0f / scale;
    unknown40[level].x = sizeX * inverse;
    unknown40[level].y = sizeY * inverse;
    unknown40[level].z = sizeZ * inverse;
    unknowne0[level].x = unknown40[level].x * 0.2f;
    unknowne0[level].y = unknown40[level].y * 0.2f;
    unknowne0[level].z = unknown40[level].z * 0.2f;
    if (fabsf(unknown40[level].x) <= 1.0f || fabsf(unknown40[level].y) <= 1.0f || fabsf(unknown40[level].z) <= 1.0f) {
      unknown90[level].x = 1.0f;
      unknown90[level].y = 1.0f;
      unknown90[level].z = 1.0f;
    } else {
      unknown90[level].x = 1.0f / unknown40[level].x;
      unknown90[level].y = 1.0f / unknown40[level].y;
      unknown90[level].z = 1.0f / unknown40[level].z;
      unknown164 |= 1 << level;
    }
    scale += scale;
  }
  for (int i = 0; i < 341; i++) {
    unknown168[i].m_head = nullptr;
    unknown168[i].m_tail = nullptr;
  }
}

IDColiTreeTop::~IDColiTreeTop() {}

void IDColiTreeTop::begin() {
  unknown20 = unknown00;
  unknown30 = unknown10;
  updateTree();
  unknown00 = mm::Vec3(-1000000.0f, -1000000.0f, -1000000.0f);
  unknown10 = mm::Vec3(1000000.0f, 1000000.0f, 1000000.0f);
  unknown160 &= ~1;
}

void IDColiTreeTop::initCehckTree(int index, int level, int x, int z) {
  unknown003 *cell = &unknown16b8[index];
  f32 posX = unknown40[level].x * x;
  f32 posZ = z * unknown40[level].z;
  cell->unknown00 = unknown40[level].x + posX + unknowne0[level].x;
  cell->unknown08 = posX - unknowne0[level].x;
  cell->unknown04 = posZ + unknown40[level].z + unknowne0[level].z;
  cell->unknown0c = posZ - unknowne0[level].z;
  unknown130[index >> 6] |= unknown036(index);
}

void IDColiTreeTop::releaseTreeList(IDColiTreeObj *node, int index) {
  if (!(unknown130[index >> 6] & unknown036(index))) {
    return;
  }
  ColiLinkList<IDColiTreeObj> *list = &unknown168[index];
  IDColiTreeObj *prev = node->unknown00;
  IDColiTreeObj *next = node->unknown08;
  if (prev == nullptr) {
    if (next != nullptr) {
      list->m_head = next;
      next->unknown00 = nullptr;
    } else {
      // The tail is cleared first: the game clears it with the store that also clears prev->unknown08 below (str xzr,
      // [x9, #8] at 1.0.0: 0x71008d329c, 28 instructions); with the head cleared first it keeps its own stores (29).
      list->m_tail = nullptr;
      list->m_head = nullptr;
    }
  } else {
    if (next != nullptr) {
      prev->unknown08 = next;
      node->unknown08->unknown00 = node->unknown00;
    } else {
      list->m_tail = prev;
      prev->unknown08 = nullptr;
    }
  }
  node->unknown00 = nullptr;
  node->unknown08 = nullptr;
}

u32 IDColiTreeTop::getPart1By1(u32 value) {
  value = (value ^ (value << 8)) & 0xff00ff;
  value = (value | (value << 4)) & 0xf0f0f0f;
  value = (value | (value << 2)) & 0x33333333;
  return (value | (value << 1)) & 0x55555555;
}

u32 IDColiTreeTop::getMorton2(u32 x, u32 y) { return (getPart1By1(y) << 1) | getPart1By1(x); }

ColiLinkList<IDColiTreeObj> *IDColiTreeTop::getObjList(int x, int z, int level) {
  u32 index = COLI_TBL_INDEX[level] + x + COLI_TBL_GRID[level] * z;
  return &unknown168[index];
}

} // namespace idcoli

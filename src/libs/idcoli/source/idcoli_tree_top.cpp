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
  unknown130[index >> 6] |= static_cast<u64>(1) << (static_cast<s64>(index) & 63);
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

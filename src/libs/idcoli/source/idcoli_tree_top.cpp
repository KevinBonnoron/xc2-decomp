#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiTreeTop::~IDColiTreeTop() {}

void IDColiTreeTop::begin() {
  unknown20 = unknown00;
  unknown30 = unknown10;
  updateTree();
  unknown00 = mm::Vec3(-1000000.0f, -1000000.0f, -1000000.0f);
  unknown10 = mm::Vec3(1000000.0f, 1000000.0f, 1000000.0f);
  unknown160 &= ~1;
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

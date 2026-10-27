#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace idcoli {

IDColiGrandWork::IDColiGrandWork() {}

IDColiObjGrand::IDColiObjGrand() {
  unknown50.unknowna8 = nullptr;
  unknown24 = OBJ_TYPE_GRAND;
}

IDColiObjGrand::~IDColiObjGrand() { workClear(); }

void IDColiObjGrand::workClear() {
  if (unknown50.unknowna8 != nullptr) {
    if (unknown50.unknown90 != nullptr) {
      unknown50.unknown90->~IDColiTreeTop();
    }
    if (unknown50.unknown98 != nullptr) {
      unknown50.unknown98->~IDColiTreeTop();
    }
    if (unknown50.unknowna8 != nullptr) {
      mtl::MemManager::deallocate(unknown50.unknowna8, 0, false);
      unknown50.unknowna8 = nullptr;
    }
  }
}

int IDColiObjGrand::calcGrandBufferSize(const void *binary) {
  const unknown017 *header = static_cast<const unknown017 *>(binary);
  int size = header->unknown1c * 0x10 + (header->unknown24 + header->unknown2c) * 8 + (header->unknown34 + header->unknown3c) * 8;
  if (header->unknown94 != 0) {
    size += 0x5820;
  }
  int padding = -size & 9;
  return size + header->unknown94 * 0x200 + padding;
}

void IDColiObjGrand::getGrandAABB(mm::Vec3 &max, mm::Vec3 &min) const {
  const unknown017 *header = reinterpret_cast<const unknown017 *>(unknown50.unknown00);
  u64 offset;
  if (header->unknown88 & 2) {
    offset = header->unknown8c;
  } else {
    offset = header->unknown08;
    offset -= 0x28;
  }
  const unknown018 *bounds = reinterpret_cast<const unknown018 *>(unknown50.unknown00 + offset);
  f32 maxX = bounds->unknown00[0];
  f32 maxY = bounds->unknown00[1];
  f32 maxZ = bounds->unknown00[2];
  max.x = max.x > maxX ? max.x : maxX;
  max.y = max.y > maxY ? max.y : maxY;
  max.z = max.z > maxZ ? max.z : maxZ;
  f32 minX = bounds->unknown0c[0];
  f32 minY = bounds->unknown0c[1];
  f32 minZ = bounds->unknown0c[2];
  min.x = min.x < minX ? min.x : minX;
  min.y = min.y < minY ? min.y : minY;
  min.z = min.z < minZ ? min.z : minZ;
}

} // namespace idcoli

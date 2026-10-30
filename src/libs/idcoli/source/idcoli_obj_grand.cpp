#include <new>

#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace idcoli {

// Inferred role: entry of a pointer table of a grand binary; original type name unknown.
struct unknown029 {
  u32 unknown00; // Inferred role: unknown; original member name unknown.
  u32 unknown04; // Inferred role: index into the pointed data; original member name unknown.
};

static_assert(sizeof(unknown029) == 0x8, "");

IDColiGrandWork::IDColiGrandWork() {}

IDColiObjGrand::IDColiObjGrand() {
  unknown50.unknowna8 = nullptr;
  unknown24 = unknown098_3;
}

IDColiObjGrand::~IDColiObjGrand() { workClear(); }

void IDColiObjGrand::createGrand(mtl::ALLOC_HANDLE handle, const void *binary) {
  workClear();
  u32 size = calcGrandBufferSize(binary);
  void *buffer = mtl::MemManager::allocate(handle, size, 0x10, false, "no name", 0);
  unknown50.unknowna8 = buffer;
  createGrandAdder(buffer, binary);
}

void IDColiObjGrand::createGrandAdder(void *buffer, const void *binary) {
  const unknown017 *header = static_cast<const unknown017 *>(binary);
  u8 *base = static_cast<u8 *>(buffer);
  unknown50.unknown00 = static_cast<const u8 *>(binary);
  unknown50.unknown18 = static_cast<const mm::Vec3 **>(buffer);
  u32 offset = header->unknown1c * 8;
  unknown50.unknown20 = reinterpret_cast<const IDCmfNormalData **>(base + offset);
  offset += header->unknown24 * 8;
  unknown50.unknown28 = reinterpret_cast<const unknown014 **>(base + offset);
  offset += header->unknown1c * 8;
  unknown50.unknown48 = reinterpret_cast<u32 *>(base + offset);
  offset += header->unknown2c * 4;
  unknown50.unknown50 = reinterpret_cast<u32 *>(base + offset);
  offset += header->unknown34 * 4;
  unknown50.unknown58 = reinterpret_cast<u32 *>(base + offset);
  offset += header->unknown3c * 4;
  if (header->unknown94 == 0) {
    unknown50.unknown90[0] = nullptr;
    unknown50.unknown90[1] = nullptr;
  } else {
    unknown50.unknown90[0] = reinterpret_cast<IDColiTreeTop *>(base + offset);
    unknown50.unknown90[1] = reinterpret_cast<IDColiTreeTop *>(base + (offset + 0x2c10));
    offset += 0x5820;
  }
  unknown50.unknowna0 = 0;
  int count = 0;
  if (header->unknown94 != 0) {
    unknown50.unknown70 = reinterpret_cast<IDColiGrdMoveObj *>(base + ((-offset & 0xf) + offset));
    count = header->unknown94;
  }
  unknown50.unknown78 = count;
  createMemBinary();
}

void IDColiObjGrand::createMemBinary() {
  const unknown017 *header = reinterpret_cast<const unknown017 *>(unknown50.unknown00);
  unknown50.unknown08 = reinterpret_cast<const unknown021 *>(unknown50.unknown00 + header->unknown08);
  unknown50.unknown10 = reinterpret_cast<const IDCmfPoliData *>(unknown50.unknown00 + header->unknown10);
  unknown50.unknown30 = reinterpret_cast<const IDCmfPosData *>(unknown50.unknown00 + header->unknown58);
  unknown50.unknown38 = reinterpret_cast<const IDCmfPosInfo *>(unknown50.unknown30 + header->unknown5c);
  unknown50.unknown40 = reinterpret_cast<const unknown097 *>(unknown50.unknown00 + header->unknown74);
  unknown50.unknown60 = unknown50.unknown00 + header->unknown60;
  unknown50.unknown68 = unknown50.unknown00 + header->unknown68;
  if (header->unknowna0 == 0) {
    unknown50.unknown80 = nullptr;
    unknown50.unknown88 = 0;
  } else {
    unknown50.unknown80 = reinterpret_cast<const unknown094 *>(unknown50.unknown00 + header->unknowna0);
    unknown50.unknown88 = header->unknowna4;
  }

  const mm::Vec3 *vertices = reinterpret_cast<const mm::Vec3 *>(unknown50.unknown00 + header->unknown40);
  if (header->unknown1c > 0) {
    const unknown029 *entries = reinterpret_cast<const unknown029 *>(unknown50.unknown00 + header->unknown18);
    for (int i = 0; i < header->unknown1c; i++) {
      unknown50.unknown18[i] = &vertices[entries[i].unknown04];
    }
  }

  const IDCmfNormalData *normals = reinterpret_cast<const IDCmfNormalData *>(unknown50.unknown00 + header->unknown48);
  if (header->unknown24 > 0) {
    const unknown029 *entries = reinterpret_cast<const unknown029 *>(unknown50.unknown00 + header->unknown20);
    for (int i = 0; i < header->unknown24; i++) {
      unknown50.unknown20[i] = &normals[entries[i].unknown04];
    }
  }

  if (header->unknown54 == 0) {
    for (int i = 0; i < header->unknown1c; i++) {
      unknown50.unknown28[i] = nullptr;
    }
  } else {
    const unknown014 *vectors = reinterpret_cast<const unknown014 *>(unknown50.unknown00 + header->unknown7c);
    if (header->unknown54 > 0) {
      const unknown029 *entries = reinterpret_cast<const unknown029 *>(unknown50.unknown00 + header->unknown50);
      for (int i = 0; i < header->unknown54; i++) {
        unknown50.unknown28[i] = &vectors[entries[i].unknown04];
      }
    }
  }

  if (header->unknown2c > 0) {
    const u32 *table = reinterpret_cast<const u32 *>(unknown50.unknown00 + header->unknown28);
    for (int i = 0; i < header->unknown2c; i++) {
      unknown50.unknown48[i] = table[i];
    }
  }
  if (header->unknown34 > 0) {
    const u32 *table = reinterpret_cast<const u32 *>(unknown50.unknown00 + header->unknown30);
    for (int i = 0; i < header->unknown34; i++) {
      unknown50.unknown50[i] = table[i];
    }
  }
  if (header->unknown3c > 0) {
    const u32 *table = reinterpret_cast<const u32 *>(unknown50.unknown00 + header->unknown38);
    for (int i = 0; i < header->unknown3c; i++) {
      unknown50.unknown58[i] = table[i];
    }
  }

  if (unknown50.unknown78 != 0) {
    new (unknown50.unknown90[0]) IDColiTreeTop();
    new (unknown50.unknown90[1]) IDColiTreeTop();
    const IDCmfMovePosData *moveData = reinterpret_cast<const IDCmfMovePosData *>(unknown50.unknown00 + header->unknown90);
    if (unknown50.unknown78 > 0) {
      const IDCmfMovePosInfo *moveInfo = reinterpret_cast<const IDCmfMovePosInfo *>(moveData + header->unknown94);
      for (int i = 0; i < unknown50.unknown78; i++, moveData++, moveInfo++) {
        new (&unknown50.unknown70[i]) IDColiGrdMoveObj();
        unknown50.unknown70[i].setMoveData(unknown50.unknown00, moveData, moveInfo);
      }
    }
  }
}

void IDColiObjGrand::update() {
  if (unknown50.unknown78 != 0) {
    int bank = unknown50.unknowna0;
    u32 next = bank == 0;
    unknown50.unknown90[next]->begin();
    for (int i = 0; i < unknown50.unknown78; i++) {
      unknown50.unknown70[i].update();
      unknown50.unknown90[next]->setupTreeList(&unknown50.unknown70[i].unknown1c8[next].unknown00, unknown50.unknown70[i].unknown100.unknown80, unknown50.unknown70[i].unknown100.unknown90);
    }
    unknown50.unknown90[next]->end();
    unknown50.unknowna0 = next;
  }
}

void IDColiObjGrand::workClear() {
  if (unknown50.unknowna8 != nullptr) {
    if (unknown50.unknown90[0] != nullptr) {
      unknown50.unknown90[0]->~IDColiTreeTop();
    }
    if (unknown50.unknown90[1] != nullptr) {
      unknown50.unknown90[1]->~IDColiTreeTop();
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

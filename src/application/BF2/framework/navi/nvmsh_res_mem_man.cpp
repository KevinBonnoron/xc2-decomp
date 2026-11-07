#include "navi/nvmsh_res_mem_man.h"

#include "mtl/mem_manager.h"

namespace navi {

// The game stores these fields in this order.
NvmshResMemObj::NvmshResMemObj() {
  unknown18 = nullptr;
  unknown20 = 0;
  unknown10 = 0;
  unknown00 = nullptr;
  unknown08 = nullptr;
}

NvmshResMemMan::~NvmshResMemMan() {
  if (unknown00 == nullptr) {
    return;
  }
  mtl::MemManager::deallocate(unknown00, 0, false);
  unknown00 = nullptr;
}

// The game calls memcpy here even though the ranges can overlap; keep the same call to reproduce that behavior.
void NvmshResMemMan::memLcMove(void *destination, void *source, u32 size) { __builtin_memcpy(destination, source, size); }

void NvmshResMemMan::releaseFreeObj(NvmshResMemObj *object) {
  for (NvmshResMemObj *entry = unknown18; entry != nullptr; entry = entry->unknown08) {
    if (entry == object) {
      clearMemObj(entry);
      return;
    }
  }
}

// Returns the first free piece that fits. A split needs a spare descriptor; when none is left the search returns null
// instead of continuing to a later exact fit.
NvmshResMemObj *NvmshResMemMan::createFreeObj(u32 size) {
  for (NvmshResMemObj *piece = unknown18; piece != nullptr; piece = piece->unknown08) {
    if ((piece->unknown10 & 1) != 0) {
      continue;
    }
    if (piece->unknown20 < size) {
      continue;
    }
    u32 rest = piece->unknown20 - size;
    if (rest != 0) {
      NvmshResMemObj *spare = unknown08;
      if (spare == nullptr) {
        return nullptr;
      }
      piece->unknown20 = size;
      spare->unknown18 = static_cast<u8 *>(piece->unknown18) + size;
      spare->unknown20 = rest;
      if (spare->unknown00 != nullptr) {
        if (spare->unknown08 != nullptr) {
          spare->unknown00->unknown08 = spare->unknown08;
          spare->unknown08->unknown00 = spare->unknown00;
        } else {
          unknown10 = spare->unknown00;
          unknown10->unknown08 = nullptr;
        }
      } else if (spare->unknown08 != nullptr) {
        unknown08 = spare->unknown08;
        unknown08->unknown00 = nullptr;
      } else {
        unknown08 = nullptr;
        unknown10 = nullptr;
      }
      spare->unknown10 = 0;
      spare->unknown00 = nullptr;
      spare->unknown08 = nullptr;
      NvmshResMemObj *next = piece->unknown08;
      piece->unknown08 = spare;
      spare->unknown00 = piece;
      if (next != nullptr) {
        spare->unknown08 = next;
        next->unknown00 = spare;
      } else {
        spare->unknown08 = nullptr;
        unknown20 = spare;
      }
    }
    piece->unknown10 |= 1;
    return piece;
  }
  return nullptr;
}

void NvmshResMemMan::moveMemoryObject(NvmshResMemObj *destination, NvmshResMemObj *source) {
  memLcMove(destination->unknown18, source->unknown18, source->unknown20);
  source->unknown10 |= 4;
  void *data = destination->unknown18;
  source->unknown18 = data;
  destination->unknown18 = static_cast<u8 *>(data) + source->unknown20;
}

} // namespace navi

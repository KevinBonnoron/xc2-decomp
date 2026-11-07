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

// Clears the piece and folds it into free neighbours; descriptors of pieces merged into a neighbour return to the
// spare list.
void NvmshResMemMan::clearMemObj(NvmshResMemObj *object) {
  NvmshResMemObj *previous = object->unknown00;
  object->unknown10 = 0;

  if (previous != nullptr && (previous->unknown10 & 1) == 0) {
    previous->unknown20 = previous->unknown20 + object->unknown20;
    if (object->unknown00 != nullptr) {
      if (object->unknown08 != nullptr) {
        object->unknown00->unknown08 = object->unknown08;
        object->unknown08->unknown00 = object->unknown00;
      } else {
        unknown20 = object->unknown00;
        unknown20->unknown08 = nullptr;
      }
    } else if (object->unknown08 != nullptr) {
      unknown18 = object->unknown08;
      unknown18->unknown00 = nullptr;
    } else {
      unknown18 = nullptr;
      unknown20 = nullptr;
    }
    object->unknown00 = nullptr;
    object->unknown08 = nullptr;
    if (unknown10 == nullptr) {
      unknown08 = object;
      unknown10 = object;
      object->unknown00 = nullptr;
    } else {
      unknown10->unknown08 = object;
      object->unknown00 = unknown10;
      unknown10 = object;
    }
    object->unknown08 = nullptr;
    object = previous;
  }

  NvmshResMemObj *next = object->unknown08;
  if (next == nullptr || (next->unknown10 & 1) != 0) {
    return;
  }

  object->unknown20 += next->unknown20;
  if (next->unknown00 != nullptr) {
    if (next->unknown08 != nullptr) {
      next->unknown00->unknown08 = next->unknown08;
      next->unknown08->unknown00 = next->unknown00;
    } else {
      unknown20 = next->unknown00;
      unknown20->unknown08 = nullptr;
    }
  } else if (next->unknown08 != nullptr) {
    unknown18 = next->unknown08;
    unknown18->unknown00 = nullptr;
  } else {
    unknown18 = nullptr;
    unknown20 = nullptr;
  }
  next->unknown10 = 0;
  next->unknown00 = nullptr;
  next->unknown08 = nullptr;
  if (unknown10 == nullptr) {
    unknown08 = next;
    unknown10 = next;
    next->unknown00 = nullptr;
  } else {
    unknown10->unknown08 = next;
    next->unknown00 = unknown10;
    unknown10 = next;
  }
  next->unknown08 = nullptr;
}

void NvmshResMemMan::moveMemoryObject(NvmshResMemObj *destination, NvmshResMemObj *source) {
  memLcMove(destination->unknown18, source->unknown18, source->unknown20);
  source->unknown10 |= 4;
  void *data = destination->unknown18;
  source->unknown18 = data;
  destination->unknown18 = static_cast<u8 *>(data) + source->unknown20;
}

} // namespace navi

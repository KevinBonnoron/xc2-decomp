#include "navi/nvmsh_res_mem_man.h"

#include <new>

#include "mtl/alloc_handle.h"
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

// unknown001 is already the image-prefix struct in the unity unit; these inferred helpers use the next free names.
// Inferred helper: unlinks a node from a list whose head and tail are passed by reference; original name unknown.
static inline void unknown002(NvmshResMemObj *object, NvmshResMemObj *&head, NvmshResMemObj *&tail) {
  if (object->unknown00 != nullptr) {
    if (object->unknown08 != nullptr) {
      object->unknown00->unknown08 = object->unknown08;
      object->unknown08->unknown00 = object->unknown00;
    } else {
      tail = object->unknown00;
      tail->unknown08 = nullptr;
    }
  } else if (object->unknown08 != nullptr) {
    head = object->unknown08;
    head->unknown00 = nullptr;
  } else {
    head = nullptr;
    tail = nullptr;
  }
  object->unknown00 = nullptr;
  object->unknown08 = nullptr;
}

// Inferred helper: appends a node at the tail of a list whose head and tail are passed by reference; original name
// unknown.
static inline void unknown003(NvmshResMemObj *object, NvmshResMemObj *&head, NvmshResMemObj *&tail) {
  if (tail != nullptr) {
    tail->unknown08 = object;
    object->unknown00 = tail;
    tail = object;
  } else {
    head = object;
    tail = object;
    object->unknown00 = nullptr;
  }
  object->unknown08 = nullptr;
}

// Allocates the 38-descriptor pool. Descriptor 0 references the caller buffer and joins the memory piece list; the
// other 37 descriptors are spare.
NvmshResMemMan::NvmshResMemMan(u8 *buffer, int size, mtl::ALLOC_HANDLE handle) {
  unknown18 = nullptr;
  unknown20 = nullptr;
  unknown08 = nullptr;
  unknown10 = nullptr;
  unknown00 = mtl::MemManager::allocate(handle, 0x5f0, 0x40, false, "no name", 0);

  NvmshResMemObj *base = static_cast<NvmshResMemObj *>(unknown00);
  for (int i = 0; i < 38; i++) {
    new (&base[i]) NvmshResMemObj();
  }

  base->unknown18 = buffer;
  base->unknown20 = size;
  unknown003(base, unknown18, unknown20);

  for (int i = 1; i < 38; i++) {
    unknown003(&base[i], unknown08, unknown10);
  }
}

// Clears the piece and folds it into free neighbours; descriptors of pieces merged into a neighbour return to the
// spare list.
void NvmshResMemMan::clearMemObj(NvmshResMemObj *object) {
  NvmshResMemObj *previous = object->unknown00;
  object->unknown10 = 0;

  if (previous != nullptr && (previous->unknown10 & 1) == 0) {
    previous->unknown20 = previous->unknown20 + object->unknown20;
    unknown002(object, unknown18, unknown20);
    unknown003(object, unknown08, unknown10);
    object = previous;
  }

  NvmshResMemObj *next = object->unknown08;
  if (next == nullptr || (next->unknown10 & 1) != 0) {
    return;
  }

  object->unknown20 += next->unknown20;
  unknown002(next, unknown18, unknown20);
  next->unknown10 = 0;
  unknown003(next, unknown08, unknown10);
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
      unknown002(spare, unknown08, unknown10);
      spare->unknown10 = 0;
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

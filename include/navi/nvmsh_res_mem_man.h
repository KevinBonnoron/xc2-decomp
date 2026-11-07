#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace navi {

// Element of the piece lists of NvmshResMemMan. The constructor allocates 0x5f0 bytes and initialises two 0x28-byte
// elements per 0x50 step (38 elements); it links element 0 into the list at +0x18/+0x20 and the other 37 into the
// list at +0x08/+0x10. createFreeObj takes pieces with bit 0 clear from the +0x18 list.
class NvmshResMemObj {
public:
  NvmshResMemObj();

  NvmshResMemObj *unknown00; // Inferred role: previous element; original member name unknown.
  NvmshResMemObj *unknown08; // Inferred role: next element; original member name unknown.
  u32 unknown10;             // Inferred role: state flags, bit 0 when the block is in use; original member name unknown.
  u8 _14[4];
  void *unknown18; // Inferred role: data pointer; original member name unknown.
  u32 unknown20;   // Inferred role: data size; original member name unknown.
};

static_assert(offsetof(NvmshResMemObj, unknown00) == 0x00, "");
static_assert(offsetof(NvmshResMemObj, unknown08) == 0x08, "");
static_assert(offsetof(NvmshResMemObj, unknown10) == 0x10, "");
static_assert(offsetof(NvmshResMemObj, unknown18) == 0x18, "");
static_assert(offsetof(NvmshResMemObj, unknown20) == 0x20, "");
static_assert(sizeof(NvmshResMemObj) == 0x28, "");

// Owns the navigation mesh memory block and its piece lists.
class NvmshResMemMan {
public:
  NvmshResMemMan(u8 *buffer, int size, mtl::ALLOC_HANDLE handle);
  ~NvmshResMemMan();

  static void memLcMove(void *destination, void *source, u32 size);
  NvmshResMemObj *createFreeObj(u32 size);
  void releaseFreeObj(NvmshResMemObj *object);
  void clearMemObj(NvmshResMemObj *object);
  void moveMemoryObject(NvmshResMemObj *destination, NvmshResMemObj *source);
  bool calcPieceMem();

  void *unknown00;           // Inferred role: allocated block; original member name unknown.
  NvmshResMemObj *unknown08; // Inferred role: head of the piece list at +0x08; original member name unknown.
  NvmshResMemObj *unknown10; // Inferred role: tail of the piece list at +0x08; original member name unknown.
  NvmshResMemObj *unknown18; // Inferred role: head of the piece list at +0x18; original member name unknown.
  NvmshResMemObj *unknown20; // Inferred role: tail of the piece list at +0x18; original member name unknown.
};

static_assert(offsetof(NvmshResMemMan, unknown00) == 0x00, "");
static_assert(offsetof(NvmshResMemMan, unknown08) == 0x08, "");
static_assert(offsetof(NvmshResMemMan, unknown10) == 0x10, "");
static_assert(offsetof(NvmshResMemMan, unknown18) == 0x18, "");
static_assert(offsetof(NvmshResMemMan, unknown20) == 0x20, "");
static_assert(sizeof(NvmshResMemMan) == 0x28, "");

} // namespace navi

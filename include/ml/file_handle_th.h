#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

class IWorkEvent;
struct DevFileParamTh;
enum CBM : int;

class alignas(16) FileHandleTh {
public:
  enum FTYPE {
    FTYPE_UNKNOWN_0 = 0, // Inferred role: unused handle.
    FTYPE_UNKNOWN_1 = 1, // Inferred role: buffer allocated from the memory handle.
    FTYPE_UNKNOWN_2 = 2, // Inferred role: buffer allocated from an allocator.
    FTYPE_UNKNOWN_3 = 3, // Inferred role: buffer given by the caller.
    FTYPE_UNKNOWN_4 = 4, // Inferred role: write handle.
    FTYPE_UNKNOWN_5 = 5, // Inferred role: buffer allocated from the memory handle without fallback.
    FTYPE_UNKNOWN_6 = 6, // Inferred role: buffer allocated by the device.
    FTYPE_UNKNOWN_7 = 7, // Inferred role: buffer allocated by the device, flag 4 of the parameter set.
  };

  FileHandleTh();
  FileHandleTh(const DevFileParamTh &param);
  ~FileHandleTh();

  void releaseBuffer();
  void init(FTYPE type);
  void setup(const DevFileParamTh &param);
  void initWriter(const char *path, void *data, int size, int offset, IWorkEvent *event);

  // Inferred role: sets the read offset and the default read size; original function name unknown.
  void unknown001(int offset, int size) {
    unknown14 = offset;
    if (unknown18 == 0) {
      unknown18 = size;
    }
    if (unknown14 > 0 || unknown18 > 0) {
      unknown94 |= 1;
    }
  }

  // Inferred role: rounds an unsigned size up to a multiple of the block size; original function name unknown.
  static u32 unknown002(u32 size, u32 blockSize) {
    u32 rest = size % blockSize;
    if (rest != 0) {
      return size + blockSize - rest;
    }
    return size;
  }

  // Inferred role: rounds a signed size up to a multiple of the block size; original function name unknown.
  static int unknown003(int size, int blockSize) {
    int rest = size % blockSize;
    if (rest != 0) {
      return size + blockSize - rest;
    }
    return size;
  }

  bool addCurrentPtr(int offset);
  bool setCurrentPtr(int offset);
  bool setReadBuffer(int size, u32 alignment, u32 blockSize);
  void setReadAdr(int size, void *buffer, int alignedSize);
  void setTime(u64 time);
  bool call(CBM cbm);

  FTYPE unknown00; // Inferred role: buffer type; original member name unknown.
  void *unknown08; // Inferred role: read buffer; original member name unknown.
  s32 unknown10;   // Inferred role: allocated size; original member name unknown.
  s32 unknown14;   // Inferred role: read offset; original member name unknown.
  s32 unknown18;   // Inferred role: read size; original member name unknown.
  s32 unknown1c;   // Role and original member name unknown.
  s32 unknown20;   // Role and original member name unknown.
  s32 unknown24;   // Role and original member name unknown.
  s32 m_currentPtr;
  mtl::ALLOC_HANDLE unknown2c;                          // Inferred role: mem handle; original member name unknown.
  void *unknown30;                                      // Inferred role: file size, or the allocator of the buffer; original member name unknown.
  mm::mtl::FixedVector<mtl::ALLOC_HANDLE, 8> unknown38; // Inferred role: fallback mem handles; original member name unknown.
  IWorkEvent *unknown60;                                // Inferred role: event listener; original member name unknown.
  void *unknown68;                                      // Inferred role: event; original member name unknown.
  void **unknown70;                                     // Inferred role: loaded data output; original member name unknown.
  s32 *unknown78;                                       // Inferred role: loaded size output; original member name unknown.
  s32 unknown80;                                        // Role and original member name unknown.
  u64 unknown88;                                        // Role and original member name unknown.
  u32 unknown90;                                        // Role and original member name unknown.
  u32 unknown94;                                        // Inferred role: state flags; original member name unknown.
  mm::mtl::FixStr<256> unknown98;                       // Inferred role: path; original member name unknown.
  mm::mtl::FixStr<32> unknown19c;                       // Role and original member name unknown.
  u64 m_time;
  u64 unknown1c8; // Inferred role: file time; original member name unknown.
  s32 unknown1d0; // Role and original member name unknown.
  u32 unknown1d4; // Inferred role: file channel; original member name unknown.
  s32 unknown1d8; // Role and original member name unknown.
  u64 unknown1e0; // Role and original member name unknown.
  // Inferred role: callback mode of the finished job (2 loaded, 4 load failed); original member name unknown. Evidence for the type:
  // DevFileTh::Impl::tail passes it unchanged to FileHandleTh::call(CBM) (_ZN2ml12FileHandleTh4callENS_3CBME; load at 0x71007325dc), whose
  // inlined body tests it against 4/6 and 5/2.
  CBM unknown1e8;
  s32 unknown1ec;  // Role and original member name unknown.
  s32 unknown1f0;  // Role and original member name unknown.
  bool unknown1f4; // Role and original member name unknown.
};

static_assert(offsetof(FileHandleTh, unknown08) == 0x08, "");
static_assert(offsetof(FileHandleTh, unknown10) == 0x10, "");
static_assert(offsetof(FileHandleTh, unknown18) == 0x18, "");
static_assert(offsetof(FileHandleTh, unknown20) == 0x20, "");
static_assert(offsetof(FileHandleTh, m_currentPtr) == 0x28, "");
static_assert(offsetof(FileHandleTh, unknown2c) == 0x2c, "");
static_assert(offsetof(FileHandleTh, unknown30) == 0x30, "");
static_assert(offsetof(FileHandleTh, unknown38) == 0x38, "");
static_assert(offsetof(FileHandleTh, unknown60) == 0x60, "");
static_assert(offsetof(FileHandleTh, unknown68) == 0x68, "");
static_assert(offsetof(FileHandleTh, unknown80) == 0x80, "");
static_assert(offsetof(FileHandleTh, unknown88) == 0x88, "");
static_assert(offsetof(FileHandleTh, unknown94) == 0x94, "");
static_assert(offsetof(FileHandleTh, unknown98) == 0x98, "");
static_assert(offsetof(FileHandleTh, unknown19c) == 0x19c, "");
static_assert(offsetof(FileHandleTh, m_time) == 0x1c0, "");
static_assert(offsetof(FileHandleTh, unknown1c8) == 0x1c8, "");
static_assert(offsetof(FileHandleTh, unknown1d4) == 0x1d4, "");
static_assert(offsetof(FileHandleTh, unknown1e0) == 0x1e0, "");
static_assert(offsetof(FileHandleTh, unknown1e8) == 0x1e8, "");
static_assert(offsetof(FileHandleTh, unknown1f4) == 0x1f4, "");
static_assert(sizeof(FileHandleTh) == 0x200, "");

} // namespace ml

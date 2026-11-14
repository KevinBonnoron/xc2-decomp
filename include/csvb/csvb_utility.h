#pragma once
#include "types.h"

#include <stddef.h>

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

// Inferred role: column count of a row in a CSVB file; original member names unknown.
struct stCsvbRowInfo {
  u16 unknown00;
};

// Inferred role: type word of a cell in a CSVB file (0xfffb empty, 0xfffc s8, 0xfffd s16, 0xfffe s32, 0xffff f32, otherwise the offset of a string); original member names unknown.
struct stCsvbDataInfo {
  u16 unknown00;
};

// Header of a CSVB file followed by the pointers GetCsvbInfo resolves into the file.
struct stCsvbInfo {
  // Header of a CSVB file; original type name unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: file magic; original member name unknown.
    u16 unknown04; // Inferred role: row count; original member name unknown.
    u16 unknown06; // Inferred role: data count; original member name unknown.
    u32 unknown08; // Inferred role: size of the byte data block; original member name unknown.
    u32 unknown0c; // Inferred role: size of the string block; original member name unknown.
  };

  unknown001 unknown00;
  const stCsvbRowInfo *unknown10;
  const stCsvbDataInfo *unknown18;
  const u8 *unknown20; // Inferred role: byte data block; original member name unknown.
  const char *unknown28;
};

static_assert(sizeof(stCsvbRowInfo) == 0x2, "");
static_assert(sizeof(stCsvbDataInfo) == 0x2, "");
static_assert(sizeof(stCsvbInfo::unknown001) == 0x10, "");
static_assert(offsetof(stCsvbInfo::unknown001, unknown04) == 0x04, "");
static_assert(offsetof(stCsvbInfo::unknown001, unknown06) == 0x06, "");
static_assert(offsetof(stCsvbInfo::unknown001, unknown08) == 0x08, "");
static_assert(offsetof(stCsvbInfo::unknown001, unknown0c) == 0x0c, "");
static_assert(offsetof(stCsvbInfo, unknown00) == 0x00, "");
static_assert(offsetof(stCsvbInfo, unknown10) == 0x10, "");
static_assert(offsetof(stCsvbInfo, unknown18) == 0x18, "");
static_assert(offsetof(stCsvbInfo, unknown20) == 0x20, "");
static_assert(offsetof(stCsvbInfo, unknown28) == 0x28, "");
static_assert(sizeof(stCsvbInfo) == 0x30, "");

namespace csvb {

class CCsvbUtility {
public:
  static void EndianSwap4(void *value);
  static void EndianSwap2(void *value);
  static bool LoadFile(const char *path, void **data, u32 *size);
  static void SaveFile(const char *path, const void *data, u32 size);
  static int GetCsvbFormat(const void *data);
  static bool GetCsvbInfo(stCsvbInfo &info, const void *data, u32 size, bool endianSwap);
  static void *CreateCsvbRows(mtl::ALLOC_HANDLE handle, const stCsvbRowInfo *rows, u16 count, bool endianSwap);
  static void *CreateCsvbRows(mm::mtl::IAllocator *allocator, const stCsvbRowInfo *rows, u16 count, bool endianSwap);
  static void *CreateCsvbData(mtl::ALLOC_HANDLE handle, const stCsvbDataInfo *info, u16 count, const u8 *data, const char *strings, bool endianSwap);
  static void *CreateCsvbData(mm::mtl::IAllocator *allocator, const stCsvbDataInfo *info, u16 count, const u8 *data, const char *strings, bool endianSwap);
};

} // namespace csvb

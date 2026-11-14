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

namespace csvb {

class CCsvbData {
public:
  struct unknown001 {
    u16 m_columCount;
    u16 unknown02; // Inferred role: index of the row's first value in the value table; original member name unknown.
  };

  // Inferred role: value of a cell, read as an int, a float or a string by GetInt, GetFloat and GetString; original member name unknown.
  union unknown003 {
    s32 unknown00;
    f32 unknown00_1;
    const char *unknown00_2;
  };

  struct unknown002 {
    s32 unknown00; // Inferred role: cell type (0 int, 1 float, 2 invalid, 3 string); original member name unknown.
    unknown003 unknown08;
  };

  CCsvbData();
  ~CCsvbData();
  void Clear();
  void MemoryFreeLocal(void *pointer);
  bool Load(mtl::ALLOC_HANDLE handle, const char *path);
  bool Load(mtl::ALLOC_HANDLE handle, const void *data, u32 size);
  bool Load(mm::mtl::IAllocator *allocator, const char *path);
  bool Load(mm::mtl::IAllocator *allocator, const void *data, u32 size);
  void Copy(mtl::ALLOC_HANDLE handle, const CCsvbData *source);
  void Copy(mm::mtl::IAllocator *allocator, const CCsvbData *source);
  u16 GetRowCount() const;
  u16 GetColumCount(u16 row) const;
  bool IsValid(u16 row, u16 column) const;
  s32 GetType(u16 row, u16 column) const;
  s32 GetInt(u16 row, u16 column) const;
  f32 GetFloat(u16 row, u16 column) const;
  const char *GetString(u16 row, u16 column) const;
  void Print() const;

  u16 m_rowCount;
  u8 _02[0x08 - 0x02];
  unknown001 *unknown08; // Inferred role: rows; original member name unknown.
  u16 unknown10;         // Inferred role: cell count; original member name unknown.
  u8 _12[0x18 - 0x12];
  unknown002 *unknown18; // Inferred role: cells; original member name unknown.
  u32 unknown20;         // Inferred role: size of the string block; original member name unknown.
  u8 _24[0x28 - 0x24];
  char *unknown28;                // Inferred role: string block; original member name unknown.
  mm::mtl::IAllocator *unknown30; // Inferred role: allocator of the blocks, null for the default memory manager; original member name unknown.
};

static_assert(offsetof(CCsvbData, unknown08) == 0x08, "");
static_assert(offsetof(CCsvbData, unknown10) == 0x10, "");
static_assert(offsetof(CCsvbData, unknown18) == 0x18, "");
static_assert(offsetof(CCsvbData, unknown20) == 0x20, "");
static_assert(offsetof(CCsvbData, unknown28) == 0x28, "");
static_assert(offsetof(CCsvbData, unknown30) == 0x30, "");
static_assert(sizeof(CCsvbData::unknown001) == 0x04, "");
static_assert(sizeof(CCsvbData::unknown002) == 0x10, "");
static_assert(sizeof(CCsvbData) == 0x38, "");

} // namespace csvb

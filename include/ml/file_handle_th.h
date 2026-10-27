#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

class IWorkEvent;

class FileHandleTh {
public:
  bool addCurrentPtr(int offset);
  bool setCurrentPtr(int offset);
  void setReadAdr(int size, void *buffer, int alignedSize);
  void setTime(u64 time);

  u8 _00[0x08];
  void *unknown08; // Inferred role: read buffer; original member name unknown.
  s32 unknown10;   // Inferred role: allocated size; original member name unknown.
  u8 _14[0x18 - 0x14];
  s32 unknown18; // Inferred role: read size; original member name unknown.
  u8 _1c[0x28 - 0x1c];
  s32 m_currentPtr;
  mtl::ALLOC_HANDLE unknown2c; // Inferred role: mem handle; original member name unknown.
  void *unknown30;             // Inferred role: file size; original member name unknown.
  u8 _38[0x60 - 0x38];
  IWorkEvent *unknown60; // Inferred role: event listener; original member name unknown.
  void *unknown68;       // Inferred role: event; original member name unknown.
  u8 _70[0x98 - 0x70];
  u8 unknown98; // Inferred role: path start; original member name unknown.
  u8 _99[0x1c0 - 0x99];
  u64 m_time;
  u64 unknown1c8; // Inferred role: file time; original member name unknown.
};

static_assert(offsetof(FileHandleTh, unknown08) == 0x08, "");
static_assert(offsetof(FileHandleTh, unknown10) == 0x10, "");
static_assert(offsetof(FileHandleTh, unknown18) == 0x18, "");
static_assert(offsetof(FileHandleTh, m_currentPtr) == 0x28, "");
static_assert(offsetof(FileHandleTh, unknown2c) == 0x2c, "");
static_assert(offsetof(FileHandleTh, unknown30) == 0x30, "");
static_assert(offsetof(FileHandleTh, unknown60) == 0x60, "");
static_assert(offsetof(FileHandleTh, unknown68) == 0x68, "");
static_assert(offsetof(FileHandleTh, unknown98) == 0x98, "");
static_assert(offsetof(FileHandleTh, m_time) == 0x1c0, "");
static_assert(offsetof(FileHandleTh, unknown1c8) == 0x1c8, "");

} // namespace ml

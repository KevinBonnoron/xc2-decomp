#pragma once
#include <stddef.h>

#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {
class CriticalSection;
} // namespace ml

namespace grlib {

struct CGLibMemType {
  static const u32 TYPE_EXTERNAL = 5;
  static const u32 TYPE_UNKNOWN_6 = 6;

  CGLibMemType() {
    unknown08 = TYPE_EXTERNAL;
    m_buffer = nullptr;
  }

  void *m_buffer;
  u32 unknown08; // Inferred role: type; original member name unknown.
  u32 unknown0c; // Inferred role: unused, copied with the type as one 8 bytes unit by CGLibSystemContext::releaseDelayVertex; original member name unknown.
};

static_assert(offsetof(CGLibMemType, unknown08) == 0x8, "");
static_assert(sizeof(CGLibMemType) == 0x10, "");

class CGLibMemHandle {
public:
  struct ArgMemInfo {
    u32 unknown00; // Inferred role: first part of the default heap size; original member name unknown.
    u32 unknown04; // Inferred role: pixel heap size; original member name unknown.
    u32 unknown08; // Inferred role: vertex heap size; original member name unknown.
    u32 unknown0c; // Inferred role: uniform heap size; original member name unknown.
    u32 unknown10; // Inferred role: memory heap size; original member name unknown.
    u32 unknown14; // Inferred role: fetch heap size; original member name unknown.
    u32 unknown18; // Inferred role: shader heap size; original member name unknown.
    u32 unknown1c; // Inferred role: counter heap size; original member name unknown.
    u32 unknown20; // Inferred role: second part of the default heap size; original member name unknown.
    u32 unknown24; // Inferred role: third part of the default heap size; original member name unknown.
    u32 unknown28; // Inferred role: fourth part of the default heap size; original member name unknown.
    u32 unknown2c; // Inferred role: fifth part of the default heap size; original member name unknown.
    u32 unknown30; // Inferred role: sixth part of the default heap size; original member name unknown.
  };

  static mtl::ALLOC_HANDLE s_hTop;
  static mtl::ALLOC_HANDLE s_hDefHandle;
  static mtl::ALLOC_HANDLE s_hCntHandle;
  static mtl::ALLOC_HANDLE s_hPxlHandle;
  static mtl::ALLOC_HANDLE s_hVtxHandle;
  static mtl::ALLOC_HANDLE s_hUniHandle;
  static mtl::ALLOC_HANDLE s_hMemHandle;
  static mtl::ALLOC_HANDLE s_hShdHandle;
  static mtl::ALLOC_HANDLE s_hFchHandle;

  static ml::CriticalSection &getCriticalSection();
  static void setup(const ArgMemInfo &info);

  static void setMemBuff(CGLibMemType &memType, void *buffer);
  static void allocVertex(CGLibMemType &memType, u32 size);
  static void allocUniform(CGLibMemType &memType, u32 size);
  static void free(CGLibMemType &memType);
  static void release();
};

static_assert(offsetof(CGLibMemHandle::ArgMemInfo, unknown1c) == 0x1c, "");
static_assert(offsetof(CGLibMemHandle::ArgMemInfo, unknown30) == 0x30, "");
static_assert(sizeof(CGLibMemHandle::ArgMemInfo) == 0x34, "");

} // namespace grlib

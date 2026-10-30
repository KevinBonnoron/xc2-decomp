#pragma once
#include <new>
#include <stddef.h>

#include "grlib/cglib_dec_shader.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "types.h"

namespace grlib {

// Layout evidence: CGLibShdListBase<CGLibDecShader>::createPacShader 0x71007c232c, ~CGLibShdListBase 0x71007c4808.
template <class T> class CGLibShdListBase {
public:
  // Inferred role: header of a shader pack file; original type name unknown.
  // Layout evidence: CGLibShdListBase<CGLibDecShader>::createPacShader 0x71007c232c.
  struct unknown001 {
    u8 unknown00[0x8];
    u32 unknown08; // Inferred role: offset of the shader table; original member name unknown.
    s32 unknown0c; // Inferred role: shader num; original member name unknown.
    u8 unknown10[0x4];
    u32 unknown14; // Inferred role: shader mode; original member name unknown.
    u32 unknown18; // Inferred role: offset of the shader data; original member name unknown.
    u8 unknown1c[0x4];
    u32 unknown20; // Inferred role: offset of the shader code; original member name unknown.
    u32 unknown24; // Inferred role: shader code size; original member name unknown.
    u32 unknown28; // Inferred role: offset of the control data; original member name unknown.
    u8 unknown2c[0x8];
    u32 unknown34; // Inferred role: version; original member name unknown.
  };

  static_assert(offsetof(unknown001, unknown08) == 0x8, "");
  static_assert(offsetof(unknown001, unknown0c) == 0xc, "");
  static_assert(offsetof(unknown001, unknown14) == 0x14, "");
  static_assert(offsetof(unknown001, unknown18) == 0x18, "");
  static_assert(offsetof(unknown001, unknown20) == 0x20, "");
  static_assert(offsetof(unknown001, unknown24) == 0x24, "");
  static_assert(offsetof(unknown001, unknown28) == 0x28, "");
  static_assert(offsetof(unknown001, unknown34) == 0x34, "");
  static_assert(sizeof(unknown001) == 0x38, "");

  // Inferred role: shader table entry of a shader pack file; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: offset of the shader in the shader data; original member name unknown.
    u8 unknown04[0x4];
  };

  static_assert(sizeof(unknown002) == 0x8, "");

  CGLibShdListBase() : unknown40(nullptr), unknown48(nullptr), unknown50(0) {}
  virtual ~CGLibShdListBase() { release(); }
  bool createPacShader(const void *data, u32 version, bool isCopy);

  void release() {
    unknown10.release();
    if (unknown48 != nullptr) {
      for (s32 i = 0; i < unknown50; i++) {
        unknown40[i].~T();
      }
      unknown50 = 0;
      if (unknown48 != nullptr) {
        mtl::MemManager::deallocate(unknown48, 0, false);
        unknown48 = nullptr;
      }
    }
  }

  const void *unknown08;     // Inferred role: shader pack data; original member name unknown.
  CGLibVtlMemPool unknown10; // Inferred role: mem pool; original member name unknown.
  T *unknown40;              // Inferred role: shaders; original member name unknown.
  void *unknown48;           // Inferred role: allocated buffer; original member name unknown.
  s32 unknown50;             // Inferred role: shader num; original member name unknown.
  u32 unknown54;             // Inferred role: shader mode; original member name unknown.
};

template <class T> bool CGLibShdListBase<T>::createPacShader(const void *data, u32 version, bool isCopy) {
  release();
  unknown08 = data;
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown34 != version) {
    return false;
  }
  const u8 *top = static_cast<const u8 *>(data);
  const u8 *shaderData = top + header->unknown18;
  const unknown002 *entry = reinterpret_cast<const unknown002 *>(top + header->unknown08);
  s32 i;
  u32 workSize = 0;
  for (i = 0; i < header->unknown0c; i++, entry++) {
    workSize += T::calcWorkSize(shaderData + entry->unknown00, isCopy);
  }
  u32 shaderSize = header->unknown0c * sizeof(T);
  u32 codeSize = header->unknown24;
  u32 size = (-codeSize & 0xfff) + codeSize;
  // CGLibVtlMemPool::setupBuffer takes a non-const pointer (_ZN5grlib15CGLibVtlMemPool11setupBufferEPvj).
  u8 *code = const_cast<u8 *>(static_cast<const u8 *>(unknown08)) + header->unknown20;
  unknown10.setupBuffer(code, size);
  unknown50 = header->unknown0c;
  unknown54 = header->unknown14;
  u8 *buffer = static_cast<u8 *>(mtl::MemManager::allocate(CGLibMemHandle::s_hShdHandle, shaderSize + workSize, 0x10, false, "no name", 0));
  unknown40 = reinterpret_cast<T *>(buffer);
  unknown48 = buffer;
  const u8 *base = static_cast<const u8 *>(unknown08);
  u8 *work = buffer + shaderSize;
  const unknown002 *table = reinterpret_cast<const unknown002 *>(base + header->unknown08);
  const u8 *control = base + header->unknown28;
  const u8 *shaders = base + header->unknown18;
  u32 workOfs = 0;
  for (i = 0; i < unknown50; i++) {
    new (&unknown40[i]) T();
    workOfs += unknown40[i].createMemPoolShader(work + workOfs, shaders + table[i].unknown00, control, &unknown10, isCopy);
  }
  return true;
}

class CGLibShdListData : public CGLibShdListBase<CGLibDecShader> {
public:
  ~CGLibShdListData() { release(); }
};

static_assert(sizeof(CGLibShdListData) == 0x58, "");

} // namespace grlib

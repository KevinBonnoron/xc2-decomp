#include "grlib/cglib_dec_shader.h"

#include <new>
#include <string.h>

#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_shader.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nn/os.h"

namespace grlib {

CGLibDecShader::CGLibDecShader() : unknown38(nullptr), unknown40(0), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown60(nullptr) {}

CGLibDecShader::~CGLibDecShader() { release(); }

void CGLibDecShader::release() {
  for (int i = 0; i < unknown40; i++) {
    unknown38[i].releaseShader();
  }
  unknown38 = nullptr;
  unknown40 = 0;
  if (unknown48 != nullptr) {
    mtl::MemManager::deallocate(unknown48, 0, false);
    unknown48 = nullptr;
  }
  if (unknown50 != nullptr) {
    mtl::MemManager::deallocate(unknown50, 0, false);
    unknown50 = nullptr;
  }
  unknown08.release();
}

u32 CGLibDecShader::calcWorkSize(const void *data, bool isCopy) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 != 0x54434c53) {
    return 0;
  }
  if (header->unknown04 >> 1 != 0x801) {
    return 0;
  }
  u32 size = header->unknown10 * 0xd8;
  if (isCopy) {
    u32 padding = 0;
    if (header->unknown08 % 4 != 0) {
      padding = 4 - header->unknown08 % 4;
    }
    size = header->unknown08 + size + padding;
  }
  return size;
}

u32 CGLibDecShader::calcTblSize(const void *data) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 != 0x54434c53) {
    return 0;
  }
  if (header->unknown04 >> 1 == 0x801) {
    return header->unknown08;
  }
  return 0;
}

u32 CGLibDecShader::createShader(mtl::ALLOC_HANDLE handle, const void *data, bool isTbl) {
  u32 size = calcWorkSize(data, isTbl);
  release();
  unknown50 = mtl::MemManager::allocate(handle, size, 0x10, false, "no name", 0);
  setupDefShader(data, static_cast<u8 *>(unknown50), isTbl);
  return size;
}

void CGLibDecShader::setupDefShader(const void *data, u8 *buffer, bool isTbl) {
  setupHeadShader(data, buffer, isTbl);
  setupDataShader(false);
}

u32 CGLibDecShader::createShader(void *buffer, const void *data, bool isTbl) {
  u32 size = calcWorkSize(data, isTbl);
  release();
  setupDefShader(data, static_cast<u8 *>(buffer), isTbl);
  return size;
}

u32 CGLibDecShader::createCopyShader(mtl::ALLOC_HANDLE handle, const void *data, bool isTbl) {
  u32 size = calcWorkSize(data, isTbl);
  release();
  unknown50 = mtl::MemManager::allocate(handle, size, 0x10, false, "no name", 0);
  setupCopyShader(data, static_cast<u8 *>(unknown50), isTbl);
  return size;
}

void CGLibDecShader::setupCopyShader(const void *data, u8 *buffer, bool isTbl) {
  setupHeadShader(data, buffer, isTbl);
  setupDataShader(true);
}

u32 CGLibDecShader::createCopyShader(void *buffer, const void *data, bool isTbl) {
  u32 size = calcWorkSize(data, isTbl);
  release();
  setupCopyShader(data, static_cast<u8 *>(buffer), isTbl);
  return size;
}

u32 CGLibDecShader::createMemPoolShader(void *buffer, const u8 *data, const u8 *control, CGLibVtlMemPool *pool, bool isTbl) {
  u32 size = calcWorkSize(data, isTbl);
  release();
  setupMemPoolShader(data, control, pool, static_cast<u8 *>(buffer), isTbl);
  return size;
}

void CGLibDecShader::setupMemPoolShader(const u8 *data, const u8 *control, CGLibVtlMemPool *pool, u8 *buffer, bool isTbl) {
  setupHeadShader(data, buffer, isTbl);
  setupDataMemPoolShader(control, pool);
}

void CGLibDecShader::setupHeadShader(const void *data, u8 *buffer, bool isTbl) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  unknown00 = header;
  unknown40 = header->unknown10;
  unknown38 = reinterpret_cast<CGLibShader *>(buffer);
  for (int i = 0; i < unknown40; i++) {
    new (&unknown38[i]) CGLibShader();
  }
  unknown58 = 0;
  if (isTbl) {
    unknown60 = buffer + unknown40 * sizeof(CGLibShader);
    for (int i = 0; i < static_cast<int>(header->unknown08); i++) {
      unknown60[i] = 0;
    }
  }
}

void CGLibDecShader::setupDataShader(bool isCopy) {
  const unknown001 *header = unknown00;
  const unknown003 *shader = reinterpret_cast<const unknown003 *>(reinterpret_cast<const u8 *>(header) + header->unknown14);
  if (header->unknown04 == 0x1002) {
    for (int i = 0; i < unknown40; i++, shader++) {
      const u8 *shaderData = reinterpret_cast<const u8 *>(unknown00) + shader->unknown00;
      // Original game behaviour: no memory pool is passed although CGLibSetupShader::createShader reads it.
      unknown38[i].createShader(shaderData, 0, shaderData, nullptr, CGLIB_SHDER_TYPE_UNKNOWN_0);
    }
  } else {
    u32 codeSize = header->unknown34;
    // CGLibVtlMemPool::setupBuffer takes a non-const pointer (_ZN5grlib15CGLibVtlMemPool11setupBufferEPvj).
    void *codeData = const_cast<u8 *>(reinterpret_cast<const u8 *>(header)) + header->unknown30;
    if (isCopy) {
      u32 copySize = codeSize + 4;
      u32 size = copySize + (-copySize & 0xfff);
      unknown48 = mtl::MemManager::allocate(CGLibMemHandle::s_hShdHandle, size, 0x1000, false, "no name", 0);
      memcpy(unknown48, codeData, header->unknown34);
      nn::os::FlushDataCache(unknown48, header->unknown34);
      unknown08.setupBuffer(unknown48, size);
    } else {
      u32 size = (-codeSize & 0xfff) + codeSize;
      unknown08.setupBuffer(codeData, size);
    }
    const u8 *control = reinterpret_cast<const u8 *>(unknown00) + header->unknown28;
    const unknown004 *code = reinterpret_cast<const unknown004 *>(reinterpret_cast<const u8 *>(unknown00) + header->unknown1c);
    for (int i = 0; i < unknown40; i++, shader++, code++) {
      unknown38[i].createShader(reinterpret_cast<const u8 *>(unknown00) + shader->unknown00, code->unknown00, control + code->unknown04, &unknown08, CGLIB_SHDER_TYPE_UNKNOWN_0);
    }
  }
}

void CGLibDecShader::setupDataMemPoolShader(const u8 *control, CGLibVtlMemPool *pool) {
  const unknown001 *header = unknown00;
  const u8 *controlBase = control + header->unknown28;
  const unknown003 *shader = reinterpret_cast<const unknown003 *>(reinterpret_cast<const u8 *>(header) + header->unknown14);
  const unknown004 *code = reinterpret_cast<const unknown004 *>(reinterpret_cast<const u8 *>(header) + header->unknown1c);
  for (int i = 0; i < unknown40; i++, shader++, code++) {
    unknown38[i].createShader(reinterpret_cast<const u8 *>(unknown00) + shader->unknown00, header->unknown30 + code->unknown00, controlBase + code->unknown04, pool, CGLIB_SHDER_TYPE_UNKNOWN_0);
  }
}

void CGLibDecShader::changeShaderSetMem(const void *data) { unknown00 = static_cast<const unknown001 *>(data); }

void CGLibDecShader::changeMemPoolSetMem(const u8 *data, const u8 *control, CGLibVtlMemPool *pool) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  unknown00 = header;
  const u8 *controlBase = control + header->unknown28;
  const unknown003 *shader = reinterpret_cast<const unknown003 *>(data + header->unknown14);
  const unknown004 *code = reinterpret_cast<const unknown004 *>(data + header->unknown1c);
  for (int i = 0; i < unknown40; i++, shader++, code++) {
    unknown38[i].changeShaderSetMem(reinterpret_cast<const u8 *>(unknown00) + shader->unknown00, header->unknown30 + code->unknown00, controlBase + code->unknown04, pool);
  }
}

void CGLibDecShader::getDeclarationInfo(const char *&name, int &num, int index) const {
  const unknown002 *declarations = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown0c);
  name = reinterpret_cast<const char *>(unknown00) + declarations[index].unknown08;
  num = declarations[index].unknown00;
}

u32 CGLibDecShader::getDeclarationMax() const { return unknown00->unknown08; }

u32 CGLibDecShader::getShaderMode() { return unknown00->unknown18; }

u32 CGLibDecShader::getDeclarationOfs(const char *name) const {
  const unknown002 *declarations = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown0c);
  int count = unknown00->unknown08;
  for (int i = 0; i < count; i++, declarations++) {
    if (strcmp(name, reinterpret_cast<const char *>(unknown00) + declarations->unknown08) == 0) {
      return i;
    }
  }
  return -1;
}

void CGLibDecShader::setDeclarationIdx(u32 offset, u32 index) {
  if (offset == 0xffffffff || offset >= unknown00->unknown08) {
    return;
  }
  const unknown002 *declarations = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown0c);
  unknown58 -= unknown60[offset] * declarations[offset].unknown04;
  if (index < 2) {
    unknown60[offset] = 0;
    return;
  }
  if (index > declarations[offset].unknown00) {
    unknown60[offset] = declarations[offset].unknown00 - 1;
    unknown58 += unknown60[offset] * declarations[offset].unknown04;
  } else {
    unknown60[offset] = index - 1;
    unknown58 += unknown60[offset] * declarations[offset].unknown04;
  }
}

} // namespace grlib

#include "cglib_dec_shd_ext_tbl.cpp"
#include "cglib_display_list.cpp"
#include "cglib_shader.cpp"
#include "cglib_uni_base_utility.cpp"
#include "cglib_uniform_block.cpp"

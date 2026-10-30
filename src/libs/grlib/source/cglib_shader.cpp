#include "grlib/cglib_shader.h"

#include <string.h>

#include "grlib/cglib_manager.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "nvn/nvn.h"

namespace grlib {

namespace {

// Inferred role: NVN shader stage of each stage index; original name unknown.
const u32 unknown004[6] = {0, 1, 2, 3, 4, 5};

} // namespace

void CGLibShader_plf::setUniformBlock(u32 index, NVNcommandBuffer *cmdBuf, u64 address, u32 size) {
  if (index < unknown08->unknown22) {
    u8 blockIndex = (m_data + unknown08->unknown28)[index];
    if (blockIndex != 0xff) {
      const unknown028 &block = reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown24)[blockIndex];
      u32 bindNum = block.unknown0d;
      const unknown001 *bind = reinterpret_cast<const unknown001 *>(m_data + block.unknown08);
      for (u32 i = 0; i < bindNum; i++, bind++) {
        nvnCommandBufferBindUniformBuffer(cmdBuf, static_cast<NVNshaderStage>(unknown004[bind->unknown00]), bind->unknown01, address, static_cast<int>(size));
      }
    }
  }
}

void CGLibShader_plf::setStorageBuffer(u32 index, NVNcommandBuffer *cmdBuf, u64 address, u32 size) {
  if (index < unknown08->unknown2e) {
    u8 blockIndex = (m_data + unknown08->unknown34)[index];
    if (blockIndex != 0xff) {
      const unknown028 &block = reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown30)[blockIndex];
      u32 bindNum = block.unknown0d;
      const unknown001 *bind = reinterpret_cast<const unknown001 *>(m_data + block.unknown08);
      for (u32 i = 0; i < bindNum; i++, bind++) {
        nvnCommandBufferBindStorageBuffer(cmdBuf, static_cast<NVNshaderStage>(unknown004[bind->unknown00]), bind->unknown01, address, static_cast<int>(size));
      }
    }
  }
}

void CGLibShader_plf::setTextureHandle(u32 index, NVNcommandBuffer *cmdBuf, u64 handle) {
  if (index < unknown08->unknown3a) {
    u8 slotIndex = (m_data + unknown08->unknown40)[index];
    if (slotIndex != 0xff) {
      const unknown002 &slot = reinterpret_cast<const unknown002 *>(m_data + unknown08->unknown3c)[slotIndex];
      u32 bindNum = slot.unknown09;
      const unknown001 *bind = reinterpret_cast<const unknown001 *>(m_data + slot.unknown04);
      for (u32 i = 0; i < bindNum; i++, bind++) {
        nvnCommandBufferBindTexture(cmdBuf, static_cast<NVNshaderStage>(unknown004[bind->unknown00]), bind->unknown01, handle);
      }
    }
  }
}

void CGLibShader_plf::setImageHandle(u32 index, NVNcommandBuffer *cmdBuf, u64 handle) {
  if (index < unknown08->unknown46) {
    u8 slotIndex = (m_data + unknown08->unknown4c)[index];
    if (slotIndex != 0xff) {
      const unknown002 &slot = reinterpret_cast<const unknown002 *>(m_data + unknown08->unknown48)[slotIndex];
      u32 bindNum = slot.unknown09;
      const unknown001 *bind = reinterpret_cast<const unknown001 *>(m_data + slot.unknown04);
      for (u32 i = 0; i < bindNum; i++, bind++) {
        nvnCommandBufferBindImage(cmdBuf, static_cast<NVNshaderStage>(unknown004[bind->unknown00]), bind->unknown01, handle);
      }
    }
  }
}

bool CGLibSetupShader::createShader(CGLibShader *shader, const u8 *data, u32 offset, const u8 *control, CGLibVtlMemPool *pool) {
  releaseShader(shader);
  nvnProgramInitialize(&shader->unknown18, &CGLibManager::get()->unknown00);
  const unknown029 *info = reinterpret_cast<const unknown029 *>(data);
  shader->unknown14 = 0;
  const CGLibShader::unknown005 *stages = reinterpret_cast<const CGLibShader::unknown005 *>(data + info->unknown18);
  // Inferred role: stage 5 is compute (NVN compute stage bit 0x20), otherwise all graphics stage bits (0x1f).
  u64 address = pool->unknown08;
  shader->unknown14 = stages->unknown00 == 5 ? 0x20 : 0x1f;
  NVNshaderData stageData[6];
  int count = 0;
  for (int i = 0; i < info->unknown1c; i++, stages++) {
    stageData[i].control = control + stages->unknown0c;
    stageData[i].data = address + offset + stages->unknown04;
    count = info->unknown1c;
  }
  nvnProgramSetShaders(&shader->unknown18, count, stageData);
  shader->unknown10 |= 1;
  shader->m_data = data;
  shader->unknown08 = info;
  return true;
}

void CGLibSetupShader::releaseShader(CGLibShader *shader) {
  if (shader->unknown10 & 1) {
    shader->m_data = nullptr;
    nvnProgramFinalize(&shader->unknown18);
    shader->unknown10 &= ~5;
  }
}

void CGLibShader::releaseShader() { CGLibSetupShader::releaseShader(this); }

CGLibShader::CGLibShader() : unknown10(0) { m_data = nullptr; }

CGLibShader::~CGLibShader() { releaseShader(); }

void CGLibShader::createShader(const u8 *data, u32 offset, const u8 *control, CGLibVtlMemPool *pool, CGLibShderType type) {
  releaseShader();
  changeShaderSetMem(data, offset, control, pool);
}

void CGLibShader::changeShaderSetMem(const void *data) {}

void CGLibShader::changeShaderSetMem(const u8 *data, u32 offset, const u8 *control, CGLibVtlMemPool *pool) { CGLibSetupShader::createShader(this, data, offset, control, pool); }

int CGLibShader::getTextureLocation(const char *name) const {
  u32 num = unknown08->unknown38;
  if (num != 0) {
    const unknown002 *slots = reinterpret_cast<const unknown002 *>(m_data + unknown08->unknown3c);
    for (u32 i = 0; i < num; i++, slots++) {
      if (strcmp(reinterpret_cast<const char *>(m_data + slots->unknown00), name) == 0) {
        return slots->unknown08;
      }
    }
  }
  return -1;
}

int CGLibShader::getImageLocation(const char *name) const {
  u32 num = unknown08->unknown44;
  if (num != 0) {
    const unknown002 *slots = reinterpret_cast<const unknown002 *>(m_data + unknown08->unknown48);
    for (u32 i = 0; i < num; i++, slots++) {
      if (strcmp(reinterpret_cast<const char *>(m_data + slots->unknown00), name) == 0) {
        return slots->unknown08;
      }
    }
  }
  return -1;
}

int CGLibShader::getUniformBlockOfs(const char *name) const {
  u32 num = unknown08->unknown20;
  if (num != 0) {
    const unknown028 *blocks = reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown24);
    for (u32 i = 0; i < num; i++, blocks++) {
      if (strcmp(reinterpret_cast<const char *>(m_data + blocks->unknown00), name) == 0) {
        return blocks->unknown0c;
      }
    }
  }
  return -1;
}

u16 CGLibShader::getUniformBlockSize(u32 index) const {
  if (index > unknown08->unknown22) {
    return 0;
  }
  u8 blockIndex = (m_data + unknown08->unknown28)[index];
  if (blockIndex != 0xff) {
    return reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown24)[blockIndex].unknown0e;
  }
  return 0;
}

u32 CGLibShader::getUniformBlockValOfs(u32 index, const char *name) const {
  if (index > unknown08->unknown22) {
    return 0;
  }
  u8 blockIndex = (m_data + unknown08->unknown28)[index];
  if (blockIndex != 0xff) {
    const unknown028 &block = reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown24)[blockIndex];
    u32 valueNum = block.unknown04;
    if (valueNum != 0) {
      const unknown003 *values = reinterpret_cast<const unknown003 *>(m_data + unknown08->unknown5c) + block.unknown06;
      for (u32 i = 0; i < valueNum; i++, values++) {
        if (strcmp(reinterpret_cast<const char *>(m_data + values->unknown00), name) == 0) {
          return values->unknown04;
        }
      }
      return -1;
    }
  }
  return -1;
}

int CGLibShader::getStorageBufferOfs(const char *name) const {
  u32 num = unknown08->unknown2c;
  if (num != 0) {
    const unknown028 *blocks = reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown30);
    for (u32 i = 0; i < num; i++, blocks++) {
      if (strcmp(reinterpret_cast<const char *>(m_data + blocks->unknown00), name) == 0) {
        return blocks->unknown0c;
      }
    }
  }
  return -1;
}

u16 CGLibShader::getStorageBufferSize(u32 index) const {
  if (index > unknown08->unknown2e) {
    return 0;
  }
  u8 blockIndex = (m_data + unknown08->unknown34)[index];
  if (blockIndex != 0xff) {
    return reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown30)[blockIndex].unknown0e;
  }
  return 0;
}

u32 CGLibShader::getStorageBufferValOfs(u32 index, const char *name) const {
  if (index > unknown08->unknown2e) {
    return 0;
  }
  u8 blockIndex = (m_data + unknown08->unknown34)[index];
  if (blockIndex != 0xff) {
    const unknown028 &block = reinterpret_cast<const unknown028 *>(m_data + unknown08->unknown30)[blockIndex];
    u32 valueNum = block.unknown04;
    if (valueNum != 0) {
      const unknown003 *values = reinterpret_cast<const unknown003 *>(m_data + unknown08->unknown5c) + block.unknown06;
      for (u32 i = 0; i < valueNum; i++, values++) {
        if (strcmp(reinterpret_cast<const char *>(m_data + values->unknown00), name) == 0) {
          return values->unknown04;
        }
      }
      return -1;
    }
  }
  return -1;
}

} // namespace grlib

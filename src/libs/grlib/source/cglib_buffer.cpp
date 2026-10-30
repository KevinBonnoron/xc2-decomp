#include <new>
#include <string.h>

#include "grlib/cglib_buff_fix_alloc.h"
#include "grlib/cglib_buff_mem_pool_tbl.h"
#include "grlib/cglib_buff_min_uniform.h"
#include "grlib/cglib_buff_occlusion.h"
#include "grlib/cglib_buff_release_tbl.h"
#include "grlib/cglib_buff_texture.h"
#include "grlib/cglib_buffer.h"
#include "grlib/cglib_cmd_buffer.h"
#include "grlib/cglib_manager.h"
#include "grlib/cglib_mem_handle.h"
#include "grlib/cglib_mem_pool.h"
#include "grlib/cglib_mem_pool_adder.h"
#include "grlib/cglib_mem_pool_list.h"
#include "grlib/cglib_parts_mem_pool.h"
#include "grlib/cglib_pipeline.h"
#include "grlib/cglib_release_obj.h"
#include "grlib/cglib_sampler_descriptor.h"
#include "grlib/cglib_system_context.h"
#include "grlib/cglib_tex_descriptor.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "ml/critical_section.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"
#include "nn/diag.h"
#include "nvn/nvn.h"
#include "types.h"

struct NVNmemoryPool;
struct NVNtexture;

namespace grlib {

u8 *CGLibBuffMinUniform::allocBuffer() {
  u32 id = allocID();
  return m_buffer + unknown10 * id;
}

ml::CriticalSection &CGLibMemHandle::getCriticalSection() {
  static ml::CriticalSection s_criticalSection;
  return s_criticalSection;
}

void CGLibMemHandle::setMemBuff(CGLibMemType &memType, void *buffer) {
  ml::CS lock(getCriticalSection());
  memType.m_buffer = buffer;
  memType.unknown08 = CGLibMemType::TYPE_EXTERNAL;
}

void CGLibMemHandle::allocVertex(CGLibMemType &memType, u32 size) {
  ml::CS lock(getCriticalSection());
  if (size <= 0x80) {
    memType.unknown08 = 0;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[0].allocBuffer();
  } else if (size <= 0x100) {
    memType.unknown08 = 1;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[1].allocBuffer();
  } else if (size <= 0x200) {
    memType.unknown08 = 2;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[2].allocBuffer();
  } else if (size <= 0x300) {
    memType.unknown08 = 3;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[3].allocBuffer();
  } else if (size <= 0x400) {
    memType.unknown08 = 4;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[4].allocBuffer();
  } else {
    memType.m_buffer = mtl::MemManager::allocate(s_hVtxHandle, size, 4, false, "no name", 0);
    memType.unknown08 = CGLibMemType::TYPE_UNKNOWN_6;
  }
}

void CGLibMemHandle::allocUniform(CGLibMemType &memType, u32 size) {
  ml::CS lock(getCriticalSection());
  if (size <= 0x100) {
    memType.unknown08 = 1;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[1].allocBuffer();
  } else if (size <= 0x200) {
    memType.unknown08 = 2;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[2].allocBuffer();
  } else if (size <= 0x300) {
    memType.unknown08 = 3;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[3].allocBuffer();
  } else if (size <= 0x400) {
    memType.unknown08 = 4;
    memType.m_buffer = context::CGLibSystemContext::get()->unknownf08[4].allocBuffer();
  } else {
    memType.m_buffer = mtl::MemManager::allocate(s_hUniHandle, size, 0x100, false, "no name", 0);
    memType.unknown08 = CGLibMemType::TYPE_UNKNOWN_6;
  }
}

void CGLibBuffFixAlloc::freeBuffer(void *buffer) {
  u32 index = static_cast<u64>(static_cast<u8 *>(buffer) - m_buffer) / unknown10;
  unknown08[index >> 6] &= ~(1ul << (index & 0x3f));
  unknown14--;
}

CGLibBuffFixAlloc::CGLibBuffFixAlloc() : m_buffer(nullptr), unknown08(nullptr), unknown18(0), unknown1c(0) {}

CGLibBuffFixAlloc::~CGLibBuffFixAlloc() { releaseTbl(); }

void CGLibBuffFixAlloc::releaseTbl() {
  if (m_buffer != nullptr) {
    mtl::MemManager::deallocate(m_buffer, 0, false);
    m_buffer = nullptr;
  }
  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 alignment) {
  setupTbl(tableHandle, num, unitSize);
  u32 bufferSize = unknown10 * unknown1c;
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(bufferHandle, bufferSize, alignment, false, "no name", 0));
}

void CGLibBuffFixAlloc::setupTbl(mtl::ALLOC_HANDLE tableHandle, u32 num, u32 unitSize) {
  releaseTbl();
  unknown10 = unitSize;
  u32 wordNum = num / 64 + (num % 64 != 0 ? 1 : 0);
  unknown1c = num;
  unknown20 = wordNum;
  u32 tableSize = wordNum * sizeof(u64);
  unknown08 = static_cast<u64 *>(mtl::MemManager::allocate(tableHandle, tableSize, 16, false, "no name", 0));
  unknown24 = 0;
  unknown14 = 0;
  unknown18 = 0;
  memset(unknown08, 0, tableSize);
}

void CGLibBuffFixAlloc::setupFixTbl(mtl::ALLOC_HANDLE tableHandle, mtl::ALLOC_HANDLE bufferHandle, u32 num, u32 unitSize, u32 bufferSize, u32 alignment) {
  setupTbl(tableHandle, num, unitSize);
  m_buffer = static_cast<u8 *>(mtl::MemManager::allocate(bufferHandle, bufferSize, alignment, false, "no name", 0));
}

void CGLibBuffFixAlloc::freeID(u32 id) {
  unknown08[id >> 6] &= ~(1ul << (static_cast<u64>(id) & 0x3f));
  unknown14--;
}

u32 CGLibBuffFixAlloc::createBuff() {
  unknown08[unknown18 >> 6] |= 1ul << (unknown18 & 0x3f);
  int id = unknown18;
  if (id + 1 < unknown1c) {
    unknown18 = id + 1;
  } else {
    unknown18 = 0;
  }
  unknown24 = unknown18 >> 6;
  unknown14++;
  return id;
}

void CGLibBuffTexture_plf::createPlf(u32 num, u8 *buffer) { unknown00 = buffer; }

void CGLibBuffTexture_plf::releasePlf() { unknown00 = nullptr; }

CGLibBuffTexture::CGLibBuffTexture() { unknown00 = nullptr; }

CGLibBuffTexture::~CGLibBuffTexture() { release(); }

void CGLibBuffTexture::release() {
  releasePlf();
  releaseTbl();
}

void CGLibBuffTexture::createTexture(u32 num) {
  release();
  setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0xc0, 0x10);
  createPlf(num, m_buffer);
}

u32 CGLibBuffOcclusion_plf::createPlf(u32 num, u8 *buffer) { return num; }

int CGLibBuffOcclusion_plf::getBufferSize() { return context::CGLibSystemContext::s_nvReportCounterSize << 1; }

void CGLibBuffOcclusion_plf::releasePlf() {}

CGLibBuffOcclusion::CGLibBuffOcclusion() {}

CGLibBuffOcclusion::~CGLibBuffOcclusion() { release(); }

void CGLibBuffOcclusion::release() {
  releasePlf();
  releaseTbl();
}

void CGLibBuffOcclusion::createOcclusion(u32 num) {
  release();
  setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hCntHandle, num, getBufferSize(), 0x1000);
  createPlf(num, m_buffer);
}

CGLibBuffMemPoolTbl::CGLibBuffMemPoolTbl() {}

CGLibBuffMemPoolTbl::~CGLibBuffMemPoolTbl() { release(); }

void CGLibBuffMemPoolTbl::release() { releaseTbl(); }

void CGLibBuffMemPoolTbl::createMemPoolTbl(u32 num) {
  release();
  setupTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, num, 0x100, 0x100);
}

CGLibBuffMinUniform::CGLibBuffMinUniform() { release(); }

CGLibBuffMinUniform::~CGLibBuffMinUniform() {}

void CGLibBuffMinUniform::release() {
  unknown28.release();
  releaseTbl();
}

void CGLibBuffMinUniform::createUniform(u32 size, u32 unitSize) {
  release();
  setupFixTbl(CGLibMemHandle::s_hDefHandle, CGLibMemHandle::s_hDefHandle, size / unitSize, unitSize, size, 0x1000);
  unknown28.setupBuffer(m_buffer, size, 0x24);
}

CGLibBuffer::CGLibBuffer() {}

CGLibBuffer::~CGLibBuffer() { nvnBufferFinalize(&m_buffer); }

void CGLibBuffer::release() { nvnBufferFinalize(&m_buffer); }

void CGLibBuffer::setup(u32 offset, u32 size, CGLibMemPool &memPool) {
  nvnBufferFinalize(&m_buffer);
  NVNbufferBuilder builder;
  nvnBufferBuilderSetDefaults(&builder);
  nvnBufferBuilderSetDevice(&builder, &CGLibManager::get()->unknown00);
  nvnBufferBuilderSetStorage(&builder, memPool.m_memoryPool, offset, size);
  nvnBufferInitialize(&m_buffer, &builder);
}

void CGLibBuffer::updateData() {}

void CGLibBuffer::setUniformBlock(u32 index) {}

void CGLibBuffer::setStorageBuffer(u32 index) {}

void CGLibBuffer::updateMaping() {}

CGLibVtlMemPool::CGLibVtlMemPool() {
  m_size = 0;
  m_buffer = nullptr;
  unknown20 = false;
  unknown18 = 0;
}

CGLibVtlMemPool::~CGLibVtlMemPool() { release(); }

void CGLibVtlMemPool::release() {
  if (unknown20) {
    nvnMemoryPoolFinalize(unknown00);
    context::CGLibSystemContext::get()->unknowne90.freeBuffer(unknown00);
  }
  m_size = 0;
  m_buffer = nullptr;
  unknown20 = false;
  unknown18 = 0;
}

void CGLibVtlMemPool::delayRelease() {
  if (unknown20) {
    context::CGLibSystemContext::get()->releaseDelayMempool(unknown00, nullptr);
  }
  m_size = 0;
  m_buffer = nullptr;
  unknown20 = false;
  unknown18 = 0;
}

CGLibMemPool::CGLibMemPool() : unknown08(0), unknown10(nullptr), unknown18(nullptr) {}

CGLibMemPool::~CGLibMemPool() { release(); }

void CGLibMemPool::release() {
  if (unknown08 != 0) {
    nvnMemoryPoolFinalize(m_memoryPool);
    context::CGLibSystemContext::get()->unknowne90.freeBuffer(m_memoryPool);
    unknown08 = 0;
    if (unknown10 != nullptr) {
      mtl::MemManager::deallocate(unknown10, 0, false);
      unknown10 = nullptr;
    }
    m_memoryPool = nullptr;
  }
}

void CGLibMemPool::delayRelease() {
  if (unknown08 != 0) {
    context::CGLibSystemContext::get()->releaseDelayMempool(m_memoryPool, unknown10);
    unknown10 = nullptr;
    unknown08 = 0;
  }
}

void CGLibMemPool::setupHandle(mtl::ALLOC_HANDLE handle, u32 size, u32 flags) {
  release();
  unknown10 = mtl::MemManager::allocate(handle, size, 0x1000, false, "no name", 0);
  setupBuffer(unknown10, size + (-size & 0xfff), flags);
}

CGLibMemPoolList::CGLibMemPoolList() : unknown20(0) {}

CGLibMemPoolList::~CGLibMemPoolList() { release(); }

void CGLibMemPoolList::release() {
  CGLibMemPool::release();
  unknown20 = 0;
}

void CGLibMemPoolList::setupHandle(mtl::ALLOC_HANDLE handle, u32 size, u32 flags) { CGLibMemPool::setupHandle(handle, size, flags); }

int CGLibMemPoolList::cntOffset(u32 size, u32 alignment) {
  int offset = unknown20 + (alignment - unknown20 % alignment) % alignment;
  u32 padding = (alignment - size % alignment) % alignment;
  unknown20 = offset + size + padding;
  return offset;
}

CGLibReleaseObj::CGLibReleaseObj() : unknown20(nullptr) {
  unknown00.unknown00 = nullptr;
  unknown00.unknown08 = nullptr;
  unknown00.unknown10 = 0;
  unknown00.unknown14 = 0;
  unknown00.unknown18 = 0;
  unknown00.unknown1a = 0;
  unknown00.unknown1c = 0;
}

CGLibReleaseObj::~CGLibReleaseObj() { release(); }

void CGLibReleaseObj::release() {
  if (unknown00.unknown18 & 1) {
    s_callRelease[unknown00.unknown1a](unknown00);
    unknown00.unknown10 = 0;
    unknown00.unknown14 = 0;
    unknown00.unknown18 = 0;
    unknown00.unknown1a = 0;
    unknown00.unknown1c = 0;
    unknown00.unknown00 = nullptr;
    unknown00.unknown08 = nullptr;
  }
}

CGLibBuffReleaseTbl::CGLibBuffReleaseTbl() : unknown00(0), unknown08(nullptr) {
  unknown20[1].unknown00 = nullptr;
  unknown20[1].unknown08 = nullptr;
  unknown20[0].unknown00 = nullptr;
  unknown20[0].unknown08 = nullptr;
  unknown10 = nullptr;
  unknown18 = nullptr;
}

CGLibBuffReleaseTbl::~CGLibBuffReleaseTbl() { release(); }

void CGLibBuffReleaseTbl::release() {
  for (int i = 0; i < unknown00; i++) {
    unknown08[i].release();
  }
  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
  unknown00 = 0;
  unknown20[1].unknown00 = nullptr;
  unknown20[1].unknown08 = nullptr;
  unknown20[0].unknown00 = nullptr;
  unknown20[0].unknown08 = nullptr;
  unknown10 = nullptr;
  unknown18 = nullptr;
}

int CGLibBuffReleaseTbl::setup(u32 num) {
  release();
  unknown00 = num;
  u32 size = num * sizeof(CGLibReleaseObj);
  unknown08 = static_cast<CGLibReleaseObj *>(mtl::MemManager::allocate(CGLibMemHandle::s_hDefHandle, size, 0x10, false, "no name", 0));
  for (int i = 0; i < unknown00; i++) {
    new (&unknown08[i]) CGLibReleaseObj();
    CGLibReleaseObj *obj = &unknown08[i];
    if (unknown18 == nullptr) {
      unknown10 = obj;
    } else {
      unknown18->unknown20 = obj;
    }
    unknown18 = obj;
    obj->unknown20 = nullptr;
  }
  return size;
}

CGLibReleaseObj *CGLibBuffReleaseTbl::createObj() {
  CGLibReleaseObj *obj = unknown10;
  if (obj != nullptr) {
    CGLibReleaseObj *next = obj->unknown20;
    unknown10 = next;
    if (next == nullptr) {
      unknown18 = nullptr;
    }
    obj->unknown20 = nullptr;
  }
  unknown001 &list = unknown20[CGLibManager::s_nStkNowIdx];
  if (list.unknown08 == nullptr) {
    list.unknown00 = obj;
  } else {
    list.unknown08->unknown20 = obj;
  }
  list.unknown08 = obj;
  obj->unknown20 = nullptr;
  return obj;
}

void CGLibBuffReleaseTbl::update() {
  CGLibReleaseObj *obj = unknown20[CGLibManager::s_nDblNowIdx].unknown00;
  if (obj != nullptr) {
    do {
      CGLibReleaseObj *next = obj->unknown20;
      obj->release();
      if (unknown18 == nullptr) {
        unknown10 = obj;
      } else {
        unknown18->unknown20 = obj;
      }
      unknown18 = obj;
      obj->unknown20 = nullptr;
      obj = next;
    } while (obj != nullptr);
    unknown20[CGLibManager::s_nDblNowIdx].unknown00 = nullptr;
    unknown20[CGLibManager::s_nDblNowIdx].unknown08 = nullptr;
  }
}

void CGLibReleaseObj_plf::release_mempool(wrkRelease &work) {
  if (work.unknown18 & 2) {
    nvnMemoryPoolFinalize(static_cast<NVNmemoryPool *>(work.unknown00));
    context::CGLibSystemContext::get()->unknowne90.freeBuffer(work.unknown00);
  }
  if (work.unknown08 != nullptr) {
    mtl::MemManager::deallocate(work.unknown08, 0, false);
    work.unknown08 = nullptr;
  }
}

void CGLibReleaseObj_plf::release_textrue(wrkRelease &work) {
  if (work.unknown18 & 4) {
    nvnTextureFinalize(static_cast<NVNtexture *>(work.unknown00));
    context::CGLibSystemContext::get()->unknowne60.freeBuffer(work.unknown00);
  }
  if (work.unknown08 != nullptr) {
    mtl::MemManager::deallocate(work.unknown08, 0, false);
    work.unknown08 = nullptr;
  }
  if (work.unknown10 != -1) {
    context::CGLibSystemContext::get()->unknown538.freeID(work.unknown10);
  }
  if (work.unknown14 != -1) {
    context::CGLibSystemContext::get()->unknown538.freeID(work.unknown14);
  }
}

void CGLibReleaseObj_plf::release_vertex(wrkRelease &work) { CGLibMemHandle::free(reinterpret_cast<CGLibMemType &>(work)); }

CGLibTexDescriptor::CGLibTexDescriptor() {}

CGLibTexDescriptor::~CGLibTexDescriptor() { release(); }

void CGLibTexDescriptor_plf::bindTexture(const CGLibTextureBuffer &texture, int textureId, int imageId) {
  nvnTexturePoolRegisterTexture(&unknown48, context::CGLibSystemContext::s_nNnumReservedTextures + textureId, texture.unknown18, nullptr);
  if (imageId != -1) {
    nvnTexturePoolRegisterImage(&unknown48, context::CGLibSystemContext::s_nNnumReservedTextures + imageId, texture.unknown18, nullptr);
  }
}

int CGLibTexDescriptor_plf::setTexture(const CGLibTextureBuffer &texture) { return texture.unknown34 + context::CGLibSystemContext::s_nNnumReservedTextures; }

int CGLibTexDescriptor_plf::setImage(const CGLibTextureBuffer &texture) { return texture.unknown38 + context::CGLibSystemContext::s_nNnumReservedTextures; }

void CGLibTexDescriptor::release() {
  nvnTexturePoolFinalize(&unknown48);
  unknown28.release();
  releaseTbl();
}

int CGLibTexDescriptor::setup(void *buffer, u32 num) {
  int size = context::CGLibSystemContext::s_nvTextureSize * num;
  unknown28.setupBuffer(buffer, size, 0x22);
  nvnTexturePoolInitialize(&unknown48, unknown28.m_memoryPool, 0, num);
  return size;
}

int CGLibTexDescriptor::setup(mtl::ALLOC_HANDLE handle, u32 num) {
  int size = context::CGLibSystemContext::s_nvTextureSize * num;
  u32 alignedSize = size + (-size & 0xfff);
  unknown28.setupHandle(handle, alignedSize, 0x22);
  nvnTexturePoolInitialize(&unknown48, unknown28.m_memoryPool, 0, num);
  return size;
}

int CGLibTexDescriptor::setup(CGLibMemPool &memPool, u32 offset, u32 num) {
  int size = context::CGLibSystemContext::s_nvTextureSize * num;
  nvnTexturePoolInitialize(&unknown48, memPool.m_memoryPool, offset, num);
  return size;
}

void CGLibTexDescriptor::reset() {}

void CGLibTexDescriptor::bind() { nvnCommandBufferSetTexturePool(context::CGLibSystemContext::get()->unknown1070.unknown00, &unknown48); }

CGLibSamplerDescriptor::CGLibSamplerDescriptor() {}

CGLibSamplerDescriptor::~CGLibSamplerDescriptor() { release(); }

void CGLibSamplerDescriptor::release() {
  nvnSamplerPoolFinalize(&unknown48);
  unknown28.release();
  releaseTbl();
}

int CGLibSamplerDescriptor::setup(void *buffer, u32 num) {
  int size = context::CGLibSystemContext::s_nvSamplerSize * num;
  unknown28.setupBuffer(buffer, size, 0x22);
  nvnSamplerPoolInitialize(&unknown48, unknown28.m_memoryPool, 0, num);
  return size;
}

int CGLibSamplerDescriptor::setup(mtl::ALLOC_HANDLE handle, u32 num) {
  int size = context::CGLibSystemContext::s_nvSamplerSize * num;
  u32 alignedSize = size + (-size & 0xfff);
  unknown28.setupHandle(handle, alignedSize, 0x22);
  nvnSamplerPoolInitialize(&unknown48, unknown28.m_memoryPool, 0, num);
  return size;
}

int CGLibSamplerDescriptor::setup(CGLibMemPool &memPool, u32 offset, u32 num) {
  int size = context::CGLibSystemContext::s_nvSamplerSize * num;
  nvnSamplerPoolInitialize(&unknown48, memPool.m_memoryPool, offset, num);
  return size;
}

void CGLibSamplerDescriptor::reset() {}

void CGLibSamplerDescriptor::bind() { nvnCommandBufferSetSamplerPool(context::CGLibSystemContext::get()->unknown1070.unknown00, &unknown48); }

CGLibPartsMemPool::~CGLibPartsMemPool() { unknown10.release(); }

void CGLibPartsMemPool::addAdder(void *buffer, u32 size) { unknown10.setupBuffer(buffer, size, 100); }

ml::CriticalSection &CGLibMemPoolAdder::getCriticalSection() {
  static ml::CriticalSection s_criticalSection;
  return s_criticalSection;
}

CGLibMemPoolAdder::CGLibMemPoolAdder() : unknown00(nullptr), unknown08(nullptr) {}

CGLibMemPoolAdder::~CGLibMemPoolAdder() { release(); }

void CGLibMemPoolAdder::release() {
  CGLibPartsMemPool *pool = unknown00;
  while (pool != nullptr) {
    CGLibPartsMemPool *next = pool->unknown08;
    delete pool;
    pool = next;
  }
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void CGLibMemPoolAdder::setup() { release(); }

CGLibMemPool *CGLibMemPoolAdder::getMemPool(const void *address) {
  ml::CS lock(getCriticalSection());
  for (CGLibPartsMemPool *pool = unknown00; pool != nullptr; pool = pool->unknown08) {
    u64 base = reinterpret_cast<u64>(pool->unknown10.unknown18);
    u64 target = reinterpret_cast<u64>(address);
    if (base <= target && target - base < pool->unknown10.unknown08) {
      return &pool->unknown10;
    }
  }
  return nullptr;
}

void CGLibMemPoolAdder::addAdder(mtl::ALLOC_HANDLE handle) { addAdder(reinterpret_cast<void *>(mtl::MemManager::getTopAdr(handle)), mtl::MemManager::getTotalSize(handle)); }

void CGLibMemPoolAdder::releaseAdder(mtl::ALLOC_HANDLE handle) { releaseAdder(reinterpret_cast<void *>(mtl::MemManager::getTopAdr(handle))); }

void CGLibMemPoolAdder::releaseAdder(void *buffer) {
  ml::CS lock(getCriticalSection());
  for (CGLibPartsMemPool *pool = unknown00; pool != nullptr; pool = pool->unknown08) {
    if (pool->unknown10.unknown18 == buffer) {
      CGLibPartsMemPool *previous = pool->unknown00;
      CGLibPartsMemPool *next = pool->unknown08;
      if (previous == nullptr) {
        if (next == nullptr) {
          unknown00 = nullptr;
          unknown08 = nullptr;
        } else {
          unknown00 = next;
          next->unknown00 = nullptr;
        }
      } else if (next == nullptr) {
        unknown08 = previous;
        previous->unknown08 = nullptr;
      } else {
        previous->unknown08 = next;
        pool->unknown08->unknown00 = pool->unknown00;
      }
      pool->unknown00 = nullptr;
      pool->unknown08 = nullptr;
      delete pool;
      break;
    }
  }
}

namespace {

// Inferred role: command buffer memory callback; original name unknown.
void unknown003(NVNcommandBuffer *cmdBuf, NVNcommandBufferMemoryEvent event, size_t minSize, void *callbackData);

} // namespace

void CGLibCmdBuffer_plf::setCallback() {
  nvnCommandBufferSetMemoryCallback(&unknown00, unknown003);
  nvnCommandBufferSetMemoryCallbackData(&unknown00, this);
}

CGLibCmdBuffer::CGLibCmdBuffer() : unknowne0(0), unknowne4(0), unknowne8(false) {}

CGLibCmdBuffer::~CGLibCmdBuffer() { release(); }

void CGLibCmdBuffer::release() {
  if (unknowne8) {
    nvnCommandBufferFinalize(&unknown00);
    unknowna0.release();
  }
}

void CGLibCmdBuffer::setup(mtl::ALLOC_HANDLE handle, u32 size, u32 controlSize) {
  release();
  nvnCommandBufferInitialize(&unknown00, &CGLibManager::get()->unknown00);
  unknowna0.setupHandle(handle, size, 0x11);
  unknownd8 = &unknowna0;
  unknownc8 = 0;
  unknowncc = size - controlSize;
  unknownd0 = controlSize;
  setCallback();
  unknowne8 = true;
}

void CGLibCmdBuffer::setup(void *buffer, u32 size, u32 controlSize) {
  release();
  nvnCommandBufferInitialize(&unknown00, &CGLibManager::get()->unknown00);
  unknowna0.setupBuffer(buffer, size, 0x11);
  unknownd8 = &unknowna0;
  unknownc8 = 0;
  unknowncc = size - controlSize;
  unknownd0 = controlSize;
  setCallback();
  unknowne8 = true;
}

void CGLibCmdBuffer::setup(u32 offset, u32 size, CGLibMemPool &memPool, u32 controlSize) {
  release();
  nvnCommandBufferInitialize(&unknown00, &CGLibManager::get()->unknown00);
  unknownd8 = &memPool;
  unknownc8 = offset;
  unknowncc = size - controlSize;
  unknownd0 = controlSize;
  setCallback();
  unknowne8 = true;
}

void CGLibCmdBuffer::begin() {
  nvnCommandBufferAddCommandMemory(&unknown00, unknownd8->m_memoryPool, unknownc8 + unknownd0, unknowncc);
  nvnCommandBufferAddControlMemory(&unknown00, static_cast<u8 *>(unknownd8->unknown18) + unknownc8, unknownd0);
  nvnCommandBufferBeginRecording(&unknown00);
  unknowne0 = 0;
  unknowne4 = 0;
}

void CGLibCmdBuffer::beginResetOff() {
  nvnCommandBufferBeginRecording(&unknown00);
  unknowne0 = 0;
  unknowne4 = 0;
}

void CGLibCmdBuffer::end() {
  unknownc0 = nvnCommandBufferEndRecording(&unknown00);
  unknowne0 = nvnCommandBufferGetCommandMemoryUsed(&unknown00);
  unknowne4 = nvnCommandBufferGetControlMemoryUsed(&unknown00);
}

void CGLibCmdBuffer::call() {
  if ((unknowne0 | unknowne4) != 0) {
    nvnCommandBufferCallCommands(&context::CGLibSystemContext::get()->unknown08->unknown00, 1, &unknownc0);
  }
}

namespace {

void unknown003(NVNcommandBuffer *cmdBuf, NVNcommandBufferMemoryEvent event, size_t minSize, void *callbackData) {
  switch (event) {
  case NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY:
  case NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY:
    break;
  default:
    nn::detail::UnexpectedDefaultImpl("", "", 0);
  }
}

} // namespace

} // namespace grlib

#include "ptlib/renderer/screen_render_manager.h"

#include <new>

#include "grlib/cglib_ctl_vertex.h"
#include "mm/mm_std_base.h"
#include "ptlib/particle_stack_allocater.h"
#include "ptlib/particle_system.h"
#include "types.h"

namespace ptlib {
namespace screen {

namespace {
ScreenRenderManager *unknown001;
f32 unknown002[20] = {-1.0f, -1.0f, 0.5f, 0.0f, 1.0f, 1.0f, -1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.0f, -1.0f, 1.0f, 0.5f, 0.0f, 0.0f};
const u16 unknown003[4] = {0, 1, 2, 3};
} // namespace

void ScreenRenderManager::init() {
#line 98
  MM_ASSERT(!getPtr());
  StaticAllocObj *allocator = StaticAllocObj::create(0x2f0, __FILE__, 102);
  unknown001 = static_cast<ScreenRenderManager *>(allocator->sysAlloc(sizeof(ScreenRenderManager), 0x10, nullptr, 0));
  new (unknown001) ScreenRenderManager();
  if (getPtr() != nullptr) {
    getPtr()->InitSub(allocator);
  }
}

ScreenRenderManager *&ScreenRenderManager::getPtr() { return unknown001; }

void ScreenRenderManager::InitSub(StaticAllocObj *allocator) {
  unknown0e0 = allocator;
  InitVertex();
  InitTexture();
  InitFetchVertex();
  efAstMsg("m_uAllocSizeUse < m_uAllocSize", "memory empty");
}

void ScreenRenderManager::term() {
#line 114
  MM_ASSERT(getPtr());
  getPtr()->ReleaseSub();
  getPtr()->~ScreenRenderManager();
  StaticAllocObj::destroy(getPtr()->unknown0e0);
  unknown001 = nullptr;
}

void ScreenRenderManager::ReleaseSub() {
  unknownd0.release();
  unknown80.release();
  unknowna8.release();
}

ScreenRenderManager *ScreenRenderManager::get() {
#line 133
  MM_ASSERT(getPtr());
  return getPtr();
}

bool ScreenRenderManager::isValid() { return getPtr() != nullptr; }

void ScreenRenderManager::InitVertex() {
  unknown80.createCopyVertexBuff(unknown002, 0x50, 0x14);
  unknowna8.createCopyIndexBuff(unknown003, 4, GRL_PRIMITIVE_QUADS, GRL_INDEX_FORMAT_U16);
}

void ScreenRenderManager::InitTexture() {
  unknown00[0].initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_LINEAR);
  unknown00[0].updateData();
  unknown00[2].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_NEAREST);
  unknown00[2].updateData();
  unknown00[3].initSampler(GRL_TEX_CLAMP_CLAMP, GRL_TEX_MAG_FILTER_LINEAR);
  unknown00[3].updateData();
  unknown00[1].initSampler(GRL_TEX_CLAMP_REPEAT, GRL_TEX_MAG_FILTER_LINEAR);
  unknown00[1].setClamp(GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_REPEAT, GRL_TEX_CLAMP_REPEAT);
  unknown00[1].updateData();
}

void ScreenRenderManager::InitFetchVertex() {
  void *memory = unknown0e0->sysAlloc(0x100, 0x10, nullptr, 0);
  grlib::CGLibVtxAttr attributes[2];
  attributes[0] = {GRL_VTX_FORMAT_RGB32F, 0, 0, 0};
  attributes[1] = {GRL_VTX_FORMAT_RG32F, 1, 0xc, 0};
  unknownd0.createMemFetchObj(memory, attributes, 2);
}

} // namespace screen
} // namespace ptlib

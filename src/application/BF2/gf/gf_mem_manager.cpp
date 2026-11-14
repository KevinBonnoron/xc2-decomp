#include "gf/gf_mem_manager.h"

#include "gf/asset/gf_slot_mapping.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "ml/dev_graph.h"
#include "ml/ml_mem.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace gf {

GfAllocatorManager GfMemManager::s_allocator;
mtl::ALLOC_HANDLE GfMemManager::s_hMemProg;
mtl::ALLOC_HANDLE GfMemManager::s_hMemInitial;
mtl::ALLOC_HANDLE GfMemManager::s_hMemScript;
mtl::ALLOC_HANDLE GfMemManager::s_hMemAsset;
mtl::ALLOC_HANDLE GfMemManager::s_hMemBdat;
mtl::ALLOC_HANDLE GfMemManager::s_hMemFontRsc;
mtl::ALLOC_HANDLE GfMemManager::s_hMemMenu;
mtl::ALLOC_HANDLE GfMemManager::s_hMemAnimation;
mtl::ALLOC_HANDLE GfMemManager::s_hMemGimmick;
mtl::ALLOC_HANDLE GfMemManager::s_hMemGmkBdat;
mtl::ALLOC_HANDLE GfMemManager::s_hMemProgLarge;

GfMemManager::GfMemManager(const GfSetupParam &param) : unknown08(false) { initialize(param); }

void GfMemManager::initialize(const GfSetupParam &) {
  ml::MlMem::getProductMem();
  unknown08 = true;
}

GfMemManager::~GfMemManager() {}

void GfMemManager::buildCoreMemory(const GfSetupParam &param) {
  s_allocator.initialize(param);
  initializeCore(param);
}

void GfMemManager::initializeCore(const GfSetupParam &param) {
  mtl::ALLOC_HANDLE parent = param.unknown18;
  s_hMemProg = mtl::MemManager::create(parent, 0x2400000, "GfProg", false, mtl::ALLOCATOR_TYPE_UNKNOWN_1, 0x10);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_0, s_hMemProg);
  s_hMemInitial = mtl::MemManager::create(parent, 0xe00000, "GfInitial", false, mtl::ALLOCATOR_TYPE_UNKNOWN_1, 0x10);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_1, s_hMemInitial);
  s_hMemScript = mtl::MemManager::create(parent, 0x200000, "GfScript", false, mtl::ALLOCATOR_TYPE_UNKNOWN_2, 0x1000);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_2, s_hMemScript);
  s_hMemBdat = mtl::MemManager::create(parent, 0x100000, "GfBdat", false, mtl::ALLOCATOR_TYPE_UNKNOWN_2, 0x1000);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_4, s_hMemBdat);
  s_hMemFontRsc = mtl::MemManager::create(parent, 0x1e00000, "GfFontRsc", false, mtl::ALLOCATOR_TYPE_UNKNOWN_2, 0x1000);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_5, s_hMemFontRsc);
  s_hMemMenu = mtl::MemManager::create(parent, 0x5000000, "GfMenu", false, mtl::ALLOCATOR_TYPE_UNKNOWN_2, 0x1000);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_6, s_hMemMenu);
  s_hMemAnimation = mtl::MemManager::create(parent, 0xe00000, "GfAnim", false, mtl::ALLOCATOR_TYPE_UNKNOWN_1, 0x10);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_7, s_hMemAnimation);
  s_hMemGimmick = mtl::MemManager::create(parent, 0x400000, "GfGmk", false, mtl::ALLOCATOR_TYPE_UNKNOWN_1, 0x10);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_8, s_hMemGimmick);
  s_hMemGmkBdat = mtl::MemManager::create(parent, 0x200000, "GfGmkBdat", false, mtl::ALLOCATOR_TYPE_UNKNOWN_1, 0x10);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_9, s_hMemGmkBdat);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_10, ml::MlMem::getDebugMem());
  s_hMemAsset = mtl::MemManager::create(parent, GfSlotMapping::getAllSize(), "AssetMain", false, mtl::ALLOCATOR_TYPE_UNKNOWN_2, 0x1000);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_3, s_hMemAsset);
  ml::DevGraph::setMemPoolMemHandle(s_hMemAsset);
  s_hMemProgLarge = mtl::MemManager::create(parent, 0x4000, "ProgLarge", false, mtl::ALLOCATOR_TYPE_UNKNOWN_2, 0x1000);
  s_allocator.buildAllocator(ALLOCATOR_UNKNOWN_11, s_hMemProgLarge);
}

void GfMemManager::destroyCoreMemory() {
  finalizeCore();
  s_allocator.finalize();
}

void GfMemManager::finalizeCore() {
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_9, s_hMemGmkBdat);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_8, s_hMemGimmick);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_7, s_hMemAnimation);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_6, s_hMemMenu);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_5, s_hMemFontRsc);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_4, s_hMemBdat);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_3, s_hMemAsset);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_2, s_hMemScript);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_10, ml::MlMem::getDebugMem());
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_1, s_hMemInitial);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_0, s_hMemProg);
  s_allocator.destroyAllocator(ALLOCATOR_UNKNOWN_11, s_hMemProgLarge);
  if (s_hMemAsset.isValid()) {
    ml::DevGraph::releaseMemPoolMemHandle(s_hMemAsset);
  }
  if (s_hMemProgLarge.isValid()) {
    mtl::MemManager::erase(s_hMemProgLarge);
    s_hMemProgLarge = mtl::ALLOC_HANDLE();
  }
  if (s_hMemGmkBdat.isValid()) {
    mtl::MemManager::erase(s_hMemGmkBdat);
    s_hMemGmkBdat = mtl::ALLOC_HANDLE();
  }
  if (s_hMemGimmick.isValid()) {
    mtl::MemManager::erase(s_hMemGimmick);
    s_hMemGimmick = mtl::ALLOC_HANDLE();
  }
  if (s_hMemAnimation.isValid()) {
    mtl::MemManager::erase(s_hMemAnimation);
    s_hMemAnimation = mtl::ALLOC_HANDLE();
  }
  if (s_hMemMenu.isValid()) {
    mtl::MemManager::erase(s_hMemMenu);
    s_hMemMenu = mtl::ALLOC_HANDLE();
  }
  if (s_hMemFontRsc.isValid()) {
    mtl::MemManager::erase(s_hMemFontRsc);
    s_hMemFontRsc = mtl::ALLOC_HANDLE();
  }
  if (s_hMemBdat.isValid()) {
    mtl::MemManager::erase(s_hMemBdat);
    s_hMemBdat = mtl::ALLOC_HANDLE();
  }
  if (s_hMemAsset.isValid()) {
    mtl::MemManager::erase(s_hMemAsset);
    s_hMemAsset = mtl::ALLOC_HANDLE();
  }
  if (s_hMemScript.isValid()) {
    mtl::MemManager::erase(s_hMemScript);
    s_hMemScript = mtl::ALLOC_HANDLE();
  }
  if (s_hMemInitial.isValid()) {
    mtl::MemManager::erase(s_hMemInitial);
    s_hMemInitial = mtl::ALLOC_HANDLE();
  }
  if (s_hMemProg.isValid()) {
    mtl::MemManager::erase(s_hMemProg);
    s_hMemProg = mtl::ALLOC_HANDLE();
  }
}

void GfMemManager::build(const GfSetupParam &param) { new (GfAllocatorManager::getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMemManager(param); }

void GfMemManager::destroy() {
  GfMemManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfMemManager::finalize() { unknown08 = false; }

bool GfMemManager::isInitialized() {
  GfMemManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown08;
  }
  return false;
}

void GfMemManager::initializeGame(mtl::ALLOC_HANDLE) {}

void GfMemManager::finalizeGame() {}

mtl::ALLOC_HANDLE GfMemManager::getMemHandle(ALLOCATOR allocator) {
  switch (allocator) {
  case ALLOCATOR_UNKNOWN_0:
    return s_hMemProg;
  case ALLOCATOR_UNKNOWN_1:
    return s_hMemInitial;
  case ALLOCATOR_UNKNOWN_2:
    return s_hMemScript;
  case ALLOCATOR_UNKNOWN_3:
    return s_hMemAsset;
  case ALLOCATOR_UNKNOWN_4:
    return s_hMemBdat;
  case ALLOCATOR_UNKNOWN_5:
    return s_hMemFontRsc;
  case ALLOCATOR_UNKNOWN_6:
    return s_hMemMenu;
  case ALLOCATOR_UNKNOWN_7:
    return s_hMemAnimation;
  case ALLOCATOR_UNKNOWN_8:
    return s_hMemGimmick;
  case ALLOCATOR_UNKNOWN_9:
    return s_hMemGmkBdat;
  case ALLOCATOR_UNKNOWN_10:
    return ml::MlMem::getDebugMem();
  case ALLOCATOR_UNKNOWN_11:
    return s_hMemProgLarge;
  }
  return mtl::ALLOC_HANDLE();
}

} // namespace gf

void *operator new(size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment) { return allocator->allocate(size, alignment); }

void *operator new[](size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment) { return allocator->allocate(size, alignment); }

template mm::mtl::PtrSingleton<gf::GfMemManager>::~PtrSingleton();

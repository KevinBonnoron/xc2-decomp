#include "gf/asset/gf_asset_resource.h"

#include "dr/dr_stm_read_obj.h"
#include "framework/resource/common_resource.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/allocator.h"
#include "mtl/mem_manager.h"
#include "scn/scn_obj_acc.h"

namespace gf {

namespace {

constexpr u32 unknown002 = 0x19283746; // Inferred role: initial sample word; original name unknown.

} // namespace

GfAssetResource::GfAssetResource()
    : unknown0c(unknown001_0), unknown10(0), unknown18(nullptr), unknown20(nullptr), unknown28(), unknown30(nullptr), unknown38(0), unknownc8(nullptr), unknownd0(unknown002), unknownd4(unknown002) {}

GfAssetResource::~GfAssetResource() { destroy(); }

void GfAssetResource::destroy() {
  destroyResource();
  unknown3c = "";
  unknown20 = nullptr;
  unknown38 = 0;
  unknown0c = unknown001_0;
}

inline void GfAssetResource::unknown003() {
  destroyStreamObject();
  if (unknown30 != nullptr) {
    mtl::MemManager::deallocate(unknown30, 0, false);
    unknown30 = nullptr;
  }
  mm::mtl::safeRelease(unknown18);
}

void GfAssetResource::destroyResource() {
  if (unknown0c == unknown001_3) {
    unknown30 = nullptr;
  }
  unknown003();
}

void GfAssetResource::reloadPre() {
  if (unknown0c != unknown001_3) {
    unknown003();
  }
}

#line 71
GfAssetResource *GfAssetResource::create(const char *assetName, const char *name, mtl::ALLOC_HANDLE handle, int priority) {
  GfAssetResource *resource = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfAssetResource();
  resource->setup(assetName, name, handle, priority);
  return resource;
}

void GfAssetResource::setup(const char *assetName, const char *name, mtl::ALLOC_HANDLE handle, int priority) {
  unknown18 = fw::CommonResource::request(handle, name, priority, false);
  unknown3c = name;
  unknownc0 = assetName;
  unknown10 = priority;
  unknown28 = handle;
  unknown0c = unknown001_1;
}

#line 99
GfAssetResource *GfAssetResource::create(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, void *data, u32 size) {
  GfAssetResource *resource = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfAssetResource();
  resource->setup(assetName, name, allocator, data, size);
  return resource;
}

void GfAssetResource::setup(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, void *data, u32 size) {
  unknown30 = allocator->allocate(size, 0x2000);
  __builtin_memcpy(unknown30, data, size);
  unknown38 = size;
  unknown3c = name;
  unknownc0 = assetName;
  unknown0c = unknown001_2;
}

void GfAssetResource::importSample() {
  unknownd0 = *static_cast<u32 *>(unknown30);
  unknownd4 = *reinterpret_cast<u32 *>(static_cast<u8 *>(unknown30) + unknown38 - 4);
}

void GfAssetResource::checkMemoryForDebug() {}

#line 147
GfAssetResource *GfAssetResource::create(const char *assetName, const char *name, void *data, u32 size) {
  GfAssetResource *resource = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfAssetResource();
  resource->setup(assetName, name, data, size);
  return resource;
}

void GfAssetResource::setup(const char *assetName, const char *name, void *data, u32 size) {
  unknown30 = data;
  unknown38 = size;
  unknown3c = name;
  unknown0c = unknown001_3;
  unknownc0 = assetName;
  importSample();
}

#line 172
GfAssetResource *GfAssetResource::create(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, int priority) {
  GfAssetResource *resource = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfAssetResource();
  resource->setup(assetName, name, allocator, priority);
  return resource;
}

void GfAssetResource::setup(const char *assetName, const char *name, mm::mtl::IAllocator *allocator, int priority) {
  unknown18 = fw::CommonResource::request(allocator, name, priority, false);
  unknown3c = name;
  unknownc0 = assetName;
  unknown0c = unknown001_1;
  unknown20 = allocator;
  unknown10 = priority;
}

void *GfAssetResource::getAssetData() const {
  switch (unknown0c) {
  case unknown001_2:
  case unknown001_3:
    return unknown30;
  case unknown001_1:
    return unknown18->getAssetData();
  default:
    return nullptr;
  }
}

u32 GfAssetResource::getAssetSize() const {
  switch (unknown0c) {
  case unknown001_2:
  case unknown001_3:
    return unknown38;
  case unknown001_1:
    return unknown18->getAssetSize();
  default:
    return 0;
  }
}

const char *GfAssetResource::getAssetName() const { return unknown3c.c_str(); }

u64 GfAssetResource::getAssetTimeStamp() const {
  if (unknown0c == unknown001_1) {
    return unknown18->getAssetTimeStamp();
  }
  return 0;
}

void GfAssetResource::destroyStreamObject() {
  if (unknownc8 != nullptr) {
    unknownc8->release();
    unknownc8 = nullptr;
  }
}

void GfAssetResource::setupStreamObject() {
  if (unknownc8 == nullptr) {
    unknownc8 = ml::ScnObjAccStmReadObj::create(unknown3c.c_str());
  }
}

void GfAssetResource::createStreamObject() { unknownc8 = ml::ScnObjAccStmReadObj::create(unknown3c.c_str()); }

} // namespace gf

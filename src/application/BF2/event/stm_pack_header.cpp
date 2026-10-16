#include "event/stm_pack_header.h"

#include "event/memory_manager.h"
#include "event/pack_header.h"
#include "fw/fw_render_resource.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

StmPackHeader::StmPackHeader() : mResource(nullptr) {}

StmPackHeader::~StmPackHeader() { destroy(); }

void StmPackHeader::destroy() {
  if (mResource != nullptr) {
    mResource->release();
    mResource = nullptr;
  }
}

void StmPackHeader::create(mtl::ALLOC_HANDLE handle, const char *path) {
  destroy();
  mResource = fw::RenderResource::request(mm::mtl::Singleton<MemoryManager>::getPtr()->getResHandle(), path, 0);
}

const char *StmPackHeader::getPath(size_t index) const {
  if (mResource->getAssetData() == nullptr) {
    return "";
  }
  return getHeader()->getPath(index);
}

u32 StmPackHeader::getPrio(size_t index) const {
  if (mResource->getAssetData() == nullptr) {
    return 0;
  }
  return getHeader()->getPrio(index);
}

size_t StmPackHeader::getDataOfs(size_t index) const {
  if (mResource->getAssetData() == nullptr) {
    return 0;
  }
  return getHeader()->getDataOfs(index);
}

size_t StmPackHeader::getDataSize(size_t index) const {
  if (mResource->getAssetData() == nullptr) {
    return 0;
  }
  return getHeader()->getDataSize(index);
}

size_t StmPackHeader::getCount() const {
  if (mResource->getAssetData() == nullptr) {
    return 0;
  }
  return getHeader()->getCount();
}

bool StmPackHeader::isLoading() const { return !mResource->valid(); }

bool StmPackHeader::isFailure() const { return false; }

} // namespace event

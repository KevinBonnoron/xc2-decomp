#include "gf/asset/gf_asset_pack.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_file_size_pool.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace gf {

GfAssetType GfAssetPack::getAssetType() const { return m_assetType.unknown00; }

const char *GfAssetPack::getAssetName() const { return m_assetType.unknown08.c_str(); }

void GfAssetPack::lockEnterRersource() {
  unknown2b8 = true;
  m_assetType.unknown108 = true;
}

bool GfAssetPack::setForceDestroy() {
  if (unknown238) {
    return false;
  }
  unknown238 = true;
  return true;
}

void GfAssetPack::setTimeout() { unknown23b = true; }

void GfAssetPack::updateCacheCount() {
  if (unknown254 == 0) {
    if (unknown27c < 99) {
      unknown27c++;
    }
  } else if (unknown27c != 0) {
    unknown27c = 0;
  }
}

void GfAssetPack::updateReloadCount() {
  u32 userCount = unknown254;
  if (getRefCount() - userCount == 1) {
    if (unknown280 < 99) {
      unknown280++;
    }
  } else if (unknown280 != 0) {
    unknown280 = 0;
  }
}

bool GfAssetPack::isEnableReload() const { return unknown280 > 9; }

void GfAssetPack::releaseSlotHandle() {
  if (unknown230 != reinterpret_cast<GF_SLOT_HANDLE *>(-1)) {
    GfAssetManager::releaseSlotHandle(unknown230);
    unknown230 = reinterpret_cast<GF_SLOT_HANDLE *>(-1);
  }
}

bool GfAssetPack::isPreSizeSizeValid() const {
  for (GfAssetFiles::AssetFile *const *it = m_assetType.unknown50.begin(); it != m_assetType.unknown50.end(); ++it) {
    if ((*it)->unknown94 == -2) {
      return false;
    }
  }
  return !m_assetType.unknown50.empty();
}

bool GfAssetPack::isExistSameAsset(const GfAssetPack &other) const { return m_assetType.isExistSameAsset(other.m_assetType); }

void GfAssetFiles::replaceAssetType(GfAssetType type) {
  if (type != ASSET_TYPE_BASE) {
    unknown00 = type;
  }
}

GfAssetFiles::~GfAssetFiles() {
  for (AssetFile **it = unknown50.begin(); it != unknown50.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }
}

void GfAssetFiles::addResourceWithLockAsset(GfFileIdx index, const char *name) {
  unknown108 = false;
  addResource(index, name);
  unknown108 = true;
}

void GfAssetFiles::destroyFileSizeCache() {
  GfFileSizePool *pool = GfFileSizePool::get();
  if (pool == nullptr) {
    return;
  }
  AssetFile **end = unknown50.end();
  for (AssetFile **it = unknown50.begin(); it != end; ++it) {
    AssetFile *file = *it;
    if (file->unknown94 != -2) {
      pool->recalcFileSizeCache(file->unknown08, file->unknown10.c_str());
      file->unknown94 = -2;
      file->unknown08 = pool->requestFileSize(file->unknown10.c_str());
    }
  }
}

void GfAssetFiles::applyPreFileSize() {
  GfFileSizePool *pool = GfFileSizePool::get();
  if (pool == nullptr) {
    return;
  }
  AssetFile **end = unknown50.end();
  for (AssetFile **it = unknown50.begin(); it != end; ++it) {
    if ((*it)->unknown94 == -2) {
      pool->getFileSize((*it)->unknown94, (*it)->unknown08);
    }
  }
}

bool GfAssetFiles::isPreSizeSizeValid() const {
  for (AssetFile *const *it = unknown50.begin(); it != unknown50.end(); ++it) {
    if ((*it)->unknown94 == -2) {
      return false;
    }
  }
  return !unknown50.empty();
}

s64 GfAssetFiles::calcAllFileSize() const {
  s64 total = 0;
  for (AssetFile *const *it = unknown50.begin(); it != unknown50.end(); ++it) {
    s64 size = (*it)->unknown94;
    if (size > 0) {
      if ((size & 0x1fff) != 0) {
        size = size + 0x2000 - (size & 0x1fff);
      }
      total += size;
    }
  }
  return total;
}

s64 GfAssetFiles::calcFileSize(GfFileIdx index) const {
  for (AssetFile *const *it = unknown50.begin(); it != unknown50.end(); ++it) {
    if ((*it)->unknown00 == index && (*it)->unknown94 > 0) {
      return (*it)->unknown94;
    }
  }
  return 0;
}

void GfAssetPack::dispAssetLogForDebug() {}

void GfAssetPack::setLoadComplete() {}

} // namespace gf

template mm::mtl::FixedList<gf::GfAssetPack *, 1024>::iterator mm::mtl::FixedList<gf::GfAssetPack *, 1024>::erase(mm::mtl::FixedList<gf::GfAssetPack *, 1024>::iterator);

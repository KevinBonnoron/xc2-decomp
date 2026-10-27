#include "gf/asset/gf_asset_pack.h"

#include "gf/asset/gf_asset_manager.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace gf {

GfAssetType GfAssetPack::getAssetType() const { return m_assetType.unknown00; }

const char *GfAssetPack::getAssetName() const { return m_assetType.unknown08.c_str(); }

void GfAssetPack::lockEnterRersource() {
  unknown2b8 = true;
  unknown228 = true;
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
  for (GfAssetFiles::AssetFile *const *it = unknown170.begin(); it != unknown170.end(); ++it) {
    if ((*it)->unknown94 == -2) {
      return false;
    }
  }
  return !unknown170.empty();
}

bool GfAssetPack::isExistSameAsset(const GfAssetPack &other) const { return m_assetType.isExistSameAsset(other.m_assetType); }

void GfAssetFiles::replaceAssetType(GfAssetType type) {
  if (type != ASSET_TYPE_BASE) {
    unknown00 = type;
  }
}

void GfAssetPack::dispAssetLogForDebug() {}

void GfAssetPack::setLoadComplete() {}

} // namespace gf

template mm::mtl::FixedList<gf::GfAssetPack *, 1024>::iterator mm::mtl::FixedList<gf::GfAssetPack *, 1024>::erase(mm::mtl::FixedList<gf::GfAssetPack *, 1024>::iterator);

#include "gf/asset/gf_asset_pack_info.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack.h"
#include "gf/asset/gf_asset_util.h"
#include "gf/asset/gf_slot.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/reference_object.h"

namespace gf {

class GfExtendResource : public mm::mtl::ReferenceObject {};

AssetPackInfo::~AssetPackInfo() {
  GfAssetPack **end = unknown10.end();
  for (GfAssetPack **it = unknown10.begin(); it != end; ++it) {
    GfAssetPack *pack = *it;
    pack->unknown254--;
    *it = nullptr;
    GfAssetManager::callEventAssetPack(pack);
    mm::mtl::safeRelease(pack);
  }
}

void AssetPackInfo::setLoadComplete() { unknown307 = false; }

void AssetPackInfo::setupLoadStart() { unknown334 = 0; }

void AssetPackInfo::replaceAssetPack(GfAssetType from, GfAssetType to, GfAssetPack *pack) { unknown308 = to; }

void AssetPackInfo::setExtendResource(u32 index, GfExtendResource *resource) { unknown2e0[index] = resource; }

void AssetPackInfo::releaseExtResource() {
  for (u32 i = 0; i < 4; i++) {
    mm::mtl::safeRelease(unknown2e0[i]);
  }
}

void AssetPackInfo::setNoCache(bool noCache) {
  for (GfAssetPack **it = unknown10.begin(); it != unknown10.end(); ++it) {
    (*it)->unknown239 = noCache;
  }
}

bool AssetPackInfo::isUseSameAsset(const AssetPackInfo *other) const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (*it != nullptr) {
      for (GfAssetPack *const *otherIt = other->unknown10.begin(); otherIt != other->unknown10.end(); ++otherIt) {
        if (*otherIt != nullptr && *it == *otherIt) {
          return true;
        }
      }
    }
  }
  return false;
}

bool AssetPackInfo::isFullResource() const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if ((*it)->unknown23a) {
      return true;
    }
  }
  return false;
}

bool AssetPackInfo::isExistAssetPack(const GfAssetPack *pack) const {
  if (pack == nullptr) {
    return false;
  }
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if (*it == pack) {
      return true;
    }
  }
  return false;
}

void AssetPackInfo::setDestroy() {
  if (unknown304) {
    return;
  }
  unknown304 = true;
  GfAssetUtil::addDestroyObject(unknown08, true);
}

GfAssetPack *AssetPackInfo::getAssetPack(GF_SLOT_HANDLE *handle) const {
  for (GfAssetPack *const *it = unknown10.begin(); it != unknown10.end(); ++it) {
    if ((*it)->unknown230 == handle) {
      return *it;
    }
  }
  return nullptr;
}

void AssetPackInfo::setAssetPack(GfAssetType type, GfAssetPack *pack) {
  if (mm::mtl::find(unknown10.begin(), unknown10.end(), pack) != unknown10.end()) {
    return;
  }
  pack->addRef();
  unknown10.push_back(pack);
  pack->unknown254++;
  if (unknown308 == ASSET_TYPE_BASE) {
    unknown308 = type;
  }
}

void AssetPackInfo::setModelName(const char *name) { unknown30c = util::getFilePtrFromPath(name); }

void AssetPackInfo::setMotionName(const char *name) { unknown320 = util::getFilePtrFromPath(name); }

bool AssetPackInfo::getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots) const {
  GfAssetPack *const *end = unknown10.end();
  for (GfAssetPack *const *it = unknown10.begin(); it != end; ++it) {
    GF_SLOT_HANDLE *slot = (*it)->unknown230;
    if (slot != INVALID_SLOT_HANDLE) {
      slots.push_back(slot);
    }
  }
  return !slots.empty();
}

} // namespace gf

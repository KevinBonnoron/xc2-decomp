#include "gf/asset/gf_asset_multi_bind.h"

#include "gf/object/gf_obj_util.h"
#include "mm_mtl/algorithm.h"

namespace gf {

GfAssetMultiBind::GfAssetMultiBind(u32 uniqueId, bool flag) : unknown488(uniqueId), unknown48c(0), unknown490(0), unknown494(flag) {}

bool GfAssetMultiBind::isValid() const { return unknown08.size() == unknown48c && unknown248.size() == unknown08.size(); }

bool GfAssetMultiBind::bind(GF_OBJ_HANDLE *handle) {
  if (mm::mtl::find(unknown08.begin(), unknown08.end(), handle) == unknown08.end()) {
    unknown08.push_back(handle);
  }
  return true;
}

bool GfAssetMultiBind::unbind(GF_OBJ_HANDLE *handle) {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 32>::iterator it = mm::mtl::find(unknown08.begin(), unknown08.end(), handle);
  if (unknown08.end() != it) {
    unknown08.erase(it);
    return true;
  }
  return false;
}

bool GfAssetMultiBind::loadedAsset(GF_OBJ_HANDLE *handle) {
  if (unknown08.end() == mm::mtl::find(unknown08.begin(), unknown08.end(), handle)) {
    return false;
  }
  if (mm::mtl::find(unknown248.begin(), unknown248.end(), handle) == unknown248.end()) {
    unknown248.push_back(handle);
    unknown490++;
  }
  return true;
}

bool GfAssetMultiBind::unloadedAsset(GF_OBJ_HANDLE *handle) {
  if (unknown08.end() == mm::mtl::find(unknown08.begin(), unknown08.end(), handle)) {
    return false;
  }
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 32>::iterator it = mm::mtl::find(unknown248.begin(), unknown248.end(), handle);
  if (unknown248.end() != it) {
    unknown248.erase(it);
    unknown490--;
  }
  return true;
}

void GfAssetMultiBind::checkObject() {
  mm::mtl::FixedList<GF_OBJ_HANDLE *, 32>::iterator it = unknown08.begin();
  while (it != unknown08.end()) {
    if (GfObjUtil::isValid(*it)) {
      ++it;
    } else {
      it = unknown08.erase(it);
    }
  }
}

} // namespace gf

template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::iterator);

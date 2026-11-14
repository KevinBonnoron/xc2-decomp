// Original file name from the game string C:/Monolithsoft/BF2/prog/application/BF2/gf/menu/gf_menu_map_info.cpp.
#include "gf/menu/gf_menu_map_info.h"

#include <string.h>

#include "framework/resource/common_resource.h"
#include "mm_math/mm_pnt.h"

namespace gf {

GfMenuMapInfo::~GfMenuMapInfo() {}

void GfMenuMapInfo::destroy() {
  GfMenuMapInfo *info = get();
  info->finalize();
  delete info;
}

bool GfMenuMapInfo::isInitialized() {
  if (get() != nullptr && get()->unknown08) {
    return !isLoading();
  }

  return false;
}

bool GfMenuMapInfo::isLoading() {
  GfMenuMapInfo *info = get();
  if (info != nullptr) {
    if (info->unknown10.capacity() != 0 && info->unknown10.size() != 0) {
      for (u32 i = 0; i < info->unknown10.size(); i++) {
        if (!info->unknown10[i]->valid()) {
          return true;
        }
      }
    }
    if (info->unknown38.capacity() != 0 && info->unknown38.size() != 0) {
      for (u32 i = 0; i < info->unknown38.size(); i++) {
        if (!info->unknown38[i].unknown00->valid()) {
          return true;
        }
      }
    }
  }

  return false;
}

u32 GfMenuMapInfo::getMapAreaCount(int index) {
  GfMenuMapInfo *info = get();
  if (info == nullptr) {
    return -1;
  }
  if (index < info->unknown10.size() && info->unknown10[index]->valid()) {
    return static_cast<const unknown001 *>(info->unknown10[index]->getAssetData())->unknown04;
  }

  return 0;
}

bool GfMenuMapInfo::getMapArea(int index, u32 areaIndex, MapAreaInfo &area) {
  GfMenuMapInfo *info = get();
  if (info != nullptr && index < info->unknown10.size() && info->unknown10[index]->valid()) {
    const unknown001 *data = static_cast<const unknown001 *>(info->unknown10[index]->getAssetData());
    if (areaIndex < data->unknown04) {
      area = data->unknown08[areaIndex];
      return true;
    }
  }

  return false;
}

const GfMenuMapInfo::MapAreaInfo *GfMenuMapInfo::getMapArea(int index, u32 areaIndex) {
  GfMenuMapInfo *info = get();
  if (info != nullptr && index < info->unknown10.size() && info->unknown10[index]->valid()) {
    const unknown001 *data = static_cast<const unknown001 *>(info->unknown10[index]->getAssetData());
    return areaIndex < data->unknown04 ? &data->unknown08[areaIndex] : nullptr;
  }

  return nullptr;
}

bool GfMenuMapInfo::getMapAreaFromName(int index, const char *name, MapAreaInfo &area) {
  GfMenuMapInfo *info = get();
  if (info != nullptr && index < info->unknown10.size() && info->unknown10[index]->valid()) {
    const unknown001 *data = static_cast<const unknown001 *>(info->unknown10[index]->getAssetData());
    for (u32 i = 0; i < data->unknown04; i++) {
      if (strcmp(data->unknown08[i].unknown00, name) == 0) {
        area = data->unknown08[i];
        return true;
      }
    }
  }

  return false;
}

const GfMenuMapInfo::MapAreaInfo *GfMenuMapInfo::getMapAreaFromName(int index, const char *name) {
  GfMenuMapInfo *info = get();
  if (info != nullptr && index < info->unknown10.size() && info->unknown10[index]->valid()) {
    const unknown001 *data = static_cast<const unknown001 *>(info->unknown10[index]->getAssetData());
    for (u32 i = 0; i < data->unknown04; i++) {
      if (strcmp(data->unknown08[i].unknown00, name) == 0) {
        return &data->unknown08[i];
      }
    }
  }

  return nullptr;
}

bool GfMenuMapInfo::isValid() {
  GfMenuMapInfo *info = get();
  if (info == nullptr || isLoading()) {
    return false;
  }

  return info->unknown60 != -1 && info->unknown64 != -1;
}

bool GfMenuMapInfo::getMapSegImageOffs(mm::Pnt<s16> &offset) {
  GfMenuMapInfo *info = get();
  if (isValid()) {
    offset.x = info->unknown74;
    offset.y = info->unknown78;
    return true;
  }

  return false;
}

bool GfMenuMapInfo::getMiniIconList(u32 type, const mm::mtl::Vector<MiniIcon> **list) {
  GfMenuMapInfo *info = get();
  if (type < 5 && info != nullptr) {
    *list = &info->unknown80[type];
    return true;
  }
  return false;
}

bool GfMenuMapInfo::getMapRatio(f32 &x, f32 &y) {
  GfMenuMapInfo *info = get();
  if (info != nullptr) {
    x = info->unknown148;
    y = info->unknown14c;
    return true;
  }

  return false;
}

bool GfMenuMapInfo::getMapSize(s16 &left, s16 &top, s16 &right, s16 &bottom) {
  GfMenuMapInfo *info = get();
  if (info != nullptr) {
    left = info->unknown150;
    top = info->unknown152;
    right = info->unknown154;
    bottom = info->unknown156;
    return true;
  }

  return false;
}

bool GfMenuMapInfo::getCurMapAreaInfo(MapAreaInfo &area) {
  GfMenuMapInfo *info = get();
  if (info != nullptr) {
    getMapArea(info->unknown60, info->unknown64, area);
    return true;
  }

  return false;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfMenuMapInfo>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfMenuMapInfo::MiniIcon>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfMenuMapInfo::MiniIcon>::push_back(const gf::GfMenuMapInfo::MiniIcon &);
template void mm::mtl::Vector<gf::GfMenuMapInfo::SegInfo>::expand(size_t, size_t);

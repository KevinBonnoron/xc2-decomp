#include "gf/game/gf_game_search_obj.h"

#include <new>

#include "gf/gf_allocator.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

namespace gf {

GfGameSearchObj::GfGameSearchObj(const GfSetupParam &) : unknown90978(0), unknown9097c(true) {}

void GfGameSearchObj::initialize(const GfSetupParam &) { unknown9097c = true; }

GfGameSearchObj::~GfGameSearchObj() {}

void GfGameSearchObj::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameSearchObj(param); }

void GfGameSearchObj::destroy() {
  GfGameSearchObj *search = get();
  search->finalize();
  delete search;
}

void GfGameSearchObj::finalize() {
  for (u32 index = 0; index < 64; index++) {
    if (unknown08.unknown010(index)) {
      destroyList(unknown08.unknown007[index].unknown78);
      if (unknown08.unknown007[index].unknown78 != nullptr) {
        delete unknown08.unknown007[index].unknown78;
        unknown08.unknown007[index].unknown78 = nullptr;
      }
    }
  }
  unknown2438.clear();
  unknown9097c = false;
}

void GfGameSearchObj::destroyList(mm::mtl::FixedList<GfSearchInfo *, 256> *list) {
  if (list != nullptr) {
    for (mm::mtl::FixedList<GfSearchInfo *, 256>::iterator it = list->begin(); it != list->end(); ++it) {
      unknown2898.unknown004(*it);
    }
    list->clear();
  }
}

bool GfGameSearchObj::isInitialized() {
  GfGameSearchObj *search = get();
  if (search != nullptr) {
    return search->unknown9097c;
  }
  return false;
}

GfGameSearchObj::GFSEARCH_INFO *GfGameSearchObj::getInfo(GF_SEARCH_OBJ *searchObj) {
  GfGameSearchObj *search = get();
  if (searchObj != unknown012 && search != nullptr) {
    return &search->unknown08.unknown007[reinterpret_cast<u64>(searchObj) & 0x3f];
  }
  return nullptr;
}

mm::mtl::FixedList<GfSearchInfo *, 256> *GfGameSearchObj::getObj(GF_SEARCH_OBJ *searchObj) {
  GFSEARCH_INFO *infos = get()->unknown08.unknown007;
  return infos[reinterpret_cast<u64>(searchObj) & 0x3f].unknown78;
}

void GfGameSearchObj::setEnable(GF_SEARCH_OBJ *searchObj, bool isEnable) {
  GfGameSearchObj *search = get();
  if (searchObj != unknown012 && search != nullptr) {
    if (isEnable) {
      search->unknown08.unknown007[reinterpret_cast<u64>(searchObj) & 0x3f].unknown80 &= ~1;
    } else {
      search->unknown08.unknown007[reinterpret_cast<u64>(searchObj) & 0x3f].unknown80 |= 1;
    }
  }
}

bool GfGameSearchObj::isEnable(GF_SEARCH_OBJ *searchObj) {
  GfGameSearchObj *search = get();
  if (searchObj != unknown012 && search != nullptr) {
    return (search->unknown08.unknown007[reinterpret_cast<u64>(searchObj) & 0x3f].unknown80 & 1) == 0;
  }
  return false;
}

u64 GfGameSearchObj::createHandle(u32 index) {
  u32 serial = unknown90978;
  unknown90978 = serial + 1;
  if (serial >= 0x3ffffff) {
    serial++;
    unknown90978 = serial + 1;
  }
  return (index & 0x3f) | (serial << 6);
}

GF_SEARCH_OBJ *GfGameSearchObj::createObj(const GfSearchParam &param) {
  GfGameSearchObj *search = get();
  GF_SEARCH_OBJ *searchObj = unknown012;
  if (search != nullptr) {
    u32 index = 0;
    GFSEARCH_INFO *info = new (search->unknown08.unknown003(&index)) GFSEARCH_INFO;
    searchObj = reinterpret_cast<GF_SEARCH_OBJ *>(search->createHandle(index));
    info->unknown70 = searchObj;
    info->unknown00 = param;
    info->unknown78 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) mm::mtl::FixedList<GfSearchInfo *, 256>;
    search->unknown2438.push_back(searchObj);
  }
  return searchObj;
}

void GfGameSearchObj::destroyObj(GF_SEARCH_OBJ *searchObj) {
  GfGameSearchObj *search = get();
  if (search != nullptr) {
    u32 index = reinterpret_cast<u64>(searchObj) & 0x3f;
    GFSEARCH_INFO *info = &search->unknown08.unknown007[index];
    search->destroyList(info->unknown78);
    if (info->unknown78 != nullptr) {
      delete info->unknown78;
      info->unknown78 = nullptr;
    }
    info->~GFSEARCH_INFO();
    search->unknown08.unknown011(index);
    mm::mtl::FixedList<GF_SEARCH_OBJ *, 64>::iterator it = mm::mtl::find(search->unknown2438.begin(), search->unknown2438.end(), searchObj);
    if (it != search->unknown2438.end()) {
      search->unknown2438.erase(it);
    }
  }
}

void GfGameSearchObj::update(const fw::UpdateInfo &) {
  GfGameSearchObj *search = get();
  search->unknowne940.unknown001();
  for (mm::mtl::FixedList<GF_SEARCH_OBJ *, 64>::iterator it = search->unknown2438.begin(); it != search->unknown2438.end(); ++it) {
    search->updateObj(*it);
  }
}

} // namespace gf

template class ml::fixed_size_alloc_inside<gf::GfGameSearchObj::GFSEARCH_INFO, 64>;
template class ml::fixed_size_alloc_inside<gf::GfSearchInfo, 1024>;
template mm::mtl::PtrSingleton<gf::GfGameSearchObj>::~PtrSingleton();
template mm::mtl::FixedList<gf::GF_SEARCH_OBJ *, 64>::iterator mm::mtl::FixedList<gf::GF_SEARCH_OBJ *, 64>::erase(mm::mtl::FixedList<gf::GF_SEARCH_OBJ *, 64>::iterator);

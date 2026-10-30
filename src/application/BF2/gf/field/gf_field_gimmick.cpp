// Same order as in the game executable.
// clang-format off
#include "gf/field/gf_mob_slot_manager.cpp"
// clang-format on

#include "gf/field/gf_field_gimmick.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

#include "fw/fw_update_info.h"
#include "gf/asset/gf_slot.h"
#include "gf/data/gf_character_id.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gmk/gmk_anti_blade_area.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_blade.h"
#include "gmk/gmk_effect.h"
#include "gmk/gmk_event.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"
#include "ml/rand.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "mtl/alloc_handle.h"

namespace gf {

namespace {

// Inferred role: tells whether a blade is Homura or Hikari; original name unknown.
bool unknown002(u32 blade) { return blade == BLADE_HOMURA || blade == BLADE_HIKARI; }

} // namespace

// Inferred role: finds the blade gimmick showing a blade, or a free one of a blade size; the layout comes from
// GfFieldGimmick::gevBladeActivate and the vtable gf::GfGmkBladeTraverser.
class GfGmkBladeTraverser {
public:
  GfGmkBladeTraverser(u8 size, u32 blade) : unknown08(size), unknown0c(blade), unknown10(nullptr), unknown18(unknown002(blade)) {}

  virtual void onTraverse(const gmk::AGmkBase &gmk) {
    const gmk::GmkBlade &blade = static_cast<const gmk::GmkBlade &>(gmk);
    if (unknown0c != 0) {
      if (unknown18 ? unknown002(blade.unknown50) : blade.unknown50 == unknown0c) {
        unknown10 = &blade;
      }
    } else if (blade.getBdatInfo()->unknown00 == unknown08 && blade.unknown50 == 0) {
      unknown10 = &blade;
    }
  }

  u8 unknown08;                   // Inferred role: blade size; original member name unknown.
  u32 unknown0c;                  // Inferred role: blade; original member name unknown.
  const gmk::GmkBlade *unknown10; // Inferred role: found gimmick; original member name unknown.
  bool unknown18;                 // Inferred role: blade is Homura or Hikari; original member name unknown.
};

// Inferred role: reserve blades out of the village and not shown by a blade gimmick; the layout comes from its
// constructor and the vtable gf::GfUnpopBladeIds.
class GfUnpopBladeIds {
public:
  GfUnpopBladeIds() {
    GfDataBlade::getListReserver(unknown08);
    for (u16 *it = unknown08.begin(); it != unknown08.end(); ++it) {
      if (!GfGameUtil::isBladeInVillage(*it)) {
        unknown08.erase(it);
        --it;
      }
    }
    mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GMK_TYPE_BLADE, *this);
  }

  virtual void onTraverse(const gmk::AGmkBase &gmk) {
    const gmk::GmkBlade &blade = static_cast<const gmk::GmkBlade &>(gmk);
    if (blade.unknown50 != 0) {
      u16 *it = mm::mtl::find(unknown08.begin(), unknown08.end(), static_cast<u16>(blade.unknown50));
      if (it != unknown08.end()) {
        unknown08.erase(it);
      }
    }
  }

  mm::mtl::FixedVector<u16, 422> unknown08; // Inferred role: blades; original member name unknown.
};

namespace {

// Inferred role: finds the blade gimmick of a blade or a blade size; original name unknown.
const gmk::GmkBlade *unknown003(u8 size, u32 blade) {
  GfGmkBladeTraverser traverser(size, blade);
  mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GMK_TYPE_BLADE, traverser);
  return traverser.unknown10;
}

// Inferred role: makes a blade gimmick show a blade; original name unknown. The traversal only hands out const
// gimmicks: the blade a gimmick shows is changed through the gimmick it found.
void unknown004(const gmk::GmkBlade &gmk, u32 blade) {
  gmk::GmkBlade &bladeGmk = const_cast<gmk::GmkBlade &>(gmk);
  bool isChanged = bladeGmk.unknown50 != blade;
  bladeGmk.unknown50 = blade;
  bladeGmk.unknown54 = isChanged;
}

// Inferred role: chance to prefer a rare blade for a blade gimmick; original constant name unknown.
constexpr f32 unknown005 = 0.75f;

} // namespace

GfFieldGimmick::GfFieldGimmick(const GfSetupParam &param) : unknownf4a8(false), unknownf4c0(nullptr), unknownfe40(false), unknownfe41(true) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfFieldGimmick::initialize(const GfSetupParam &) {
  gmk::GmkManager::CreateInfo info;
  info.unknown00 = getAllocator(ALLOCATOR_UNKNOWN09)->getMemHandle();
  info.unknown04 = "bdat/common_gmk.bdat";
  info.unknown28 = "RSC_GmkSetList";
  info.unknown4c = 1;
  unknown20.create(info);
  unknownf4a8 = true;
}

void GfFieldGimmick::listenerGfObj(OBJEVT, GF_OBJ_HANDLE *, u32) {}

void GfFieldGimmick::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  switch (event) {
  case GEV_MAPJUMP_START:
    if (info.unknown0c) {
      unknownfe40 = true;
    }
    break;
  case GEV_MAPJUMP_DESTROY_FIELD:
    for (gmk::GmkSet **it = unknown20.unknownf358.begin(); it != unknown20.unknownf358.end(); ++it) {
      gmk::GmkEffectList *list = static_cast<gmk::GmkEffectList *>((*it)->getGmkList(gmk::GMK_TYPE_EFFECT));
      if (list == nullptr || !list->isValid()) {
        continue;
      }
      u32 num = list->getInstNum();
      for (u32 index = 0; index < num; index++) {
        gmk::GmkEffect &effect = list->gmkInsts[index];
        gmk::AGmkBase::CreateInfo createInfo = effect.unknown20;
        if (createInfo.unknown08 != nullptr) {
          effect.create(createInfo);
        }
      }
    }
    for (gmk::GmkSet **it = unknown20.unknownf358.begin(); it != unknown20.unknownf358.end(); ++it) {
      gmk::IGmkList *list = (*it)->getGmkList(gmk::GMK_TYPE_EVENT);
      if (list == nullptr) {
        continue;
      }
      u32 num = list->getInstNum();
      for (u32 index = 0; index < num; index++) {
        // IGmkList::getInst is const in the game (its instances use the const mm::mtl::Vector::operator[]).
        const_cast<gmk::GmkEvent *>(static_cast<const gmk::GmkEvent *>(list->getInst(index)))->unknownf2 = false;
      }
    }
    break;
  case GEV_MAPJUMP_FADEIN: {
    GfUnpopBladeIds unpopBlades;
    if (unpopBlades.unknown08.empty()) {
      break;
    }
    do {
      u16 *blade = &unpopBlades.unknown08[ml::mtRand(unpopBlades.unknown08.size())];
      if (!GfDataBlade::isRareBlade(*blade) && ml::mtRandf1() < unknown005) {
        for (u16 *it = unpopBlades.unknown08.begin(); it != unpopBlades.unknown08.end(); ++it) {
          if (GfDataBlade::isRareBlade(*it)) {
            blade = it;
            break;
          }
        }
      }
      gevBladeActivate(*blade, ACTIVATE_TYPE_UNUSE, ACTIVATE_TYPE_RESERVER);
      unpopBlades.unknown08.erase(blade);
    } while (!unpopBlades.unknown08.empty());
  } break;
  case GEV_MAPJUMP_END:
    unknownfe40 = false;
    break;
  default:
    break;
  }
}

void GfFieldGimmick::gevBladeActivate(u32 blade, ActivateType, ActivateType oldActivateType) {
  if (blade == BLADE_HOMURI) {
    return;
  }
  if (oldActivateType == ACTIVATE_TYPE_RESERVER) {
    if (!GfGameUtil::isBladeInVillage(blade) || unknown003(0, blade) != nullptr) {
      return;
    }
    const gmk::GmkBlade *gmk = unknown003(GfDataBlade::getSize(blade), 0);
    if (gmk != nullptr) {
      unknown004(*gmk, blade);
    }
  } else if (oldActivateType == ACTIVATE_TYPE_PARTY || oldActivateType == ACTIVATE_TYPE_MERCENARY_TEAM || oldActivateType == ACTIVATE_TYPE_UNUSE) {
    GfGmkBladeTraverser traverser(0, blade);
    mm::mtl::PtrSingleton<gmk::GmkManager>::get()->traverseGmkInst(gmk::GMK_TYPE_BLADE, traverser);
    if (traverser.unknown10 == nullptr) {
      return;
    }
    unknown004(*traverser.unknown10, 0);
    GfUnpopBladeIds unpopBlades;
    if (unpopBlades.unknown08.empty()) {
      return;
    }
    u32 newBlade = unpopBlades.unknown08.front();
    if (!GfDataBlade::isRareBlade(newBlade) && ml::mtRandf1() < unknown005) {
      for (u16 id : unpopBlades.unknown08) {
        if (GfDataBlade::isRareBlade(id)) {
          newBlade = id;
          break;
        }
      }
    }
    unknown004(*traverser.unknown10, newBlade);
  }
}

void GfFieldGimmick::build(const GfSetupParam &param) {
  // __LINE__ must be 727 as in the original file: it is the line argument of operator new.
#line 727
  GfEvent::addEventCallback(new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldGimmick(param));
}

void GfFieldGimmick::destroy() {
  GfFieldGimmick *gimmick = get();
  GfEvent::removeEventCallback(gimmick);
  gimmick->finalize();
  delete gimmick;
}

void GfFieldGimmick::finalize() {
  unknown20.dispose();
  unknownf4a8 = false;
}

bool GfFieldGimmick::isInitialized() {
  GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<GfFieldGimmick>::get();
  if (gimmick != nullptr) {
    return gimmick->unknownf4a8;
  }
  return false;
}

void GfFieldGimmick::update(const fw::UpdateInfo &info) {
  if (GfManager::isDestroyNow()) {
    return;
  }
  GfFieldGimmick *gimmick = mm::mtl::PtrSingleton<GfFieldGimmick>::get();
  gimmick->unknown20.update(info.unknown04);
  gimmick->unknownf3b0.update();
  gimmick->unknownf3e8.update(info.unknown04);
  gimmick->unknownf418.update(info.unknown04);
  gimmick->unknownf480.update(info.unknown04);
  if (gimmick->unknownf4ac.unknown00) {
    f32 deltaTime = info.unknown04;
    if (!gimmick->unknownf4ac.unknown01) {
      gimmick->unknownf4ac.unknown01 = mm::mtl::PtrSingleton<gmk::GmkManager>::get()->updateImmediate();
    } else {
      gimmick->unknownf4ac.unknown02 = mm::mtl::PtrSingleton<gmk::GmkManager>::get()->isValidView();
    }
    gimmick->unknownf4ac.unknown04 += deltaTime;
    if (gimmick->unknownf4ac.unknown04 > 10.0f) {
      gimmick->unknownf4ac.unknown02 = true;
    }
  }
  gimmick->unknownf910.update();
  if (gmk::isPlayerExist()) {
    gimmick->unknownfe41 = GfGameUtil::isPointSavable(gmk::getPlayerPos());
  }
}

bool GfFieldGimmick::createGmkSet(int gmkSet) {
  if (!mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    return false;
  }
  mtl::ALLOC_HANDLE memory = getAllocator(ALLOCATOR_UNKNOWN08)->getMemHandle();
  int rscGmkSet = getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(gmkSet);
  mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.createGmkSet(memory, rscGmkSet, mm::Vec3::zero, 0.0f);
  return true;
}

bool GfFieldGimmick::isGmkSetReady() {
  if (GfManager::isDestroyNow()) {
    return true;
  }
  return mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isGmkSetsReady();
}

int GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(int map) {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    return mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.findFirstBdatId_RSC_GmkSetList(map);
  }
  return -1;
}

void GfFieldGimmick::disposeGmkSet(int gmkSet) {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    int rscGmkSet = getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(gmkSet);
    mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.disposeGmkSet(rscGmkSet);
  }
}

int GfFieldGimmick::getBdatIdFrom_RSC_GmkSetList_To_FLD_maplist(int gmkSet) {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.isValid()) {
    return mm::mtl::PtrSingleton<GfFieldGimmick>::get()->unknown20.getMapBdatId(gmkSet);
  }
  return -1;
}

int GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea() {
  if (mm::mtl::PtrSingleton<GfFieldGimmick>::get() == nullptr) {
    return 0;
  }
  gmk::GmkAntiBladeAreaManager *manager = mm::mtl::PtrSingleton<gmk::GmkAntiBladeAreaManager>::get();
  if (manager != nullptr) {
    gmk::GmkAntiBladeArea *area = manager->unknown20;
    if (area != nullptr) {
      return area->unknown20.unknown10->id;
    }
    return 0;
  }
  return 0;
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldGimmick>::~PtrSingleton();

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<gf::GF_SLOT_HANDLE *, float>::MapTraits<gf::GF_SLOT_HANDLE *, float>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<gf::GF_SLOT_HANDLE *, float> &);
template void unknown101::rebalance(unknown101::node *);

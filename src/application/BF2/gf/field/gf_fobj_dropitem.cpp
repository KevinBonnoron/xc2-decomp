#include "gf/field/gf_fobj_dropitem.h"
#include "mm_mtl/map.h" // IWYU pragma: keep

#include "mm_mtl/fixed_list.h" // IWYU pragma: keep

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/field/gf_fobj_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixstr.h"

namespace gf {

// Inferred role: item list bdats of the dropitems; original name unknown.
static const u32 unknown001[] = {
    BDAT_ITM_COLLECTION_LIST,
    BDAT_ITM_TRESURE_LIST,
    BDAT_ITM_PC_WPN_CHIP,
    BDAT_ITM_PC_EQUIP,
    BDAT_ITM_ORB,
    BDAT_BTL_HEAL_POT,
    BDAT_ITM_PRECIOUS_LIST,
    BDAT_ITM_CRYSTAL_LIST,
    BDAT_ITM_SALVAGE_LIST,
    BDAT_ITM_BOOSTER_LIST,
};

void GfFobjDropitem::bindToGfObj(GF_OBJ_HANDLE *handle) const {
  GfObjAcc acc(handle);
  acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, reinterpret_cast<u64>(this));
}

void GfFobjDropitem::unbindToGfObj(GF_OBJ_HANDLE *handle) const {
  if (handle != INVALID_HANDLE) {
    GfObjAcc acc(handle);
    if (acc.isValid()) {
      acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, 0);
    }
  }
}

void GfFobjDropitem::destroy() {
  disposeEffect();
  if (unknown10 != INVALID_HANDLE) {
    GfObjAcc acc(unknown10);
    if (acc.isValid()) {
      acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, 0);
    }
  }
}

void GfFobjDropitem::setEventDisp(bool isDisp) {
  GfObjAcc acc(unknown10);
  if (acc.isValid()) {
    acc.setDisp(OBJDISP_UNKNOWN_1, isDisp);
  }
  if (unknown54 != 0) {
    fw::EffectManager::get()->setDisp(unknown54, isDisp);
  }
}

void GfFobjDropitem::BdatInfo::create(s32 id) {
  GfFobjManager *manager = GfFobjManager::get();
  u8 *bdat = manager != nullptr ? manager->unknown9068 : nullptr;
  unknown00 = Bdat::getValCheck(bdat, "dropSE", id, 2);
  unknown02 = Bdat::getValCheck(bdat, "getdropSE", id, 2);
  unknown04 = Bdat::getValCheck(bdat, "limitType", id, 1);
}

bool GfFobjDropitem::EmitInfo::isValid() const {
  if (unknown28.size() != 0) {
    mm::mtl::FixStr<16> name;
    name.format("paramid%d", unknown54);
    GfFobjManager *manager = GfFobjManager::get();
    u8 *bdat = manager != nullptr ? manager->unknown9068 : nullptr;
    return Bdat::getMember(bdat, name.c_str()) != nullptr;
  }
  return false;
}

bool GfFobjDropitem::isEnableGet() const { return unknown30 > 1; }

void GfFobjDropitem::disposeEffect() {
  if (unknown54 != 0) {
    fw::EffectManager::get()->dead(unknown54);
    unknown54 = 0;
  }
}

u32 GfFobjDropitem::getBdatDefineFromItemId(s32 itemId) {
  for (u32 i = 0; i < sizeof(unknown001) / sizeof(unknown001[0]); i++) {
    u32 bdatId = unknown001[i];
    u8 *bdat = GfDataBdat::getFP(bdatId);
    if (bdat != nullptr) {
      s32 top = Bdat::getIdTop(bdat);
      s32 count = Bdat::getIdCount(bdat);
      if (itemId >= top && itemId < top + count) {
        return bdatId;
      }
    }
  }
  return GfDataBdat::BDAT_COUNT;
}

u32 GfFobjDropitem::getResBdatIdFromItemId(s32 itemId) {
  for (u32 i = 0; i < sizeof(unknown001) / sizeof(unknown001[0]); i++) {
    u32 bdatId = unknown001[i];
    u8 *bdat = GfDataBdat::getFP(bdatId);
    if (bdat != nullptr) {
      s32 top = Bdat::getIdTop(bdat);
      s32 count = Bdat::getIdCount(bdat);
      if (itemId >= top && itemId < top + count) {
        u32 resBdatId = 0xffffffff;
        bdat = GfDataBdat::getFP(bdatId);
        if (bdat != nullptr) {
          switch (bdatId) {
          case BDAT_ITM_TRESURE_LIST:
          case BDAT_ITM_BOOSTER_LIST:
            resBdatId = 9;
            break;
          case BDAT_ITM_COLLECTION_LIST:
            resBdatId = (Bdat::getValCheck(bdat, "Category", itemId, 1) & 0xff) - 3;
            break;
          case BDAT_ITM_PC_WPN_CHIP:
            resBdatId = 0xf;
            break;
          case BDAT_ITM_PC_EQUIP:
            resBdatId = 0x12;
            break;
          case BDAT_ITM_ORB:
            resBdatId = 0x13;
            break;
          case BDAT_BTL_HEAL_POT:
            resBdatId = Bdat::getValCheck(bdat, "DropRsc", itemId, 1) & 0xff;
            break;
          case BDAT_ITM_PRECIOUS_LIST:
            resBdatId = 0x17;
            break;
          case BDAT_ITM_CRYSTAL_LIST:
            resBdatId = (Bdat::getValCheck(bdat, "Category", itemId, 1) & 0xff) + 0x18;
            break;
          case BDAT_ITM_SALVAGE_LIST:
            resBdatId = 8;
            break;
          }
        }
        return resBdatId;
      }
    }
  }
  return 0xffffffff;
}

} // namespace gf

template mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::iterator mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::erase(mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::iterator);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<unsigned short, float>::MapTraits<unsigned short, float>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<unsigned short, float> &);
template void unknown101::rebalance(unknown101::node *);

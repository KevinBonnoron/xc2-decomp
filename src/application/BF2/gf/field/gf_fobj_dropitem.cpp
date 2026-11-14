#include "gf/field/gf_fobj_dropitem.h"

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "framework/object/component_object.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_fobj_gotten_effect_manager.h"
#include "gf/field/gf_fobj_manager.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_init_param.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_factory.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h" // IWYU pragma: keep
#include "mm_mtl/rtti.h"

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

// Inferred role: rows of BDAT_FLD_WILDCARD_DATA holding the gold amounts that select the size of the gold dropitem; original names unknown.
static const int unknown004 = 8;
static const int unknown005 = 9;
static const int unknown006 = 10;
static const int unknown007 = 11;

// Inferred helper: gets the setup of a field object; original name unknown.
static GfObjSetupFieldObj *unknown003(GF_OBJ_HANDLE *handle) {
  GfObjSetupFieldObj *setup = nullptr;
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  if (info != nullptr && info->unknown30 != nullptr) {
    GfObj *obj = info->unknown18;
    if (info->unknown30->unknown08 == obj->unknown28 && obj->unknown28 == OBJECT_TYPE_FIELD_OBJ) {
      setup = mm::mtl::dynamicCast<GfObjSetupFieldObj>(info->unknown30);
    }
  }
  return setup;
}
// Inferred role: pick up area of the pc param list; original type name unknown.
struct unknown002 {
  f32 unknown00; // Inferred role: horizontal radius; original member name unknown.
  f32 unknown04; // Inferred role: height above; original member name unknown.
  f32 unknown08; // Inferred role: depth below; original member name unknown.
};

GfFobjDropitem::GfFobjDropitem(GF_OBJ_HANDLE *handle)
    : unknown08(0), unknown0a(0), unknown0c(false), unknown0e(false), unknown10(handle), unknown20(0.0f, 0.0f, 0.0f), unknown30(0), unknown34(0.0f), unknown38(0.0f), unknown3c(0.0f), unknown50(false),
      unknown54(0) {}

void GfFobjDropitem::bindToGfObj(GF_OBJ_HANDLE *handle) const {
  GfObjAcc acc(handle);
  acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, reinterpret_cast<u64>(this));
}

void GfFobjDropitem::unbindToGfObj(GF_OBJ_HANDLE *handle) const {
  if (handle != unknown020) {
    GfObjAcc acc(handle);
    if (acc.isValid()) {
      acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, 0);
    }
  }
}

void GfFobjDropitem::destroy() {
  disposeEffect();
  if (unknown10 != unknown020) {
    GfObjAcc acc(unknown10);
    if (acc.isValid()) {
      acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, 0);
    }
  }
}

void GfFobjDropitem::setEventDisp(bool isDisp) {
  GfObjAcc acc(unknown10);
  if (acc.isValid()) {
    acc.setDisp(OBJDISP_UNKNOWN_0, isDisp);
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

void GfFobjDropitem::createGottenEffect(GF_OBJ_HANDLE *target) const {
  if (GfObjUtil::getObj(unknown10) != nullptr) {
    GfObjAcc acc(unknown10);
    if (acc.isValidTransform()) {
      GfFobjManager *manager = GfFobjManager::get();
      if (manager != nullptr) {
        GfFobjGottenEffectManager &effects = manager->unknown9088;
        GfFobjGottenEffectManager::CreateEffectInfo info;
        info.unknown00 = acc.getWorldTransform().unknown00;
        info.unknown10 = target;
        info.unknown18 = unknown0e;
        effects.createEffect(info);
      }
    }
  }
}

bool GfFobjDropitem::canGetItem(GF_OBJ_HANDLE *target, f32 margin) const {
  GfObj *targetObj = GfObjUtil::getObj(target);
  if (targetObj != nullptr) {
    if (targetObj->unknown38[GfComTransform::COMPONENT_INDEX] == nullptr) {
      return false;
    }
    if (targetObj->unknown38[GfComTransform::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComTransform::m_rtti)) {
      fw::ParamList &paramList = *fw::ParamManager::get()->unknown408[5];
      const unknown002 *param = paramList.unknown0c > 5 ? static_cast<const unknown002 *>(paramList.unknown10[5].param) : nullptr;
      GfObj *obj = GfObjUtil::getObj(unknown10);
      if (obj != nullptr) {
        if (obj->unknown38[GfComTransform::COMPONENT_INDEX] == nullptr) {
          return false;
        }
        if (obj->unknown38[GfComTransform::COMPONENT_INDEX]->getRTTI()->isKindOf(&GfComTransform::m_rtti)) {
          mm::Vec3 diff = obj->getComponent<GfComTransform>()->getPosition() - targetObj->getComponent<GfComTransform>()->getPosition();
          if (diff.y + margin < -param->unknown08) {
            return false;
          }
          if (param->unknown04 < diff.y - margin) {
            return false;
          }
          f32 bonus = 0.0f;
          s16 percent = GfGameManager::getOwnerBonus()->unknown00[OWNER_BONUS_UNKNOWN_10];
          if (percent >= 0) {
            s32 clamped = percent;
            if (clamped > 9999) {
              clamped = 10000;
            }
            bonus = clamped * 0.01f;
          }
          f32 radius = bonus + param->unknown00 + margin;
          diff.y = 0.0f;
          if (radius * radius < diff.x * diff.x + diff.y * diff.y + diff.z * diff.z) {
            return false;
          }
          return true;
        }
      }
    }
  }
  return false;
}

bool GfFobjDropitem::isEnableGet() const { return unknown30 > 1; }

bool GfFobjDropitem::applyGetItem(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target) {
  GfObjAcc acc(handle);
  if (acc.isValid()) {
    GfFobjDropitem *dropitem = reinterpret_cast<GfFobjDropitem *>(acc.getUserData(OBJ_USER_DATA_UNKNOWN_2));
    if (dropitem != nullptr && GfObjUtil::getObj(target) != nullptr) {
      dropitem->applyGetItem(target);
      return true;
    }
  }
  return false;
}

void GfFobjDropitem::disposeEffect() {
  if (unknown54 != 0) {
    fw::EffectManager::get()->dead(unknown54);
    unknown54 = 0;
  }
}

GF_OBJ_HANDLE *GfFobjDropitem::emitDropgold(u8 paramIndex, u32 gold) {
  GfFobjManager *manager = GfFobjManager::get();
  CBdatWrapper bdat(manager != nullptr ? manager->unknown9068 : nullptr);
  GfFobjManager::getDropitemParams();
  GfInitParamFobj initParam;
  u8 *wildcard = GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA);
  u32 limit1 = Bdat::getValCheck(wildcard, 0, unknown004, gmk::BDAT_TYPE_UNKNOWN_8).valueF32;
  u32 limit2 = Bdat::getValCheck(wildcard, 0, unknown005, gmk::BDAT_TYPE_UNKNOWN_8).valueF32;
  u32 limit3 = Bdat::getValCheck(wildcard, 0, unknown006, gmk::BDAT_TYPE_UNKNOWN_8).valueF32;
  u32 limit4 = Bdat::getValCheck(wildcard, 0, unknown007, gmk::BDAT_TYPE_UNKNOWN_8).valueF32;
  if (gold < limit1) {
    initParam.m_bladeID = 10;
  } else if (gold < limit2) {
    initParam.m_bladeID = 11;
  } else if (gold < limit3) {
    initParam.m_bladeID = 12;
  } else if (gold < limit4) {
    initParam.m_bladeID = 13;
  } else {
    initParam.m_bladeID = 14;
  }
  initParam.unknown18 = &bdat;
  initParam.unknown94 = paramIndex;
  GF_OBJ_HANDLE *handle = GfObjFactory::createFieldObj(initParam);
  GfObjSetupFieldObj *setup = unknown003(handle);
  setup->unknown80 = gold;
  setup->unknown84 = initParam.m_bladeID;
  return handle;
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

GfDropitemEmitter::GfDropitemEmitter(const CreateInfo *info) : m_dropitemsEmitted(false), unknown44(0.0f), unknown48(0.0f) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfDropitemEmitter::create(const CreateInfo &info) {
  dispose();
  unknown00 = info;
  unknown50 = &GfDropitemEmitter::seqWaitBeginDrop;
}

void GfDropitemEmitter::dispose() {
  unknown44 = 0.0f;
  unknown48 = 0.0f;
  m_dropitemsEmitted = false;
  unknown00 = CreateInfo();
}

void GfDropitemEmitter::update(f32 deltaTime) {
  if (unknown00.unknown28 != nullptr && unknown00.unknown30 > 0) {
    unknown44 += deltaTime;
    if (unknown50) {
      (this->*unknown50)(deltaTime);
    }
  }
}

void GfDropitemEmitter::seqWaitBeginDrop(f32 deltaTime) {
  if (unknown44 < unknown00.unknown1c) {
    return;
  }
  GfFobjDropitem::EmitInfo info;
  info.createDropitemInfos(unknown00.unknown28, unknown00.unknown30);
  info.unknown00 = unknown00.unknown00;
  info.unknown10 = unknown00.unknown10;
  info.unknown14 = unknown00.unknown14;
  info.unknown18 = unknown00.unknown18;
  info.unknown1c = unknown00.unknown20;
  info.unknown20 = unknown00.unknown24;
  unknown48 = GfFobjDropitem::emitDropitems(info) + unknown44;
  unknown50 = &GfDropitemEmitter::seqWaitEndDrop;
}

void GfDropitemEmitter::seqWaitEndDrop(f32 deltaTime) {
  if (unknown44 < unknown48) {
    return;
  }
  m_dropitemsEmitted = true;
  unknown50 = nullptr;
}

} // namespace gf

template mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::iterator mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::erase(mm::mtl::FixedList<gf::GfFobjDropitem *, 1024>::iterator);

typedef mm::mtl::RedBlackTreeBase<mm::mtl::Map<unsigned short, float>::MapTraits<unsigned short, float>> unknown101;

template void unknown101::free_node(unknown101::node *, bool);
template unknown101::node *unknown101::insert(const mm::mtl::MapPair<unsigned short, float> &);
template void unknown101::rebalance(unknown101::node *);
template void mm::mtl::Vector<gf::GfDropitemInfo>::expand(size_t, size_t);

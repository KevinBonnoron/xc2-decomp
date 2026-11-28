#include "gf/field/gf_fobj_dropitem.h"

#include <utility>

#include "bdat.h"
#include "framework/effect/effect_manager.h"
#include "framework/memory/framework_memory.h"
#include "framework/object/component_object.h"
#include "framework/sound/sound_manager.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_dropitem_params.h"
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
#include "ml/rand.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h" // IWYU pragma: keep
#include "mm_mtl/rtti.h"

// The game builds the dropitem parameters in this unit: the parameter functions (0x71002f6980 to 0x71002f736c) come directly before the emitter (0x71002f73e4) and
// GfFobjDropitem (from 0x71002f770c) with no other unit between, and the deferred mm::mtl::Vector<GfDropitemParam>::extend of the parameter file (0x71002fa940)
// comes after the last function of GfFobjDropitem (0x71002fa124), where a unit emits its deferred functions (a separate parameter unit would hold it right after
// its own functions). GfFobjDropitem::initialize (0x71002f862c) also inlines GfDropitemParamInst::create, getInitVelocity and GfDropitemParams::getParamByBdatId
// although each has an out-of-line copy: the callees are visible in the unit of the caller.
#include "gf/field/gf_dropitem_param.cpp"

namespace fw {
enum SoundCategory : int;
} // namespace fw

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
    : unknown08(0), unknown0a(0), unknown0c(false), unknown0e(false), m_GF_OBJ_HANDLE(handle), unknown20(0.0f, 0.0f, 0.0f), unknown30(0), unknown34(0.0f), unknown38(0.0f), unknown3c(0.0f),
      unknown50(false), unknown54(0) {}

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
  if (m_GF_OBJ_HANDLE != unknown020) {
    GfObjAcc acc(m_GF_OBJ_HANDLE);
    if (acc.isValid()) {
      acc.setUserData(OBJ_USER_DATA_UNKNOWN_2, 0);
    }
  }
}

void GfFobjDropitem::setEventDisp(bool isDisp) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
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
  if (GfObjUtil::getObj(m_GF_OBJ_HANDLE) != nullptr) {
    GfObjAcc acc(m_GF_OBJ_HANDLE);
    if (acc.isValidTransform()) {
      GfFobjManager *manager = GfFobjManager::get();
      if (manager != nullptr) {
        GfFobjGottenEffectManager &effects = manager->m_fobjGottenEffectManager;
        GfFobjGottenEffectManager::CreateEffectInfo info;
        info.unknown00 = acc.getWorldTransform().unknown00;
        info.m_GF_OBJ_HANDLE = target;
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
      GfObj *obj = GfObjUtil::getObj(m_GF_OBJ_HANDLE);
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
  initParam.m_cBdatWrapper = &bdat;
  initParam.unknown94 = paramIndex;
  GF_OBJ_HANDLE *handle = GfObjFactory::createFieldObj(initParam);
  GfObjSetupFieldObj *setup = unknown003(handle);
  setup->unknown80 = gold;
  setup->unknown84 = initParam.m_bladeID;
  return handle;
}

// 1.0.0: 0x71002f7cb4, 515 instructions. Reads the drop list of the emit info (items with a count and a rate, gold entries), builds the list of the items to
// drop (the counts, then one entry per random roll against the rates) and emits the items and the gold in turns on a fan of angles. Returns the longest life
// time of the emitted dropitems, or -1 when there is nothing to drop. The game's list is a mm::mtl::Vector<std::pair<int, float>>: its expand is the
// out-of-line _ZN2mm3mtl6VectorINSt3__14pairIifEEE6expandEmm (0x71002faad8) that the function calls.
f32 GfFobjDropitem::emitDropitems(const EmitInfo &info) {
  fw::SoundManager::get()->playSe("se007", nullptr, 1.0f, static_cast<fw::SoundCategory>(0));
  u32 goldTotal = 0;
  u32 rateTotal = 0;
  u32 itemCount = 0;
  u32 goldCount = 0;
  for (u32 i = 0; i < info.unknown28.size(); i++) {
    const GfDropitemInfo &entry = info.unknown28[i];
    if (entry.unknown00 > 0) {
      itemCount += entry.unknown04;
      rateTotal += entry.unknown05;
    } else if (entry.unknown08 != 0) {
      goldTotal += entry.unknown08;
      goldCount += entry.unknown04;
    }
  }
  u32 itemTotal = info.unknown50 + itemCount;
  if (itemTotal == 0 && goldCount == 0) {
    return -1.0f;
  }
  u32 goldMin = mm::min(goldTotal, goldCount);
  mm::mtl::Vector<std::pair<int, float>> list;
  list.setAllocator(fw::FrameworkMemory::getAllocator(5));
  list.reserve(itemTotal);
  for (u32 i = 0; i < info.unknown28.size(); i++) {
    const GfDropitemInfo &entry = info.unknown28[i];
    for (u8 n = 0; n < entry.unknown04; n++) {
      if (entry.unknown00 > 0) {
        list.push_back(std::pair<int, float>(entry.unknown00, entry.unknown0c));
      }
    }
  }
  for (u8 n = 0; n < info.unknown50; n++) {
    f32 roll = rateTotal * ml::mtRandf1();
    for (u32 i = 0; i < info.unknown28.size(); i++) {
      const GfDropitemInfo &entry = info.unknown28[i];
      if (entry.unknown00 > 0) {
        f32 rate = entry.unknown05;
        // `if (rate >= roll) { push; break; } roll -= rate;` gives `b.ge` where the game has the inverted branch.
        if (rate < roll) {
          roll -= rate;
        } else {
          list.push_back(std::pair<int, float>(entry.unknown00, entry.unknown0c));
          break;
        }
      }
    }
  }
  u32 total = list.size() + goldMin;
  if (total == 0) {
    return -1.0f;
  }
  f32 result = 0.0f;
  f32 step = info.unknown14 * 2.0f / total;
  f32 angle = info.unknown10 - info.unknown14;
  u32 gold = goldTotal - goldMin;
  u32 itemDropped = 0;
  u32 goldDropped = 0;
  for (u32 i = 0; i < total; i++, angle += step) {
    // Measured: `u32 itemRest = list.size() - itemDropped;` schedules the index copy `mov w24, w25` before the `sub w26, w8, w25` (8 differing lines, first difference at 0x71002f8168).
    u32 itemRest = list.size();
    itemRest -= itemDropped;
    u32 goldRest = goldMin - goldDropped;
    GF_OBJ_HANDLE *handle = unknown020;
    if (ml::mtRandf1() * (itemRest + goldRest) < itemRest) {
      int itemId = list[itemDropped].first;
      // Inferred role: the item 0x61c3 is dropped only once while the emit info asks for it (unknown55): the local flag 0xc4d5 of group 1 records the drop; original names unknown.
      // The flag is tested first. With `itemId == 0x61c3 &&` first the optimised IR branches on `or (itemId != 0x61c3), (flag == 0)` to the skip block; with the flag first it branches on
      // `and (itemId == 0x61c3), (flag != 0)` to the body, which is the same machine code, but the loop counters (itemDropped, goldDropped and the index copy) then get w24, w25 and w23
      // instead of the game's w25, w23 and w24 (29 differing lines, first at 0x71002f8154). Traced in the greedy allocator: each counter evicts one of the assert constants hoisted
      // before the loop, and the order of those constants follows the block order of the IR.
      if (info.unknown55 && itemId == 0x61c3) {
        if (GfGameFlag::getLocal(1, 0xc4d5) != 0) {
          continue;
        }
        GfGameFlag::setLocal(1, 0xc4d5, 1);
      }
      f32 itemParam = list[itemDropped].second;
      handle = emitDropitem(info.unknown54, itemId, itemParam);
      itemDropped++;
    } else {
      u32 amount = gold;
      if (goldRest != 1) {
        amount = static_cast<f32>(gold / static_cast<u32>(goldRest * ml::mtRandf1() + 1.0f)) * ml::mtRandf1();
      }
      // `gold -= amount` comes before the call: the game subtracts with `sub w20, w20, w8` before `bl emitDropgold`, and w8 does not survive the call.
      gold -= amount;
      handle = emitDropgold(info.unknown54, amount + 1);
      goldDropped++;
    }
    if (handle != unknown020) {
      GfDropitemParams *params = GfFobjManager::getDropitemParams();
      GfObjSetupFieldObj *setup = unknown003(handle);
      if (!params->isBdatIdValid(setup->unknown6c)) {
        setup->unknown6c = params->unknown30;
      }
      const GfDropitemParam &param = params->getParamByBdatId(setup->unknown6c);
      // The position and rotation locals place the stores of the setup: with the six members written one by one the function has 514 instructions, and with either local alone
      // (the other expression written in the store) it still does not match (measured).
      mm::Vec3 position(info.unknown00.x, info.unknown00.y + param.unknown34 + param.unknown38, info.unknown00.z);
      mm::Vec3 rotation(0.0f, angle + (ml::mtRandf1() - 0.5f) * (param.unknown18 * mm::DEG_TO_RAD), 0.0f);
      setup->unknown20 = position;
      setup->unknown30 = rotation;
      setup->unknown70 = info.unknown18;
      f32 lifeTime = info.unknown1c + info.unknown20 * ml::mtRandf1();
      setup->unknown74 = lifeTime;
      // `lifeTime > result` gives the compares in the other operand order (`fcmp s0, s9`).
      if (result < lifeTime) {
        result = lifeTime;
      }
    }
  }
  return result;
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
  m_createInfo = info;
  unknown50 = &GfDropitemEmitter::seqWaitBeginDrop;
}

void GfDropitemEmitter::dispose() {
  unknown44 = 0.0f;
  unknown48 = 0.0f;
  m_dropitemsEmitted = false;
  m_createInfo = CreateInfo();
}

void GfDropitemEmitter::update(f32 deltaTime) {
  if (m_createInfo.unknown28 != nullptr && m_createInfo.unknown30 > 0) {
    unknown44 += deltaTime;
    if (unknown50) {
      (this->*unknown50)(deltaTime);
    }
  }
}

void GfDropitemEmitter::seqWaitBeginDrop(f32 deltaTime) {
  if (unknown44 < m_createInfo.unknown1c) {
    return;
  }
  GfFobjDropitem::EmitInfo info;
  info.createDropitemInfos(m_createInfo.unknown28, m_createInfo.unknown30);
  info.unknown00 = m_createInfo.unknown00;
  info.unknown10 = m_createInfo.unknown10;
  info.unknown14 = m_createInfo.unknown14;
  info.unknown18 = m_createInfo.unknown18;
  info.unknown1c = m_createInfo.unknown20;
  info.unknown20 = m_createInfo.unknown24;
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
template void mm::mtl::Vector<std::pair<int, float>>::expand(size_t, size_t);

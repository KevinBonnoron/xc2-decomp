#include "gf/field/gf_field_dmg.h"

#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gmk/gmk_bdat.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep

namespace gf {

const GfFieldDmgManager::BdatInfo *GfFieldDmgManager::findBdatInfo(u16 attribute) const {
  if (!unknown10.empty()) {
    for (const BdatInfo &info : unknown10) {
      if (info.unknown02 == attribute) {
        return &info;
      }
    }
  }
  return nullptr;
}

GfFieldDmgManager::GfFieldDmgManager(const GfSetupParam *param) {
  GfEvent::addEventCallback(this);
  if (param != nullptr) {
    create(*param);
  }
}

void GfFieldDmgManager::create(const GfSetupParam &) {
  dispose();
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_DMGFLOOR);
  int count = Bdat::getIdCount(bdat);
  unknown10.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0));
  unknown10.reserve(count);
  unknown10.resize(count);
}

GfFieldDmgManager::~GfFieldDmgManager() {
  dispose();
  GfEvent::removeEventCallback(this);
}

void GfFieldDmgManager::dispose() {
  if (!unknown10.empty()) {
    unknown10.destroy();
  }
}

void GfFieldDmgManager::BdatInfo::create(const CBdatWrapper &bdat, int id) {
  unknown02 = 0;
  unknown00 = bdat.getValCheck("Condition", id, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown02 = bdat.getValCheck("attributeID", id, gmk::BDAT_TYPE_UNKNOWN_2);
  Bdat::Value interval;
  interval.valueU32 = bdat.getValCheck("DMG_interval", id, gmk::BDAT_TYPE_UNKNOWN_8);
  unknown04 = interval.valueF32;
  unknown08 = bdat.getValCheck("Pc_dmg", id, gmk::BDAT_TYPE_UNKNOWN_1);
  unknown09 = bdat.getValCheck("EN_dmg", id, gmk::BDAT_TYPE_UNKNOWN_1);
}

void GfFieldDmgManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  if (event != GEV_UNKNOWN_5) {
    return;
  }
  unknown10.clear();
  CBdatWrapper bdat(GfDataBdat::getFP(BDAT_FLD_DMGFLOOR));
  int count = Bdat::getIdCount(bdat.unknown00);
  for (int i = 0; i < count; i++) {
    int id = Bdat::getIdTop(bdat.unknown00) + i;
    if (static_cast<u16>(bdat.getValCheck("MAPID", id, gmk::BDAT_TYPE_UNKNOWN_2)) == info.unknown04) {
      unknown10.push_back(BdatInfo());
      unknown10.back().create(bdat, id);
    }
  }
}

void GfFieldDmgManager::build(const GfSetupParam &param) {
  // __LINE__ must be 275 as in the original file: it is the line argument of operator new.
#line 275
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldDmgManager(&param);
}

void GfFieldDmgManager::destroy() {
  if (get() != nullptr) {
    delete get();
  }
}

GfFieldDmg::GfFieldDmg(const CreateInfo *info) : unknown08(true), unknown09(false), unknown10(nullptr), unknown18(0xffffffff), unknown1c(0.0f), unknown20(false) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFieldDmg::create(const CreateInfo &info) {
  dispose();
  unknown08 = info.unknown00;
  unknown09 = true;
}

void GfFieldDmg::dispose() {
  unknown20 = false;
  unknown18 = fw::COLI_INVALID_DAMAGE_ID;
  unknown1c = 0.0f;
  unknown10 = nullptr;
  unknown08 = true;
  unknown09 = false;
}

void GfFieldDmg::update(const UpdateInfo &info) {
  unknown20 = false;
  if (!unknown09) {
    return;
  }
  if (info.unknown08 != unknown18) {
    if (info.unknown08 < 0) {
      unknown10 = nullptr;
    } else {
      unknown10 = GfFieldDmgManager::get()->findBdatInfo(info.unknown08);
    }
    unknown18 = info.unknown08;
    unknown1c = 0.0f;
  }
  if (unknown10 == nullptr) {
    return;
  }
  GfGameUtil::requestFieldDamage(info.unknown00);
  unknown1c += info.unknown0c;
  if (unknown10->unknown04 <= unknown1c) {
    unknown20 = true;
    unknown1c = 0.0f;
    if (unknown08) {
      applyDamage(info.unknown00, unknown10->unknown09);
    }
  }
}

bool GfFieldDmg::applyDamage(GF_OBJ_HANDLE *handle, u8 rate) {
  GfObjAcc acc(handle);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return false;
  }
  DataParamAcc param(handle);
  u32 damage = calculateDamage(param.getHpMax(false), rate, 0.0f);
  u32 hp = param.getHp();
  if (damage >= hp - 1) {
    damage = hp - 1;
  }
  if (damage != 0) {
    MsgObjectDamage message(damage, 2);
    obj->sendMessage(obj, message);
  }
  return true;
}

s32 GfFieldDmg::calculateDamage(u32 maxHp, u8 rate, f32 reduction) {
  u32 damage = static_cast<u32>(static_cast<f32>(rate * maxHp) * 0.01f);
  return damage - static_cast<u32>(static_cast<f32>(damage) * reduction);
}

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldDmgManager>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfFieldDmgManager::BdatInfo>::resize(size_t);
template void mm::mtl::Vector<gf::GfFieldDmgManager::BdatInfo>::expand(size_t, size_t);
template void mm::mtl::Vector<gf::GfFieldDmgManager::BdatInfo>::extend(size_t, size_t);

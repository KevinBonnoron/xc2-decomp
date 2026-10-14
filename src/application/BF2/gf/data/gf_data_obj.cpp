#include "gf/data/gf_data_obj.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_mob.h"
#include "gf/data/gf_data_npc.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

DataObjPcWpn::DataObjPcWpn(u32 id) : handle(INVALID_HANDLE), id(id) {}

DataObjPcWpn::~DataObjPcWpn() {}

bool DataObjPcWpn::isValid() const { return id != 0; }

const char *DataObjPcWpn::getName() const { return GfDataItem::getName(getBdatId()); }

bool DataObjPcWpn::getName(u8 *&bdat, u32 &textId) const { return GfDataItem::getName(bdat, textId, getBdatId()); }

u32 DataObjPcWpn::getBdatId() const { return id; }

u32 DataObjPcWpn::getEquipWeapon(bool, int) const { return id; }

u32 DataObjPcWpn::getWeaponType(bool, int) const { return GfBdatItem::get()->getPcWpnWpnType(getBdatId()); }

u32 DataObjPcWpn::getWeaponDamage(bool) const { return GfBdatItem::get()->getPcWpnDamage(getBdatId()); }

u32 DataObjPcWpn::getWeaponStability(bool) const { return GfBdatItem::get()->getPcWpnStability(getBdatId()); }

DataObjNpc::DataObjNpc(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjNpc::isValid() const { return id != 0; }

const char *DataObjNpc::getName() const { return GfDataNpc::getName(getBdatId()); }

bool DataObjNpc::getName(u8 *&bdat, u32 &textId) const { return GfDataNpc::getName(bdat, textId, getBdatId()); }

const char *DataObjNpc::getModelResourceName() const { return GfDataNpc::getModelName(getBdatId()); }

const char *DataObjNpc::getMotionResourceName() const { return GfDataNpc::getMotionName(getBdatId()); }

u32 DataObjNpc::getBdatId() const { return id; }

bool DataObjNpc::isDispInitExtraParts(u32 part) const { return GfDataNpc::getExtraParts(getBdatId(), part); }

u32 DataObjNpc::getMenuOffset() const { return GfDataNpc::getOffsetID(getBdatId()); }

u32 DataObjNpc::getFootStep() const { return GfDataNpc::getFootStep(getBdatId()); }

u32 DataObjNpc::getFootStepEffect() const { return GfDataNpc::getFootStepEffect(getBdatId()); }

u32 DataObjNpc::getEyeRotControl() const { return GfDataNpc::getEyeRotControl(getBdatId()); }

DataObjMap::DataObjMap(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjMap::isValid() const { return id != 0; }

const char *DataObjMap::getName() const { return GfBdatMaplist::get()->getMaplistresource(getBdatId()); }

u32 DataObjMap::getBdatId() const { return id; }

DataObjMob::DataObjMob(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjMob::isValid() const { return id != 0; }

const char *DataObjMob::getName() const { return GfDataMob::getName(getBdatId()); }

bool DataObjMob::getName(u8 *&bdat, u32 &textId) const { return GfDataMob::getName(bdat, textId, getBdatId()); }

const char *DataObjMob::getModelResourceName() const { return GfBdatRsc::get()->getRscMobListModel(getBdatId()); }

const char *DataObjMob::getMotionResourceName() const { return GfBdatRsc::get()->getRscMobListMotion(getBdatId()); }

u32 DataObjMob::getBdatId() const { return id; }

bool DataObjMob::isDispInitExtraParts(u32 part) const { return GfBdatRsc::get()->getRscMobListExtraParts(getBdatId(), part) != 0; }

u32 DataObjMob::getMenuOffset() const { return GfBdatRsc::get()->getRscMobListOffsetID(getBdatId()); }

u32 DataObjMob::getFootStep() const { return GfDataMob::getFootStep(getBdatId()); }

u32 DataObjMob::getFootStepEffect() const { return GfDataMob::getFootStepEffect(getBdatId()); }

DataObjUiObj::DataObjUiObj(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjUiObj::isValid() const { return id != 0; }

const char *DataObjUiObj::getName() const { return GfDataMob::getName(getBdatId()); }

bool DataObjUiObj::getName(u8 *&bdat, u32 &textId) const { return GfDataMob::getName(bdat, textId, getBdatId()); }

const char *DataObjUiObj::getModelResourceName() const { return GfBdatRsc::get()->getRscMobListModel(getBdatId()); }

const char *DataObjUiObj::getMotionResourceName() const { return GfBdatRsc::get()->getRscMobListMotion(getBdatId()); }

u32 DataObjUiObj::getBdatId() const { return id; }

bool DataObjUiObj::isDispInitExtraParts(u32) const { return false; }

DataObjGmk::DataObjGmk(u32 id, GimmickType gimmickType) : handle(INVALID_HANDLE), id(id), gimmickType(gimmickType) {}

bool DataObjGmk::isValid() const { return id != 0; }

const char *DataObjGmk::getName() const { return ""; }

bool DataObjGmk::getName(u8 *&, u32 &) const { return false; }

const char *DataObjGmk::getModelResourceName() const {
  if (gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return GfBdatRsc::get()->getRSC_TboxListModel(getBdatId());
  }

  return GfBdatRsc::get()->getRSC_MapObjListModel(getBdatId());
}

const char *DataObjGmk::getMotionResourceName() const {
  if (gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return GfBdatRsc::get()->getRSC_TboxListMotion(getBdatId());
  }

  return GfBdatRsc::get()->getRSC_MapObjListMotion(getBdatId());
}

u32 DataObjGmk::getBdatId() const { return id; }

bool DataObjGmk::isDispInitExtraParts(u32) const {
  if (gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return false;
  }

  return GfBdatRsc::get()->getRSC_MapObjListExtraParts1(getBdatId()) != 0;
}

bool DataObjBelonging::isValid() const { return handle != INVALID_HANDLE; }

const char *DataObjBelonging::getName() const { return ""; }

bool DataObjBelonging::getName(u8 *&, u32 &) const { return false; }

const char *DataObjBelonging::getModelResourceName() const { return ""; }

const char *DataObjBelonging::getMotionResourceName() const { return ""; }

u32 DataObjBelonging::getBdatId() const { return 0; }

} // namespace gf

#include "gmk/gmk_base.h"
#include "bdat.h"
#include "fw/fw_coli_check.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"

namespace gmk {

AGmkBase::AGmkBase() : m_createBaseInfo(), _40() {}

void AGmkBase::disposeBase() {
  m_createBaseInfo.m_ownerGmkEnemyList = nullptr;
  m_createBaseInfo.m_xform = nullptr;
  m_createBaseInfo.unknown10 = nullptr;
}

u8 *AGmkBase::getBindedBdatFp() const { return m_createBaseInfo.m_ownerGmkEnemyList->getBindedBdatFp(); }

bool AGmkBase::canCreateGameEntity() const {
  const GmkSet *set = m_createBaseInfo.m_ownerGmkEnemyList->getCreateInfo().m_gmkSet;
  if (set == nullptr) {
    return true;
  }
  return !set->m_createInfo.unknown24;
}

f32 AGmkBase::getYSnapRayLength() const {
  switch (m_createBaseInfo.unknown10->unknown0c) {
  case SHAPE_TYPE_UNKNOWN_1:
  case SHAPE_TYPE_UNKNOWN_3:
    return m_createBaseInfo.m_xform->unknown20.y;
  case SHAPE_TYPE_UNKNOWN_2:
    return m_createBaseInfo.m_xform->unknown20.x;
  case SHAPE_TYPE_UNKNOWN_4:
    return m_createBaseInfo.m_xform->unknown20.x + m_createBaseInfo.m_xform->unknown20.y;
  default:
    return 1.0f;
  }
}

bool AGmkBase::getYSnapPosInShape(mm::Vec3 &position) const {
  fw::ColiCheckConfig config;
  mm::Vec3 shapePosition;
  getPositionInShape(shapePosition, false);
  shapePosition.y += m_createBaseInfo.m_xform->unknown20.y * 0.5f;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = true;
  config.unknown15 = false;
  config.unknown10 = 2;
  config.unknown04 = 0x80000020;
  config.unknown00 = 9;
  return getYSnapPos(position, shapePosition, m_createBaseInfo.m_xform->unknown20.y, config);
}

bool AGmkBase::getPositionAppliedYSnap(mm::Vec3 &result, const mm::Vec3 &position, bool isXformY) const {
  f32 halfLength = getYSnapRayLength() * 0.5f;
  fw::ColiCheckConfig config;
  mm::Vec3 start;
  start.x = position.x;
  start.y = halfLength + (isXformY ? m_createBaseInfo.m_xform->unknown00 : position).y;
  start.z = position.z;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown15 = false;
  config.unknown14 = true;
  config.unknown10 = 2;
  config.unknown04 = 0x80000020;
  config.unknown00 = 9;
  return getYSnapPos(result, start, halfLength + halfLength, config);
}

void AGmkBase::createBase(const CreateBaseInfo &info) { m_createBaseInfo = info; }

void AGmkBase::bindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  gf::GfObjAcc acc(handle);
  acc.setUserData(gf::OBJ_USER_DATA_UNKNOWN_0, reinterpret_cast<u64>(this));
}

void AGmkBase::unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  if (handle == gf::unknown020) {
    return;
  }
  gf::GfObjAcc acc(handle);
  if (acc.isValid()) {
    acc.setUserData(gf::OBJ_USER_DATA_UNKNOWN_0, 0);
  }
}

int AGmkBase::findBdatRowIndex() const {
  u8 *bdat = getBindedBdatFp();
  const char *name = m_createBaseInfo.unknown10->unknown00;
  if (name[0] == '\0') {
    return -1;
  }
  int top = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  for (int id = top; id < top + count; id++) {
    const char *rowName = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, BDAT_TYPE_UNKNOWN_7));
    if (rowName != nullptr && __builtin_strcmp(rowName, name) == 0) {
      return id;
    }
  }
  return -1;
}

void AGmkBase::update(f32 deltaTime) { debugUpdateMmf(); }

void AGmkBase::debugDraw() const {
  if (!isValid()) {
    return;
  }
}

void AGmkBase::onGobEvent(gf::IGfObjListener::OBJEVT event, gf::GF_OBJ_HANDLE *handle) {
  if (event != gf::IGfObjListener::OBJEVT_UNKNOWN_3) {
    return;
  }
  unbindToGameObj(handle);
}

} // namespace gmk

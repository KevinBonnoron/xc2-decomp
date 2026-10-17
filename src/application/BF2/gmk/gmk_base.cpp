#include "gmk/gmk_base.h"
#include "bdat.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"

namespace gmk {

AGmkBase::AGmkBase() : baseInfo(), _40() {}

void AGmkBase::disposeBase() {
  baseInfo.list = nullptr;
  baseInfo.xform = nullptr;
  baseInfo.gobInfo = nullptr;
}

u8 *AGmkBase::getBindedBdatFp() const { return baseInfo.list->getBindedBdatFp(); }

bool AGmkBase::canCreateGameEntity() const {
  const GmkSet *set = baseInfo.list->getCreateInfo().set;
  if (set == nullptr) {
    return true;
  }
  return !set->createInfo.isGameEntityDisabled;
}

f32 AGmkBase::getYSnapRayLength() const {
  switch (baseInfo.gobInfo->shapeType) {
  case SHAPE_TYPE_POINT:
  case SHAPE_TYPE_BOX:
    return baseInfo.xform->scale.y;
  case SHAPE_TYPE_SPHERE:
    return baseInfo.xform->scale.x;
  case SHAPE_TYPE_CAPSULE:
    return baseInfo.xform->scale.x + baseInfo.xform->scale.y;
  default:
    return 1.0f;
  }
}

void AGmkBase::createBase(const CreateBaseInfo &info) { baseInfo = info; }

void AGmkBase::bindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  gf::GfObjAcc acc(handle);
  acc.setUserData(gf::OBJ_USER_DATA_GMK, reinterpret_cast<u64>(this));
}

void AGmkBase::unbindToGameObj(gf::GF_OBJ_HANDLE *handle) const {
  if (handle == gf::INVALID_HANDLE) {
    return;
  }
  gf::GfObjAcc acc(handle);
  if (acc.isValid()) {
    acc.setUserData(gf::OBJ_USER_DATA_GMK, 0);
  }
}

int AGmkBase::findBdatRowIndex() const {
  u8 *bdat = getBindedBdatFp();
  const char *name = baseInfo.gobInfo->name;
  if (name[0] == '\0') {
    return -1;
  }
  int top = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  for (int id = top; id < top + count; id++) {
    const char *rowName = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, "name", id, BDAT_TYPE_STRING));
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
  if (event != gf::IGfObjListener::OBJEVT_DESTROY) {
    return;
  }
  unbindToGameObj(handle);
}

} // namespace gmk

#include "gmk/gmk_base.h"
#include "bdat.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list.h"
#include "gmk/gmk_set.h"

namespace gmk {

AGmkBase::AGmkBase() : unknown08(), _40() {}

void AGmkBase::disposeBase() {
  unknown08.unknown00 = nullptr;
  unknown08.unknown08 = nullptr;
  unknown08.unknown10 = nullptr;
}

u8 *AGmkBase::getBindedBdatFp() const { return unknown08.unknown00->getBindedBdatFp(); }

bool AGmkBase::canCreateGameEntity() const {
  const GmkSet *set = unknown08.unknown00->getCreateInfo().unknown08;
  if (set == nullptr) {
    return true;
  }
  return !set->unknown10.unknown24;
}

f32 AGmkBase::getYSnapRayLength() const {
  switch (unknown08.unknown10->unknown0c) {
  case SHAPE_TYPE_POINT:
  case SHAPE_TYPE_BOX:
    return unknown08.unknown08->unknown20.y;
  case SHAPE_TYPE_SPHERE:
    return unknown08.unknown08->unknown20.x;
  case SHAPE_TYPE_CAPSULE:
    return unknown08.unknown08->unknown20.x + unknown08.unknown08->unknown20.y;
  default:
    return 1.0f;
  }
}

void AGmkBase::createBase(const CreateBaseInfo &info) { unknown08 = info; }

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
  const char *name = unknown08.unknown10->unknown00;
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

#include "gf/event/gf_evt_model.h"

#include "gf/object/gf_obj_util.h"

namespace gf {

const mm::mtl::RTTI *GfEvtModel::getRTTI() const { return &m_rtti; }

bool GfEvtModel::isValid() const { return GfObjUtil::isValid(unknown20); }

void GfEvtModel::update(const fw::UpdateInfo &) {}

GF_OBJ_HANDLE *GfEvtModel::getWeaponHandleRight() const { return reinterpret_cast<GF_OBJ_HANDLE *>(-1); }

GF_OBJ_HANDLE *GfEvtModel::getWeaponHandleLeft() const { return reinterpret_cast<GF_OBJ_HANDLE *>(-1); }

void GfEvtModel::setDispWeapon(bool) {}

void GfEvtModel::setDispWeapon(bool, bool) {}

void GfEvtModel::setWeaponBattleCommand() {}

void GfEvtModel::setWeaponFieldCommand() {}

void GfEvtModel::setWeaponBattleState() {}

void GfEvtModel::setWeaponFieldState() {}

void GfEvtModel::setWeaponBattleMount() {}

void GfEvtModel::setWeaponFieldMount() {}

} // namespace gf

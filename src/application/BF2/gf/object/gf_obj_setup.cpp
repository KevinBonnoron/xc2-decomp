#include "gf/object/gf_obj_setup.h"

#include "gf/data/gf_data_obj.h"

namespace gf {

const mm::mtl::RTTI *GfObjSetup::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupMap::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupBlade::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupMob::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupNpc::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupGimmick::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupBelonging::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupEnWeapon::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupEventObj::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupExtra::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupFieldObj::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupMapLodAnim::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupMapObj::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupUiObj::getRTTI() const { return &m_rtti; }

u32 GfObjSetup::getFootStep() const {
  if (unknown08 == OBJECT_TYPE_DRIVER) {
    DataObjDriver driver(unknown10);
    return driver.getFootStep();
  }
  if (unknown08 == OBJECT_TYPE_BLADE) {
    DataObjBlade blade(unknown10);
    return blade.getFootStep();
  }
  return 0;
}

u32 GfObjSetup::getFootStepEffect() const {
  if (unknown08 == OBJECT_TYPE_DRIVER) {
    DataObjDriver driver(unknown10);
    return driver.getFootStepEffect();
  }
  if (unknown08 == OBJECT_TYPE_BLADE) {
    DataObjBlade blade(unknown10);
    return blade.getFootStepEffect();
  }
  return 1;
}

u32 GfObjSetup::getEnArrangeID() const { return 0; }

void GfObjSetup::setInitialScale(f32 scale) {
  unknown40 = scale;
  unknown44 = scale;
  unknown48 = scale;
}

void GfObjSetup::setInitialScale(const mm::Vec3 &scale) {
  unknown40 = scale.x;
  unknown44 = scale.y;
  unknown48 = scale.z;
}

void setSkelType(u32 type, GfObjSetup *setup) {
  s32 skelType;
  switch (type) {
  case 1:
    skelType = 0;
    break;
  case 2:
    skelType = 4;
    break;
  case 3:
    skelType = 1;
    break;
  case 4:
    skelType = 3;
    break;
  case 5:
    skelType = 5;
    break;
  case 6:
    skelType = 6;
    break;
  case 7:
    skelType = 7;
    break;
  case 8:
    skelType = 8;
    break;
  case 9:
    skelType = 9;
    break;
  case 10:
    skelType = 10;
    break;
  default:
    skelType = -1;
    break;
  }
  setup->unknown68 = skelType;
}

} // namespace gf

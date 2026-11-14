#include "gf/object/gf_obj_setup.h"

#include <math.h>

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_obj.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"

namespace gf {

const mm::mtl::RTTI *GfObjSetup::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupMap::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupBlade::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupDriver::getRTTI() const { return &m_rtti; }

const mm::mtl::RTTI *GfObjSetupWeapon::getRTTI() const { return &m_rtti; }

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
  if (unknown08 == OBJECT_TYPE_PC) {
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
  if (unknown08 == OBJECT_TYPE_PC) {
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

void GfObjSetupEnemy::validateBy_pop_act_type(u8 popActType) {
  switch (popActType) {
  default:
    unknown74 = "S_idle";
    break;
  case 0:
    unknown74 = "S_idle";
    break;
  case 1:
    unknown74 = "S_specialA_01";
    break;
  case 2:
    unknown74 = "S_specialB_01";
    break;
  case 3:
    unknown74 = "S_specialC_00";
    break;
  case 4:
    unknown74 = "S_specialD_00";
    break;
  }
  unknown98 = popActType != 3 && popActType != 4;
}

u32 GfObjSetupEnemy::getFootStep() const {
  DataObjEnemy enemy(getEnArrangeID());
  return enemy.getFootStep();
}

u32 GfObjSetupEnemy::getFootStepEffect() const {
  DataObjEnemy enemy(getEnArrangeID());
  return enemy.getFootStepEffect();
}

const mm::mtl::RTTI *GfObjSetupEnemy::getRTTI() const { return &m_rtti; }

u32 GfObjSetupEnemy::getEnArrangeID() const { return m_enArrangeID; }

GfObjSetupEnemy::~GfObjSetupEnemy() {
  if (unknowna0 != nullptr) {
    delete unknowna0;
    unknowna0 = nullptr;
  }
  if (unknownc0 != nullptr) {
    delete unknownc0;
    unknownc0 = nullptr;
  }
}

void GfObjSetup::setInitialTransform(const fw::Transform &transform) {
  unknown20.x = transform.unknown00.x;
  unknown20.y = transform.unknown00.y;
  unknown20.z = transform.unknown00.z;
  mm::quatToEuler(transform.unknown10, unknown30);
}

void GfObjSetup::setInitialTransform(const mm::Mat44 &matrix) {
  unknown20 = matrix.unknown004();
  mm::Mat44 rotation;
  for (int i = 0; i < 3; i++) {
    f32 length = sqrtf(matrix.rows[i][0] * matrix.rows[i][0] + matrix.rows[i][1] * matrix.rows[i][1] + matrix.rows[i][2] * matrix.rows[i][2]);
    rotation.rows[i][0] = matrix.rows[i][0] / length;
    rotation.rows[i][1] = matrix.rows[i][1] / length;
    rotation.rows[i][2] = matrix.rows[i][2] / length;
  }
  mm::unknown002(rotation, unknown30);
  unknown30.x = -unknown30.x;
  unknown30.y = -unknown30.y;
  unknown30.z = -unknown30.z;
}

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

GfObjSetupDriver *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamDriver &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupDriver *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupDriver(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown1a0;
  if (param.unknown80) {
    setup->unknown20.x = param.unknown60.x;
    setup->unknown20.y = param.unknown60.y;
    setup->unknown20.z = param.unknown60.z;
    setup->unknown30.x = param.unknown70.x;
    setup->unknown30.y = param.unknown70.y;
    setup->unknown30.z = param.unknown70.z;
  }
  return setup;
}

GfObjSetupBlade *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamBlade &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupBlade *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupBlade(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown98;
  return setup;
}

GfObjSetupMap *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMapSeamless &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 166 as in the original file: it is the line argument of the allocation.
#line 166
  GfObjSetupMap *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupMap(param);
  info->unknown30 = setup;
  if (!param.unknown90) {
    setup->unknown6c = param.m_bladeID;
  } else {
    setup->unknown70 = param.m_bladeID;
  }
  if (param.unknown98 != nullptr) {
    setup->unknown74 = true;
  }
  setup->unknown75 = true;
  return setup;
}

GfObjSetupMap *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMap &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 188 as in the original file: it is the line argument of the allocation.
#line 188
  GfObjSetupMap *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupMap(param);
  info->unknown30 = setup;
  setup->unknown74 = true;
  return setup;
}

GfObjSetupMapLodAnim *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMapLodAnim &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupMapLodAnim *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupMapLodAnim(param);
  info->unknown30 = setup;
  return setup;
}

GfObjSetupEnemy *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamEnemy &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 216 as in the original file: it is the line argument of the allocation.
#line 216
  GfObjSetupEnemy *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupEnemy(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown98;
  setup->m_enArrangeID = param.m_enArrangeID != 0 ? param.m_enArrangeID : 1;
  if (param.unknowna8 != 0) {
    setup->unknowna8 = param.unknowna8;
  }
  // __LINE__ must be 227 as in the original file: it is the line argument of the allocation.
#line 227
  setup->unknowna0 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SDataEnemy(setup->m_enArrangeID, param.unknownac);
  GfObjSetupEnemy *owner = GfObjUtil::getObjSetup<GfObjSetupEnemy>(param.unknown38);
  if (owner != nullptr && setup->unknowna0->unknown41 != 0) {
    owner->unknowna0->unknown41 = setup->unknowna0->unknown41;
  }
  return setup;
}

GfObjSetupNpc *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamNpc &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupNpc *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupNpc(param);
  info->unknown30 = setup;
  setup->unknown90 = param.unknown98;
  return setup;
}

GfObjSetupMob *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMob &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupMob *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupMob(param);
  info->unknown30 = setup;
  if (setup->unknown10 != 0) {
    u8 race = Bdat::getValCheck(GfDataBdat::getFP(BDAT_RSC_MOB_LIST), "Race", param.m_bladeID, 1);
    switch (race) {
    case 1:
      setup->unknown68 = 0;
      break;
    case 3:
      setup->unknown68 = 1;
      break;
    default:
      setup->unknown68 = -1;
      break;
    }
  }
  return setup;
}

GfObjSetupGimmick *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamGimmick &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupGimmick *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupGimmick(param);
  info->unknown30 = setup;
  setup->unknown98 = param.unknown90;
  return setup;
}

GfObjSetupMapObj *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamMapObj &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 309 as in the original file: it is the line argument of the allocation.
#line 309
  GfObjSetupMapObj *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupMapObj(param);
  info->unknown30 = setup;
  return setup;
}

GfObjSetupFieldObj *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamFobj &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupFieldObj *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupFieldObj(param);
  info->unknown30 = setup;
  mm::mtl::FixStr<16> column;
  column.format("paramid%d", param.unknown94);
  setup->unknown6c = static_cast<u16>(param.unknown18->getValCheck(column.c_str(), param.m_bladeID, 2));
  setup->unknown10 = param.m_bladeID;
  return setup;
}

GfObjSetupWeapon *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamWeapon &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  GfObjSetupWeapon *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupWeapon(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown94;
  setup->unknown74 = param.unknown98.getMountIndex();
  setup->unknown78 = param.unknown98.unknown80;
  return setup;
}

GfObjSetupEnWeapon *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamEnWeapon &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 360 as in the original file: it is the line argument of the allocation.
#line 360
  GfObjSetupEnWeapon *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupEnWeapon(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown98.getMountIndex();
  return setup;
}

GfObjSetupBelonging *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamBelonging &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 375 as in the original file: it is the line argument of the allocation.
#line 375
  GfObjSetupBelonging *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupBelonging(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown90.getMountIndex();
  setup->unknown50 = param.unknown130 ? 1.0f : 0.0f;
  return setup;
}

GfObjSetupExtra *GfObjSetup::createSetupParam(GF_OBJ_HANDLE *handle, const GfInitParamExtra &param) {
  GFOBJ_INFO *info = GfObjManager::getObjInfo(handle);
  // __LINE__ must be 391 as in the original file: it is the line argument of the allocation.
#line 391
  GfObjSetupExtra *setup = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfObjSetupExtra(param);
  info->unknown30 = setup;
  setup->unknown6c = param.unknown90.getMountIndex();
  return setup;
}

GfObjSetupEnemy::GfObjSetupEnemy(const GfInitParamEnemy &param)
    : GfObjSetup(param, OBJECT_TYPE_ENEMY), unknown6c(param.m_enArrangeID), m_enArrangeID(param.unknown98), unknown98(false), unknowna0(nullptr), unknowna8(0), unknownac(0.0f), unknownb0(0),
      unknownb2(false), unknownb4(0), unknownb8(param.m_bladeID), unknownc0(nullptr) {
  unknown74 = "S_idle";
  if (unknownb8 != 0) {
    // __LINE__ must be 662 as in the original file: it is the line argument of the allocation.
#line 662
    unknownc0 = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) SDataBlade;
    GfDataBlade::setupSDataBlade(*unknownc0, unknownb8, false);
  }
}

GfObjSetupBlade::GfObjSetupBlade(const GfInitParamBlade &param) : GfObjSetup(param, OBJECT_TYPE_BLADE), unknown6c(-1), unknown70(false), unknown74(-1) {
  unknown71 = GfGameUtil::isCondBladeModel(param.m_bladeID);
  unknown80 = param;
}

} // namespace gf

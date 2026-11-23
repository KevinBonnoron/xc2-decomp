#include "gf/camera/chain_attack/gf_camera_chain_attack.h"

#include <math.h>

#include "bdat.h"
#include "fw/fw_camera.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/camera/gf_camera_utilities.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "ml/rand.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

// Inferred role: moves a point of the camera in front of the collision of the level when it is not at the position; original name unknown. Helper for the
// four identical blocks of ChainAttackCamera::change (0x71001d4210); the four blocks written out also match (212 instructions), the helper is the shorter form.
static inline void unknown002(const ChainAttackCamera &camera, mm::Vec3 &point, const mm::Vec3 &position) {
  if (!(fabsf(position.x - point.x) <= 0.000001f) || !(fabsf(position.y - point.y) <= 0.000001f) || !(fabsf(position.z - point.z) <= 0.000001f)) {
    CameraUtilities::updateCollision(camera.m_coliCheckConfig, point, position, 45.0f, 0.4f);
  }
}

ChainAttackCameraEntity::~ChainAttackCameraEntity() {}

void ChainAttackCameraEntity::onActivate() {}

void ChainAttackCameraEntity::calcSpeedTypeLinearSpacing() {
  f32 rate = unknown11c / unknown114;
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::calcSpeedTypeFastOut() {
  f32 rate = fastOut(unknown11c / unknown114);
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::calcSpeedTypeSlowOut() {
  f32 rate = slowOut(unknown11c / unknown114);
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::calcSpeedTypeFastInFastOut() {
  f32 rate = fastInFastOut(unknown11c / unknown114);
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ChainAttackCameraEntity::update(const fw::UpdateInfo &info) {
  if (unknown110 > 0.0f) {
    unknownf0 = unknownf0 + (unknownd0 - unknownf0) * unknown110;
    unknown100 = unknown100 + (unknowne0 - unknown100) * unknown110;
  } else if (unknown114 > 0.0f) {
    // The game dispatches on m_moveType through a jump table of four entries (1.0.0: `cmp w8, #3` at 0x71001d225c, table at 0x7100f68fa8) whose entries 0 and "above 3" reach the same block
    // (0x71001d227c). Only two separate cases with the same body give that table: `case 0:` stacked on `default:` (in either order), a switch without case 0 and an if chain all compile to a compare
    // chain (194 or 192 instructions against the game's 197). The game calls calcSpeedTypeSlowInSlowOut (0x71001d22ec, 0x1fc bytes) and inlines the other three.
    switch (m_moveType) {
    case 0:
      calcSpeedTypeLinearSpacing();
      break;
    case 1:
      calcSpeedTypeSlowInSlowOut();
      break;
    case 2:
      calcSpeedTypeFastOut();
      break;
    case 3:
      calcSpeedTypeSlowOut();
      break;
    default:
      calcSpeedTypeLinearSpacing();
      break;
    }
    unknown11c += info.unknown04 / (1.0f / 30.0f);
    if (unknown114 < unknown11c) {
      unknown11c = unknown114;
    }
  }
  setLookAt(unknownf0, unknown100, 0.0f);
}

f32 ChainAttackCameraEntity::curve(f32 a, f32 b, f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return (1.0f - x) * a + x * b;
}

f32 ChainAttackCameraEntity::slowOut(f32 t) {
  f32 x = sinf((1.0f - t) * 1.5707964f + 4.712389f) + 1.0f;
  return 1.0f - (x + (1.0f - x) * 0.0f);
}

f32 ChainAttackCameraEntity::fastOut(f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return x + (1.0f - x) * 0.0f;
}

f32 ChainAttackCameraEntity::fastInFastOut(f32 t) { return (tanf(t * 1.8849556f + 2.1991148f) + 1.38f) / 2.76f; }

void ChainAttackCameraEntity::setPlayTimeRate(f32 rate) {
  unknown110 = rate;
  unknown114 = 0.0f;
  unknown11c = 0.0f;
}

void ChainAttackCameraEntity::setPlayTimeDuration(f32 duration) {
  unknown110 = 0.0f;
  unknown114 = duration;
  unknown11c = 0.0f;
}

void ChainAttackCameraEntity::setMoveType(int moveType) { m_moveType = moveType; }

const mm::mtl::RTTI *ChainAttackCameraEntity::getRTTI() const { return &m_rtti; }

const char *ChainAttackCameraEntity::getName() const { return "ChainAttackCameraEntity"; }

ChainAttackCamera::ChainAttackCamera() : unknown70(0xf), m_GF_OBJ_HANDLE(unknown020) {
  m_coliCheckConfig.unknown08 = 0.0f;
  m_coliCheckConfig.unknown0c = 0.0f;
  m_coliCheckConfig.unknown14 = false;
  m_coliCheckConfig.unknown15 = false;
  m_coliCheckConfig.unknown10 = 1;
  m_coliCheckConfig.unknown00 = 9;
  m_coliCheckConfig.unknown04 = -9;
}

ChainAttackCamera::~ChainAttackCamera() {}

void ChainAttackCamera::start() {}

void ChainAttackCamera::end() { destroyCamera(&unknown08, 0.0f); }

void ChainAttackCamera::destroyCamera(mm::mtl::IntrusivePtr<fw::Camera> *camera, f32 time) {
  if (camera->get() != nullptr) {
    if (!(*camera)->unknowna0) {
      *camera = nullptr;
    } else {
      fw::CameraManager::get()->unknown20[0].pop(*camera, time);
      *camera = nullptr;
    }
  }
}

void ChainAttackCamera::setCameraParam(const Param &param) {
  ChainAttackCameraEntity *entity = static_cast<ChainAttackCameraEntity *>(unknown08.get());
  if (entity != nullptr && entity->unknowna0) {
    if (param.unknown00 != 0) {
      entity->setPlayTimeDuration(param.unknown04);
    } else {
      entity->setPlayTimeRate(param.unknown04 * 0.0001f);
    }
    entity->setMoveType(param.unknown08);
    entity->setPoint(param.unknown10, param.unknown20, param.unknown40, param.unknown50);
  }
}

u32 ChainAttackCamera::lottery(u8 camType) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_CHAIN_ATTACK_CAM);
  s32 top = Bdat::getIdTop(bdat);
  s32 count = Bdat::getIdCount(bdat);
  mm::mtl::FixedVector<u32, 64> candidates;
  for (s32 id = top; id < top + count; id++) {
    u8 enSize = Bdat::getValCheck(bdat, "EnSize", id, gmk::BDAT_TYPE_UNKNOWN_1);
    if ((enSize & unknown70) != 0 && static_cast<u8>(Bdat::getValCheck(bdat, "CamType", id, gmk::BDAT_TYPE_UNKNOWN_1)) == camType) {
      candidates.push_back(id);
    }
  }
  if (candidates.size() == 0) {
    for (s32 id = top; id < top + count; id++) {
      if (static_cast<u8>(Bdat::getValCheck(bdat, "CamType", id, gmk::BDAT_TYPE_UNKNOWN_1)) == camType) {
        candidates.push_back(id);
      }
    }
  }
  int index = ml::mtRand() % candidates.size();
  return candidates[index];
}

void ChainAttackCamera::getParam(int id, Param &param) {
  u8 *bdat = GfDataBdat::getFP(BDAT_BTL_CHAIN_ATTACK_CAM);
  param.unknown00 = Bdat::getValCheck(bdat, "SpeedType", id, gmk::BDAT_TYPE_UNKNOWN_1);
  param.unknown04 = static_cast<u16>(Bdat::getValCheck(bdat, "SpeedNum", id, gmk::BDAT_TYPE_UNKNOWN_2));
  param.unknown08 = Bdat::getValCheck(bdat, "MoveType", id, gmk::BDAT_TYPE_UNKNOWN_1);
  param.unknown09 = Bdat::getValCheck(bdat, "S_LookPosType", id, gmk::BDAT_TYPE_UNKNOWN_1);
  param.unknown10.x = static_cast<s32>(Bdat::getValCheck(bdat, "S_PosX", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown10.y = static_cast<s32>(Bdat::getValCheck(bdat, "S_PosY", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown10.z = static_cast<s32>(Bdat::getValCheck(bdat, "S_PosZ", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown20.x = static_cast<s32>(Bdat::getValCheck(bdat, "S_LookX", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown20.y = static_cast<s32>(Bdat::getValCheck(bdat, "S_LookY", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown20.z = static_cast<s32>(Bdat::getValCheck(bdat, "S_LookZ", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown30 = Bdat::getValCheck(bdat, "E_LookPosType", id, gmk::BDAT_TYPE_UNKNOWN_1);
  param.unknown40.x = static_cast<s32>(Bdat::getValCheck(bdat, "E_PosX", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown40.y = static_cast<s32>(Bdat::getValCheck(bdat, "E_PosY", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown40.z = static_cast<s32>(Bdat::getValCheck(bdat, "E_PosZ", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown50.x = static_cast<s32>(Bdat::getValCheck(bdat, "E_LookX", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown50.y = static_cast<s32>(Bdat::getValCheck(bdat, "E_LookY", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown50.z = static_cast<s32>(Bdat::getValCheck(bdat, "E_LookZ", id, gmk::BDAT_TYPE_UNKNOWN_6));
  param.unknown10 *= 0.01f;
  param.unknown20 *= 0.01f;
  param.unknown40 *= 0.01f;
  param.unknown50 *= 0.01f;
}

void ChainAttackCamera::updateParam(Param &param, const fw::Transform &transform, const mm::Vec3 &position, const mm::Vec3 &target) {
  mm::unknown010(transform.unknown10, param.unknown10);
  mm::unknown010(transform.unknown10, param.unknown20);
  mm::unknown010(transform.unknown10, param.unknown40);
  mm::unknown010(transform.unknown10, param.unknown50);
  param.unknown10 += position;
  param.unknown20 += param.unknown09 == 0 ? position : target;
  param.unknown40 += position;
  param.unknown50 += param.unknown30 == 0 ? position : target;
}

void ChainAttackCamera::change(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
    GfObjAcc acc(handle);
    Param start;
    Param end;
    u32 startId = lottery(0);
    u32 endId = lottery(1);
    getParam(startId, start);
    getParam(endId, end);
    mm::Vec3 position;
    CameraUtilities::getCameraLookBonePosition(handle, position);
    mm::Vec3 look;
    CameraUtilities::getCameraLookBonePosition(m_GF_OBJ_HANDLE, look);
    const fw::Transform &transform = acc.getWorldTransform();
    updateParam(start, transform, position, look);
    updateParam(end, transform, position, look);
    end.unknown10 = start.unknown10;
    end.unknown20 = start.unknown20;
    // The game (0x71001d4210) moves the points in this order: target of the start, target of the end, position of the start, position of the end.
    unknown002(*this, end.unknown20, position);
    unknown002(*this, end.unknown50, position);
    unknown002(*this, end.unknown10, position);
    unknown002(*this, end.unknown40, position);
    setCameraParam(end);
  }
}

} // namespace gf

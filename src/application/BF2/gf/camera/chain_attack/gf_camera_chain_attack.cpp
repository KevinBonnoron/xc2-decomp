#include "gf/camera/chain_attack/gf_camera_chain_attack.h"

#include <math.h>

#include "bdat.h"
#include "fw/fw_camera.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_bdat.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {

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

void ChainAttackCameraEntity::setMoveType(int moveType) { unknown118 = moveType; }

const mm::mtl::RTTI *ChainAttackCameraEntity::getRTTI() const { return &m_rtti; }

const char *ChainAttackCameraEntity::getName() const { return "ChainAttackCameraEntity"; }

ChainAttackCamera::ChainAttackCamera() : unknown70(0xf), unknown78(unknown020) {
  unknown80.unknown08 = 0.0f;
  unknown80.unknown0c = 0.0f;
  unknown80.unknown14 = false;
  unknown80.unknown15 = false;
  unknown80.unknown10 = 1;
  unknown80.unknown00 = 9;
  unknown80.unknown04 = -9;
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

} // namespace gf

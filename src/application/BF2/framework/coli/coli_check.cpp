#include "framework/coli/coli_manager.h"
#include "framework/coli/coli_object.h"
#include "framework/framework.h"
#include "fw/fw_coli_check.h"
#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/rtti.h"
#include "types.h"

namespace fw {

namespace {

// Inferred helper: prepares a collision tester of the idcoli library and its callback for a check; original name unknown.
template <typename Coli> void unknown001(Coli &coli, ColiCheckCallback &callback, const ColiCheckConfig &config, mm::Vec3 *positions, mm::Vec3 *normals) {
  callback.unknown10 = config.unknown15;
  switch (config.unknown10) {
  case 0:
    coli.unknown10.unknown00 = 0;
    break;
  case 1:
    coli.unknown10.unknown00 = 1;
    break;
  case 2:
    coli.unknown10.unknown00 = 2;
    coli.unknown10.unknowne4 = 256;
    coli.unknown10.unknownb8 = positions;
    coli.unknown10.unknownc0 = normals;
    break;
  }
  coli.unknown01 = (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_0) != 0;
  coli.unknown02 = (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_3) != 0;
  coli.unknown00 = (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_1) != 0;
  coli.unknown04 = config.unknown08 * config.unknown08;
  coli.unknown10.unknowne8 = ~config.unknown04;
  coli.unknown10.unknownb3 = config.unknown15;
  coli.unknown08 = &callback;
}

} // namespace

int ColiCheckCallback::m_prevWarningFrame;

void ColiCheckCallback::coli_callback(void *userData) {
  if (unknown08 == nullptr) {
    return;
  }

  if (unknown08->hits.size() == unknown08->hits.capacity()) {
    u32 frame = Framework::getFrameCount();
    // The game keeps this test around the store alone (cmp, b.eq, str at 0x7100157ea0): the warning it guarded, printed once per frame, was stripped from the retail build.
    if (m_prevWarningFrame != frame) {
      m_prevWarningFrame = frame;
    }
    return;
  }

  TColiCheckResult<256>::unknown001 hit;
  hit.position = mm::Vec3::zero;
  hit.normal = mm::Vec3::zero;
  hit.unknown20 = mm::Vec3::zero;
  ColiObject *object = nullptr;
  if (userData != nullptr) {
    ColiObjUserData *data = static_cast<ColiObjUserData *>(userData);
    if (data->getRTTI()->isKindOf(&ColiObjUserData::m_rtti)) {
      object = ColiCheck::getObjectFromUserData(data->unknown08);
    }
  }
  hit.unknown30 = nullptr;
  hit.unknown38 = userData;
  hit.object = object;
  hit.unknown48 = HIT_FLAG_UNKNOWN_2;
  if (object != nullptr) {
    hit.unknown48 |= HIT_FLAG_UNKNOWN_3;
  }
  unknown08->hits.push_back(hit);
  unknown08->hitCount++;
}

ColiObject *ColiCheck::getObjectFromUserData(u32 handle) {
  if (handle != 0) {
    return ColiManager::get()->getObject(handle);
  }

  return nullptr;
}

bool ColiCheck::testLine(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config) {
  result.clear();
  bool isHit = false;
  if (config.unknown00 & (ColiCheckConfig::FLAG_UNKNOWN_0 | ColiCheckConfig::FLAG_UNKNOWN_1 | ColiCheckConfig::FLAG_UNKNOWN_3)) {
    idcoli::IDColiDef coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testLine(start, end);
    result.isHit = isHit;
  }
  if (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_2) {
    idcoli::IDColiPhantom coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    bool isPhantomHit = coli.testLine(start, end);
    result.isHit = isPhantomHit;
    isHit |= isPhantomHit;
  }
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testLineChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiDef coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testLine(start, end);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testLinePhantom(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiPhantom coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testLine(start, end);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testLineColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiCheckObj coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testLine(object, start, end);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testRay(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config) {
  result.clear();
  bool isHit = false;
  if (config.unknown00 & (ColiCheckConfig::FLAG_UNKNOWN_0 | ColiCheckConfig::FLAG_UNKNOWN_1 | ColiCheckConfig::FLAG_UNKNOWN_3)) {
    idcoli::IDColiDef coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testRay(start, direction, length, backLength);
    result.isHit = isHit;
  }
  if (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_2) {
    idcoli::IDColiPhantom coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    bool isPhantomHit = coli.testRay(start, direction, length, backLength);
    result.isHit = isPhantomHit;
    isHit |= isPhantomHit;
  }
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testRayChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiDef coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testRay(start, direction, length, backLength);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testRayPhantom(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiPhantom coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testRay(start, direction, length, backLength);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testRayColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength,
                            const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiCheckObj coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testRay(object, start, direction, length, backLength);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testSphere(TColiCheckResult<256> &result, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  bool isHit = false;
  if (config.unknown00 & (ColiCheckConfig::FLAG_UNKNOWN_0 | ColiCheckConfig::FLAG_UNKNOWN_1 | ColiCheckConfig::FLAG_UNKNOWN_3)) {
    idcoli::IDColiDef coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testSphere(center, radius);
    result.isHit = isHit;
  }
  if (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_2) {
    idcoli::IDColiPhantom coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    bool isPhantomHit = coli.testSphere(center, radius);
    result.isHit = isPhantomHit;
    isHit |= isPhantomHit;
  }
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testSphereChara(TColiCheckResult<256> &result, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiDef coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testSphere(center, radius);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testSpherePhantom(TColiCheckResult<256> &result, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiPhantom coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testSphere(center, radius);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testSphereColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &center, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiCheckObj coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testSphere(object, center, radius);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testCapsule(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  bool isHit = false;
  if (config.unknown00 & (ColiCheckConfig::FLAG_UNKNOWN_0 | ColiCheckConfig::FLAG_UNKNOWN_1 | ColiCheckConfig::FLAG_UNKNOWN_3)) {
    idcoli::IDColiDef coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testCapsule(start, end, radius);
    result.isHit = isHit;
  }
  if (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_2) {
    idcoli::IDColiPhantom coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    bool isPhantomHit = coli.testCapsule(start, end, radius);
    result.isHit = isPhantomHit;
    isHit |= isPhantomHit;
  }
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testCapsuleChara(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiDef coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testCapsule(start, end, radius);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testCapsulePhantom(TColiCheckResult<256> &result, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiPhantom coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testCapsule(start, end, radius);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testCapsuleColi(TColiCheckResult<256> &result, const idcoli::IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, const ColiCheckConfig &config) {
  result.clear();
  idcoli::IDColiCheckObj coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testCapsule(object, start, end, radius);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testObject(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config) {
  result.clear();
  bool isHit = false;
  if (config.unknown00 & (ColiCheckConfig::FLAG_UNKNOWN_0 | ColiCheckConfig::FLAG_UNKNOWN_1 | ColiCheckConfig::FLAG_UNKNOWN_3)) {
    idcoli::IDColiDef coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testCharColiObj(object->m_coliObject, config.unknown0c);
    result.isHit = isHit;
  }
  if (config.unknown00 & ColiCheckConfig::FLAG_UNKNOWN_2) {
    idcoli::IDColiPhantom coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    bool isPhantomHit = coli.testCharColiObj(object->m_coliObject, config.unknown0c);
    result.isHit = isPhantomHit;
    isHit |= isPhantomHit;
  }
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testObjectChara(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config) {
  if (object == nullptr || object->m_coliObject == nullptr) {
    return false;
  }

  result.clear();
  bool isHit;
  if (object->m_coliObject->unknown24 == idcoli::unknown098_1) {
    idcoli::IDColiDef coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testCharColiObj(object->m_coliObject, config.unknown0c);
  } else {
    idcoli::IDColiPhantom coli;
    ColiCheckCallback callback(result);
    mm::Vec3 positions[256];
    mm::Vec3 normals[256];
    unknown001(coli, callback, config, positions, normals);
    isHit = coli.testPhantomColiObj(object->m_coliObject, config.unknown0c);
  }
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::testObjectPhantom(TColiCheckResult<256> &result, ColiObject *object, const ColiCheckConfig &config) {
  if (object == nullptr || object->m_coliObject == nullptr) {
    return false;
  }

  result.clear();
  idcoli::IDColiPhantom coli;
  ColiCheckCallback callback(result);
  mm::Vec3 positions[256];
  mm::Vec3 normals[256];
  unknown001(coli, callback, config, positions, normals);
  bool isHit = coli.testCharColiObj(object->m_coliObject, config.unknown0c);
  result.isHit = isHit;
  return isHit;
}

bool ColiCheck::moveColi(mm::Vec3 &result, const mm::Vec3 &position, const mm::Vec3 &move) {
  idcoli::IDColiMove coliMove;
  if (coliMove.moveColi(position, move)) {
    result = coliMove.unknown130;
    return true;
  }

  result = mm::Vec3::zero;
  return false;
}

} // namespace fw

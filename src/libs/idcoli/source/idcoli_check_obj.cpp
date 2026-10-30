#include "idcoli/idcoli.h"
#include "idcoli/idcoli_util_coli.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace idcoli {

IDColiCheckObj::IDColiCheckObj() {
  unknown00 = false;
  unknown04 = 0.0f;
  unknown01 = true;
  unknown02 = true;
  unknown08 = nullptr;
}

bool IDColiCheckObj::testLine(const IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiInput input;
  IDColiInputUtil::getLine(input, start, end, true);
  input.unknowna0 = unknown04;
  IDColiObj *target = const_cast<IDColiObj *>(object);
  unknown10.unknownf8 = target;
  unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
  bool isHit = false;
  switch (object->unknown24) {
  case unknown098_1:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testCheckLine(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testResultLine(unknown10, input);
    }
    break;
  case unknown098_2:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testCheckLine(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testResultLine(unknown10, input);
    }
    break;
  case unknown098_3:
    isHit = static_cast<IDColiObjGrand *>(target)->unknown051(unknown10, input);
    break;
  }
  if (isHit && unknown10.unknown00 == 1 && unknown08 != nullptr) {
    unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
  }
  return isHit;
}

bool IDColiCheckObj::testRay(const IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiInput input;
  IDColiInputUtil::getRay(input, start, direction, length, -backLength, true);
  input.unknowna0 = unknown04;
  IDColiObj *target = const_cast<IDColiObj *>(object);
  unknown10.unknownf8 = target;
  unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
  bool isHit = false;
  switch (object->unknown24) {
  case unknown098_1:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testCheckRay(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testResultRay(unknown10, input);
    }
    break;
  case unknown098_2:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testCheckRay(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testResultRay(unknown10, input);
    }
    break;
  case unknown098_3:
    isHit = static_cast<IDColiObjGrand *>(target)->unknown052(unknown10, input);
    break;
  }
  if (isHit && unknown10.unknown00 == 1 && unknown08 != nullptr) {
    if (unknown10.unknownb0) {
      unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
    }
    if (unknown10.unknownb1) {
      unknown08->unknown01(unknown10.unknowna8, &unknown10.unknown50);
    }
  }
  // Returns false even after a hit (original bug, reproduced).
  return false;
}

bool IDColiCheckObj::testSphere(const IDColiObj *object, const mm::Vec3 &center, f32 radius) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiInput input;
  IDColiInputUtil::getSphere(input, center, radius, true);
  input.unknowna0 = unknown04;
  IDColiObj *target = const_cast<IDColiObj *>(object);
  unknown10.unknownf8 = target;
  unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
  bool isHit = false;
  switch (object->unknown24) {
  case unknown098_1:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testCheckSphere(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testResultSphere(unknown10, input);
    }
    break;
  case unknown098_2:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testCheckSphere(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testResultSphere(unknown10, input);
    }
    break;
  case unknown098_3:
    isHit = static_cast<IDColiObjGrand *>(target)->unknown053(unknown10, input, false);
    break;
  }
  if (isHit && unknown10.unknown00 == 1 && unknown08 != nullptr) {
    unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
  }
  return isHit;
}

bool IDColiCheckObj::testCapsule(const IDColiObj *object, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius) {
  unknown10.unknown030();
  unknown10.unknownf8 = nullptr;
  unknown10.unknown100 = unknown08;
  IDColiInput input;
  IDColiInputUtil::getCapsule(input, start, end, radius, true);
  input.unknowna0 = unknown04;
  IDColiObj *target = const_cast<IDColiObj *>(object);
  unknown10.unknownf8 = target;
  unknown10.unknownf0 = reinterpret_cast<u64>(object->unknown48);
  bool isHit = false;
  switch (object->unknown24) {
  case unknown098_1:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testCheckCapsule(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjCharCheck *>(target)->testResultCapsule(unknown10, input);
    }
    break;
  case unknown098_2:
    if (unknown10.unknown00 == 0) {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testCheckCapsule(unknown10, input);
    } else {
      isHit = static_cast<IDColiObjPhantomCheck *>(target)->testResultCapsule(unknown10, input);
    }
    break;
  case unknown098_3:
    isHit = static_cast<IDColiObjGrand *>(target)->unknown054(unknown10, input, false);
    break;
  }
  if (isHit && unknown10.unknown00 == 1 && unknown08 != nullptr) {
    unknown08->unknown01(unknown10.unknown98, &unknown10.unknown10);
  }
  return isHit;
}

} // namespace idcoli

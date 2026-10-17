#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

class IDColiResult;
struct CLBoxWork;

struct CLSphereWork {
  mm::Vec3 center;
  u8 _0c[0x10 - 0xc];
  f32 radius;
};

struct CLCapsuleWork {
  u8 _00[0x5c];
};

struct CLLineWork {
  u8 _00[0x70];
};

struct CLRayWork {
  CLLineWork lines[2];
};

struct IDColiInput {
  const CLBoxWork *getBox() const { return reinterpret_cast<const CLBoxWork *>(&ray); }

  u8 _00[0xb0];
  union {
    CLSphereWork sphere;
    CLCapsuleWork capsule;
    CLLineWork line;
    CLRayWork ray;
  };
};

static_assert(offsetof(IDColiInput, ray) == 0xb0, "");

class IDColiUtilColiResult {
public:
  static bool isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsulePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isPartsLineSphere(IDColiResult &result, const CLLineWork *line, const void *data, bool isBack);
  static bool isPartsLineBox(IDColiResult &result, const CLLineWork *line, const void *data, bool isBack, bool isIn);
  static bool isPartsLineCapsule(IDColiResult &result, const CLLineWork *line, const void *data, bool isBack, bool isIn);
  static bool isLineSphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineInCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLinePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRaySphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayInCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayPoli(IDColiResult &result, const IDColiInput &input, const void *data);
};

class IDColiUtilColiSimple {
public:
  static bool isSphereBox(IDColiResult &result, const CLSphereWork *sphere, const CLBoxWork *box);
  static bool isSphereBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleBox(IDColiResult &result, const CLCapsuleWork *capsule, const CLBoxWork *box);
  static bool isCapsuleBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleInBox(IDColiResult &result, const CLCapsuleWork *capsule, const CLBoxWork *box);
  static bool isCapsuleInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsulePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isBoxSphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isBoxBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isBoxCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isBoxPoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isPartsLineBox(IDColiResult &result, const CLLineWork *line, const void *data, bool isIn);
  static bool isPartsLineCapsule(IDColiResult &result, const CLLineWork *line, const void *data, bool isIn);
  static bool isLineBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLinePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isLineInCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayInCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRayPoli(IDColiResult &result, const IDColiInput &input, const void *data);
};

} // namespace idcoli

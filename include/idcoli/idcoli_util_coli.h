#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

struct unknown005 {
  virtual void unknown00(u64 value) {} // Inferred role: result callback; original name unknown.
};

class IDColiResult {
public:
  // Inferred helper: notifies the callback of a hit and returns true; original name unknown.
  bool unknown001() {
    if (unknown100 != nullptr) {
      unknown100->unknown00(unknownf0);
    }
    return true;
  }

  u8 _00[0xe8];
  u32 unknowne8; // Inferred role: material bits to skip; original member name unknown.
  u8 _ec[0xf0 - 0xec];
  u64 unknownf0; // Inferred role: callback argument; original member name unknown.
  u8 _f8[0x100 - 0xf8];
  unknown005 *unknown100; // Inferred role: callback; original member name unknown.
};

static_assert(offsetof(IDColiResult, unknowne8) == 0xe8, "");
static_assert(offsetof(IDColiResult, unknownf0) == 0xf0, "");
static_assert(offsetof(IDColiResult, unknown100) == 0x100, "");

struct CLBoxWork {
  u8 _00[0x30];
  mm::Vec3 unknown30; // Inferred role: first axis; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: second axis; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: third axis; original member name unknown.
  mm::Vec3 unknown60; // Inferred role: center; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: half size; original member name unknown.
  mm::Vec3 unknown80; // Inferred role: max; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: min; original member name unknown.
  u8 _a0[0xa4 - 0xa0];
  f32 unknowna4; // Inferred role: scale; original member name unknown.
};

static_assert(offsetof(CLBoxWork, unknown30) == 0x30, "");
static_assert(offsetof(CLBoxWork, unknown90) == 0x90, "");
static_assert(offsetof(CLBoxWork, unknowna4) == 0xa4, "");

struct CLSphereWork {
  mm::Vec3 unknown00; // Inferred role: center; original member name unknown.
  f32 unknown10;      // Inferred role: radius; original member name unknown.
};

struct CLCapsuleWork {
  mm::Vec3 unknown00; // Inferred role: start point; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: end point; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: direction; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: max; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: min; original member name unknown.
  f32 unknown50;      // Inferred role: radius; original member name unknown.
  u8 _54[0x58 - 0x54];
  f32 unknown58; // Inferred role: inverse squared length; original member name unknown.
};

static_assert(offsetof(CLCapsuleWork, unknown50) == 0x50, "");
static_assert(offsetof(CLCapsuleWork, unknown58) == 0x58, "");

struct CLLineWork {
  mm::Vec3 unknown00; // Inferred role: start point; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: end point; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: direction; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: unit direction; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: max; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: min; original member name unknown.
  f32 unknown60;      // Inferred role: squared length; original member name unknown.
  f32 unknown64;      // Inferred role: length; original member name unknown.
};

static_assert(offsetof(CLLineWork, unknown60) == 0x60, "");

struct CLRayWork {
  CLLineWork unknown00[2]; // Inferred role: lines; original member name unknown.
};

struct IDColiInput {
  const CLBoxWork *getBox() const { return &box; }

  mm::Vec3 unknown00; // Inferred role: max; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: min; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: shape position; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: line direction; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: center; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: half size; original member name unknown.
  mm::Vec3 unknown60; // Inferred role: absolute half size plus epsilon; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: line start point; original member name unknown.
  mm::Vec3 unknown80; // Inferred role: line end point; original member name unknown.
  f32 unknown90;      // Inferred role: radius; original member name unknown.
  f32 unknown94;      // Inferred role: squared radius; original member name unknown.
  f32 unknown98;      // Inferred role: line length; original member name unknown.
  u8 _9c[0xa0 - 0x9c];
  f32 unknowna0;    // Inferred role: squared range; original member name unknown.
  s16 unknowna4[6]; // Inferred role: tree bounds, max then min; original member name unknown.
  union {
    CLBoxWork box;
    CLSphereWork sphere;
    CLCapsuleWork capsule;
    CLLineWork line;
    CLRayWork ray;
  };
};

static_assert(offsetof(IDColiInput, ray) == 0xb0, "");
static_assert(offsetof(IDColiInput, unknowna4) == 0xa4, "");

typedef u32 (*unknown004)(IDColiResult &, const IDColiInput &, const void *);  // Inferred role: result collision test function; original name unknown.
typedef bool (*unknown009)(IDColiResult &, const IDColiInput &, const void *); // Inferred role: simple collision test function; original name unknown.

class IDColiInputUtil {
public:
  static void calcTreeAABB(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min);
  static void getAaBb(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min);
  static void getBox(IDColiInput &input, const CLBoxWork &box);
  static void getSphere(IDColiInput &input, const mm::Vec3 &center, f32 radius, bool isTree);
};

class IDColiUtilColiResult {
public:
  static const unknown004 s_CallLine[5];
  static const unknown004 s_CallRay[5];
  static const unknown004 s_CallSphere[5];
  static const unknown004 s_CallCapsule[5];

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
  static const unknown009 s_CallLine[5];
  static const unknown009 s_CallRay[5];
  static const unknown009 s_CallSphere[5];
  static const unknown009 s_CallCapsule[5];
  static const unknown009 s_CallBox[5];

  static bool isSphereSphere(IDColiResult &result, const IDColiInput &input, const void *data);
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

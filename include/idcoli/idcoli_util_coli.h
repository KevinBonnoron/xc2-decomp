#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

struct IDCmfPosData;
class IDColiObj;

struct IDColiCallArg {
  mm::Vec3 unknown00; // Inferred role: hit position; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: hit normal; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: hit vector; original member name unknown.
  u32 *unknown30;     // Inferred role: material data of the hit object; original member name unknown.
};

static_assert(offsetof(IDColiCallArg, unknown10) == 0x10, "");
static_assert(offsetof(IDColiCallArg, unknown20) == 0x20, "");
static_assert(offsetof(IDColiCallArg, unknown30) == 0x30, "");
static_assert(sizeof(IDColiCallArg) == 0x40, "");

struct unknown005 {
  virtual void unknown00(u64 value) {}                     // Inferred role: result callback; original name unknown.
  virtual void unknown01(u64 value, IDColiCallArg *arg) {} // Inferred role: stock callback; original name unknown.
};

class IDColiResult {
public:
  IDColiResult() {
    unknownd8 = nullptr;
    unknown00 = 0;
    unknown90 = 100000.0f;
    unknowna0 = -100000.0f;
    unknownb0 = false;
    unknownb1 = false;
    unknownb2 = false;
    unknownb3 = false;
    unknownb8 = nullptr;
    unknownc0 = nullptr;
    unknownc8 = nullptr;
    unknownd0 = nullptr;
    unknowne0 = 0;
    unknowne4 = 0;
    unknowne8 = 0;
    unknownf8 = nullptr;
    unknown100 = nullptr;
    unknown108 = nullptr;
  }

  // Inferred helper: clears the hits before a new test; original name unknown.
  void unknown030() {
    unknowne0 = 0;
    unknown90 = 100000.0f;
    unknowna0 = -100000.0f;
    unknownb0 = false;
    unknownb1 = false;
    unknown10.unknown20 = mm::Vec3(0.0f, 0.0f, 0.0f);
    unknown50.unknown20 = mm::Vec3(0.0f, 0.0f, 0.0f);
  }

  // Inferred helper: notifies the callback of a hit and returns true; original name unknown.
  bool unknown001() {
    if (unknown100 != nullptr) {
      unknown100->unknown00(unknownf0);
    }
    return true;
  }

  s32 unknown00; // Inferred role: result mode; original member name unknown.
  u8 _04[0x10 - 0x04];
  IDColiCallArg unknown10; // Inferred role: front hit; original member name unknown.
  IDColiCallArg unknown50; // Inferred role: back hit; original member name unknown.
  f32 unknown90;           // Inferred role: front hit distance; original member name unknown.
  u8 _94[0x98 - 0x94];
  u64 unknown98; // Inferred role: front hit callback argument; original member name unknown.
  f32 unknowna0; // Inferred role: back hit distance; original member name unknown.
  u8 _a4[0xa8 - 0xa4];
  u64 unknowna8;  // Inferred role: back hit callback argument; original member name unknown.
  bool unknownb0; // Inferred role: front hit found; original member name unknown.
  bool unknownb1; // Inferred role: back hit found; original member name unknown.
  bool unknownb2; // Inferred role: unknown flag; original member name unknown.
  bool unknownb3; // Inferred role: clear the back hit vector after a hit; original member name unknown.
  u8 _b4[0xb8 - 0xb4];
  mm::Vec3 *unknownb8; // Inferred role: stock positions; original member name unknown.
  mm::Vec3 *unknownc0; // Inferred role: stock normals; original member name unknown.
  mm::Vec3 *unknownc8; // Inferred role: stock vectors; original member name unknown.
  u32 **unknownd0;     // Inferred role: stock material data; original member name unknown.
  u32 *unknownd8;      // Inferred role: stock flag bits; original member name unknown.
  u32 unknowne0;       // Inferred role: stock count; original member name unknown.
  u32 unknowne4;       // Inferred role: stock max; original member name unknown.
  u32 unknowne8;       // Inferred role: material bits to skip; original member name unknown.
  u8 _ec[0xf0 - 0xec];
  u64 unknownf0;          // Inferred role: callback argument; original member name unknown.
  IDColiObj *unknownf8;   // Inferred role: tested object; original member name unknown.
  unknown005 *unknown100; // Inferred role: callback; original member name unknown.
  IDColiObj *unknown108;  // Inferred role: object to skip; original member name unknown.
};

static_assert(offsetof(IDColiResult, unknown10) == 0x10, "");
static_assert(offsetof(IDColiResult, unknown50) == 0x50, "");
static_assert(offsetof(IDColiResult, unknown90) == 0x90, "");
static_assert(offsetof(IDColiResult, unknown98) == 0x98, "");
static_assert(offsetof(IDColiResult, unknowna0) == 0xa0, "");
static_assert(offsetof(IDColiResult, unknowna8) == 0xa8, "");
static_assert(offsetof(IDColiResult, unknownb0) == 0xb0, "");
static_assert(offsetof(IDColiResult, unknownb3) == 0xb3, "");
static_assert(offsetof(IDColiResult, unknownb8) == 0xb8, "");
static_assert(offsetof(IDColiResult, unknownd0) == 0xd0, "");
static_assert(offsetof(IDColiResult, unknowne0) == 0xe0, "");
static_assert(offsetof(IDColiResult, unknowne8) == 0xe8, "");
static_assert(offsetof(IDColiResult, unknownf0) == 0xf0, "");
static_assert(offsetof(IDColiResult, unknownf8) == 0xf8, "");
static_assert(offsetof(IDColiResult, unknown100) == 0x100, "");
static_assert(offsetof(IDColiResult, unknown108) == 0x108, "");
static_assert(sizeof(IDColiResult) == 0x110, "");

struct CLBoxWork {
  mm::Vec3 unknown00; // Inferred role: first row of the local to world rotation; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: second row of the local to world rotation; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: third row of the local to world rotation; original member name unknown.
  mm::Vec3 unknown30; // Inferred role: first axis; original member name unknown.
  mm::Vec3 unknown40; // Inferred role: second axis; original member name unknown.
  mm::Vec3 unknown50; // Inferred role: third axis; original member name unknown.
  mm::Vec3 unknown60; // Inferred role: center; original member name unknown.
  mm::Vec3 unknown70; // Inferred role: half size; original member name unknown.
  mm::Vec3 unknown80; // Inferred role: max; original member name unknown.
  mm::Vec3 unknown90; // Inferred role: min; original member name unknown.
  f32 unknowna0;      // Inferred role: scale; original member name unknown.
  f32 unknowna4;      // Inferred role: inverse scale; original member name unknown.
};

static_assert(offsetof(CLBoxWork, unknown10) == 0x10, "");
static_assert(offsetof(CLBoxWork, unknown20) == 0x20, "");
static_assert(offsetof(CLBoxWork, unknown30) == 0x30, "");
static_assert(offsetof(CLBoxWork, unknown90) == 0x90, "");
static_assert(offsetof(CLBoxWork, unknowna0) == 0xa0, "");
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
  f32 unknown54;      // Inferred role: squared length; original member name unknown.
  f32 unknown58;      // Inferred role: inverse squared length; original member name unknown.
};

static_assert(offsetof(CLCapsuleWork, unknown50) == 0x50, "");
static_assert(offsetof(CLCapsuleWork, unknown54) == 0x54, "");
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
  IDColiInput() {}

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

typedef bool (*unknown004)(IDColiResult &, const IDColiInput &, const void *); // Inferred role: collision test function; original name unknown.

class IDColiInputUtil {
public:
  static void calcTreeAABB(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min);
  static void getLine(IDColiInput &input, const mm::Vec3 &start, const mm::Vec3 &end, bool isTree);
  static void getAaBb(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min);
  static void getBox(IDColiInput &input, const CLBoxWork &box);
  static void getSphere(IDColiInput &input, const mm::Vec3 &center, f32 radius, bool isTree);
  static void getSphere(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree);
  static void getLine(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree);
  static void getRay(IDColiInput &input, const mm::Vec3 &start, const mm::Vec3 &direction, f32 length, f32 backLength, bool isTree);
  static void getCapsule(IDColiInput &input, const mm::Vec3 &start, const mm::Vec3 &end, f32 radius, bool isTree);
  static void getRay(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree);
  static void getCapsule(IDColiInput &input, const IDColiInput &source, const IDCmfPosData *posData, bool isTree);
  static void getOBB(IDColiInput &input, const mm::Vec3 &max, const mm::Vec3 &min, const IDCmfPosData *posData);
};

class IDColiUtilMath {
public:
  static void getNearLineToLine(mm::Vec3 &near1, mm::Vec3 &near2, const mm::Vec3 &start1, const mm::Vec3 &end1, const mm::Vec3 &start2, const mm::Vec3 &end2);
  static void getNearLineToPoint(mm::Vec3 &near, const mm::Vec3 &start, const mm::Vec3 &end, const mm::Vec3 &point);
};

class IDColiUtilColiResult {
public:
  static const unknown004 s_CallLine[5];
  static const unknown004 s_CallRay[5];
  static const unknown004 s_CallSphere[5];
  static const unknown004 s_CallCapsule[5];

  static void setStockParms(IDColiResult &result, IDColiCallArg &arg, f32 distance, bool isBack);
  static s32 calcNearBoxPoint(mm::Vec3 &near, const CLBoxWork *box, const mm::Vec3 &point);
  static void calcBoxInPoint(mm::Vec3 &normal, f32 &distance, const CLBoxWork *box, const mm::Vec3 &point, f32 radius);
  static bool calcNearInBoxPoint(mm::Vec3 &near, const CLBoxWork *box, const mm::Vec3 &point, f32 range, f32 radius);
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
  static const unknown004 s_CallLine[5];
  static const unknown004 s_CallRay[5];
  static const unknown004 s_CallSphere[5];
  static const unknown004 s_CallCapsule[5];
  static const unknown004 s_CallBox[5];

  static bool isSphereSphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isPartsLineSphere(IDColiResult &result, const CLLineWork *line, const void *data);
  static bool isLineSphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isRaySphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isSphereBox(IDColiResult &result, const CLSphereWork *sphere, const CLBoxWork *box);
  static bool isSphereBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isSphereInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isSphereCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isSphereInCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isSpherePoli(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleSphere(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleBox(IDColiResult &result, const CLCapsuleWork *capsule, const CLBoxWork *box);
  static bool isCapsuleBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleInBox(IDColiResult &result, const CLCapsuleWork *capsule, const CLBoxWork *box);
  static bool isCapsuleInBox(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
  static bool isCapsuleInCapsule(IDColiResult &result, const IDColiInput &input, const void *data);
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

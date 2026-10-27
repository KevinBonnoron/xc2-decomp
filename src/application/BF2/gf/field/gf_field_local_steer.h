#pragma once
#include <stddef.h>

#include "types.h"

namespace gmk {
class GmkRouteNavi;
} // namespace gmk

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

struct GF_OBJ_HANDLE;

class GfFieldLocalSteer;

// Inferred helper: base of the predicates of the local steer, only the slot of operator() is known; original name unknown.
class unknown001 {
public:
  virtual bool operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const = 0;
};

// Layout evidence: the constructor at 0x710033f554 initializes the members up to 0x5054 (GfBehaviorEnemyField holds one at
// 0x200 and its next member at 0x5260), dispose clears the members up to 0x18 and the destructor inlined in
// GfBehaviorEnemyField::~GfBehaviorEnemyField clears the pointer at 0x5040.
class GfFieldLocalSteer {
public:
  struct CreateInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
    f32 unknown08;            // Role and original member name unknown.
    f32 unknown0c;            // Role and original member name unknown.
    f32 unknown10;            // Role and original member name unknown.
    bool unknown14;           // Role and original member name unknown.
    unknown001 *unknown18;    // Inferred role: predicate selecting the targets; original member name unknown.
  };

  template <typename T> class TIsTargetNotSameSquad : public unknown001 {
  public:
    bool operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const override;
  };

  GfFieldLocalSteer(const CreateInfo *info = nullptr);
  ~GfFieldLocalSteer() {
    dispose();
    if (unknown5040 != nullptr) {
      unknown5040 = nullptr;
    }
  }

  void dispose();
  bool isTimeOutCollide() const;
  f32 getCurAngle() const;

  GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
  f32 unknown08;            // Role and original member name unknown.
  f32 unknown0c;            // Role and original member name unknown.
  f32 unknown10;            // Role and original member name unknown.
  bool unknown14;           // Role and original member name unknown.
  u8 _15[0x18 - 0x15];
  unknown001 *unknown18; // Inferred role: predicate selecting the targets; original member name unknown.
  bool unknown20;        // Role and original member name unknown.
  u8 _21[0x24 - 0x21];
  f32 unknown24; // Inferred role: collide time; original member name unknown.
  u8 _28[0x30 - 0x28];
  f32 unknown30; // Inferred role: start angle; original member name unknown.
  f32 unknown34; // Inferred role: target angle; original member name unknown.
  f32 unknown38; // Inferred role: duration; original member name unknown.
  f32 unknown3c; // Inferred role: elapsed time; original member name unknown.
  u8 _40[0x5040 - 0x40];
  void *unknown5040; // Inferred role: pointer cleared by the destructor; original member name unknown.
  u8 _5048[0x5050 - 0x5048];
  f32 unknown5050;  // Role and original member name unknown.
  bool unknown5054; // Role and original member name unknown.
  u8 _5055[0x5060 - 0x5055];
};

static_assert(offsetof(GfFieldLocalSteer, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldLocalSteer, unknown14) == 0x14, "");
static_assert(offsetof(GfFieldLocalSteer, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldLocalSteer, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldLocalSteer, unknown24) == 0x24, "");
static_assert(offsetof(GfFieldLocalSteer, unknown30) == 0x30, "");
static_assert(offsetof(GfFieldLocalSteer, unknown3c) == 0x3c, "");
static_assert(offsetof(GfFieldLocalSteer, unknown5040) == 0x5040, "");
static_assert(offsetof(GfFieldLocalSteer, unknown5050) == 0x5050, "");
static_assert(offsetof(GfFieldLocalSteer, unknown5054) == 0x5054, "");
static_assert(sizeof(GfFieldLocalSteer) == 0x5060, "");

void validateGmkRouteNaviConsideringGfLocalSteer(gmk::GmkRouteNavi &navi, const GfFieldLocalSteer &steer, const mm::Vec3 &position);

} // namespace gf

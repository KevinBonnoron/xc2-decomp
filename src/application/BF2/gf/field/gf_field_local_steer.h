#pragma once
#include <stddef.h>

#include "fw/fw_coli_check.h"
#include "gf/gf_tween.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gmk {
class GmkRouteNavi;
} // namespace gmk

namespace fw {
class ComponentObject;
} // namespace fw

namespace navi {
class NvmshAcObj;
} // namespace navi

namespace gf {

struct GF_OBJ_HANDLE;

class GfFieldLocalSteer;

// Inferred helper: base of the predicates of the local steer, only the slot of operator() is known; original name unknown.
class unknown001 {
public:
  virtual bool operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const = 0;
};

// Layout evidence: the constructor at 0x710033f554 initializes the members up to 0x5054 (GfBehaviorEnemyField holds one at
// 0x200 and its next member at 0x5260), create copies the CreateInfo at 0x00 as one struct, the constructor stores the
// TGfTween<float> vtable at 0x28 and castRay passes the result at 0x40 to fw::ColiCheck::testLineChara.
class GfFieldLocalSteer {
public:
  struct CreateInfo {
    GF_OBJ_HANDLE *unknown00 = unknown020; // Inferred role: object; original member name unknown.
    f32 unknown08 = 2.0f;                  // Inferred role: ray length; original member name unknown.
    f32 unknown0c = 1.0f;                  // Inferred role: ray height; original member name unknown.
    f32 unknown10 = 0.5f;                  // Inferred role: turn duration; original member name unknown.
    bool unknown14 = true;                 // Role and original member name unknown.
    unknown001 *unknown18 = nullptr;       // Inferred role: predicate selecting the targets; original member name unknown.
  };

  template <typename T> class TIsTargetNotSameSquad : public unknown001 {
  public:
    bool operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const override;
  };

  struct UpdateInfo {
    mm::Vec3 unknown00; // Inferred role: goal position; original member name unknown.
    f32 unknown10;      // Inferred role: delta time; original member name unknown.
  };

  GfFieldLocalSteer(const CreateInfo *info = nullptr);
  ~GfFieldLocalSteer() { dispose(); }

  void create(const CreateInfo &info);
  void dispose();
  void update(const UpdateInfo &info);
  void apply(mm::Vec3 &result, const mm::Vec3 &direction) const;
  bool isTimeOutCollide() const;
  f32 getCurAngle() const;
  static bool isUseLocalSteer(GF_OBJ_HANDLE *handle);
  void castRay(const mm::Vec3 &position);

  CreateInfo unknown00;                // Inferred role: create parameters; original member name unknown.
  bool unknown20;                      // Inferred role: avoiding; original member name unknown.
  f32 unknown24;                       // Inferred role: collide time; original member name unknown.
  TGfTween<f32> unknown28;             // Inferred role: steer angle; original member name unknown.
  fw::TColiCheckResult<256> unknown40; // Inferred role: ray cast result; original member name unknown.
};

static_assert(offsetof(GfFieldLocalSteer::CreateInfo, unknown18) == 0x18, "");
static_assert(sizeof(GfFieldLocalSteer::CreateInfo) == 0x20, "");
static_assert(offsetof(GfFieldLocalSteer, unknown20) == 0x20, "");
static_assert(offsetof(GfFieldLocalSteer, unknown24) == 0x24, "");
static_assert(offsetof(GfFieldLocalSteer, unknown28) == 0x28, "");
static_assert(offsetof(GfFieldLocalSteer, unknown40) == 0x40, "");
static_assert(sizeof(GfFieldLocalSteer) == 0x5060, "");

void validateGmkRouteNaviConsideringGfLocalSteer(gmk::GmkRouteNavi &navi, const GfFieldLocalSteer &steer, const mm::Vec3 &position);
bool canGetMoveVec(const navi::NvmshAcObj *navi);
bool getMoveVec(mm::Vec3 &vector, const navi::NvmshAcObj *navi);
bool execEndSchedule(fw::ComponentObject &component);

} // namespace gf

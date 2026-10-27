#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
class IkFadeSolver;
} // namespace fw

namespace gmk {
class GmkRouteNavi;
} // namespace gmk

namespace gf {

struct GF_OBJ_HANDLE;

// Sub object at 0x5268 of GfBehaviorEnemyField. The layout follows the constructor (0x7100340e88), dispose (0x7100340f3c),
// seqInit (0x7100340f60) and seqUpdate (0x71003410ac), which writes the pitch and the roll to the solver at 0x10.
class GfFieldPitchRollController {
public:
  // Inferred helper: two flags copied together from the create info; original name unknown.
  struct unknown001 {
    unknown001() : unknown00(true), unknown01(true) {}

    bool unknown00; // Role and original member name unknown.
    bool unknown01; // Role and original member name unknown.
  };

  struct CreateInfo {
    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
    unknown001 unknown08;     // Role and original member name unknown.
    bool unknown0a;           // Role and original member name unknown.
  };

  GfFieldPitchRollController(const CreateInfo *info = nullptr);
  void create(const CreateInfo &info);
  ~GfFieldPitchRollController() { dispose(); }
  void dispose();
  void update(const gmk::GmkRouteNavi &navi);
  void seqInit(const gmk::GmkRouteNavi &navi);
  void seqUpdate(const gmk::GmkRouteNavi &navi);

  GF_OBJ_HANDLE *unknown00;                                                     // Inferred role: object; original member name unknown.
  unknown001 unknown08;                                                         // Role and original member name unknown.
  bool unknown0a;                                                               // Role and original member name unknown.
  fw::IkFadeSolver *unknown10;                                                  // Inferred role: solver; original member name unknown.
  void (GfFieldPitchRollController::*unknown18)(const gmk::GmkRouteNavi &navi); // Inferred role: seq; original member name unknown.
  f32 unknown28;                                                                // Inferred role: pitch; original member name unknown.
  f32 unknown2c;                                                                // Inferred role: roll; original member name unknown.
  bool unknown30;                                                               // Inferred role: set with unknown31 when the enemy returns to the battle state; original member name unknown.
  bool unknown31;                                                               // Inferred role: set with unknown30 when the enemy returns to the battle state; original member name unknown.
  u8 _32[0x38 - 0x32];
};

static_assert(offsetof(GfFieldPitchRollController, unknown08) == 0x08, "");
static_assert(offsetof(GfFieldPitchRollController, unknown0a) == 0x0a, "");
static_assert(offsetof(GfFieldPitchRollController, unknown10) == 0x10, "");
static_assert(offsetof(GfFieldPitchRollController, unknown18) == 0x18, "");
static_assert(offsetof(GfFieldPitchRollController, unknown28) == 0x28, "");
static_assert(offsetof(GfFieldPitchRollController, unknown30) == 0x30, "");
static_assert(sizeof(GfFieldPitchRollController) == 0x38, "");

} // namespace gf

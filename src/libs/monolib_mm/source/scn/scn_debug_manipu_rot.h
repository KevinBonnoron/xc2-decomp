#pragma once
#include <stddef.h>

#include "scn/scn_debug_manipu_obj.h"
#include "types.h"

namespace mm {
struct Col3;
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;
class Scn;

class ScnDebugManipuRot : public ScnDebugManipuObj {
public:
  ScnDebugManipuRot(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale);
  ~ScnDebugManipuRot() override;
  void setRadius(f32 radius) override;
  bool checkMouseButtonDown(EventView *event) override;
  bool checkMouseButtonUp(EventView *event) override;
  bool checkMouseMove(EventView *event) override;
  void update() override;
  void render(DebDraw *debDraw) override;
  void renderHalfCircle(DebDraw *debDraw, int axis, const mm::Col3 &color);

  u8 _360[0x970 - 0x360];
  s32 unknown970; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _974[0x990 - 0x974];
  f32 unknown990; // Inferred role: unknown, 70.0f set by the constructor; original member name unknown.
  f32 unknown994; // Inferred role: unknown, 80.0f set by the constructor; original member name unknown.
  u8 _998[0x9b0 - 0x998];
};

static_assert(offsetof(ScnDebugManipuRot, unknown970) == 0x970, "");
static_assert(offsetof(ScnDebugManipuRot, unknown990) == 0x990, "");
static_assert(offsetof(ScnDebugManipuRot, unknown994) == 0x994, "");
static_assert(sizeof(ScnDebugManipuRot) == 0x9b0, "");

} // namespace ml

#pragma once
#include <stddef.h>

#include "scn/scn_debug_manipu_obj.h"
#include "types.h"

namespace mm {
struct Col4;
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;
class EventView;
class Scn;

class ScnDebugManipuScale2D : public ScnDebugManipuObj {
public:
  ScnDebugManipuScale2D(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale);
  ~ScnDebugManipuScale2D() override;
  void setRadius(f32 radius) override;
  bool checkMouseButtonDown(EventView *event) override;
  bool checkMouseButtonUp(EventView *event) override;
  bool checkMouseMove(EventView *event) override;
  void update() override;
  void render(DebDraw *debDraw) override;
  int getSelectedAxisArrowPick(EventView *event, const mm::Vec3 &position);
  int getSelectedAxisPlanePick(EventView *event, const mm::Vec3 &position);
  void renderCubeAxisX(DebDraw *debDraw, s16 x, s16 y, int size, const mm::Col4 *color);
  void renderCubeAxisY(DebDraw *debDraw, s16 x, s16 y, int size, const mm::Col4 *color);

  s32 unknown360; // Inferred role: mouse drag x, cleared by the constructor; original member name unknown.
  s32 unknown364; // Inferred role: mouse drag y, cleared by the constructor; original member name unknown.
  s32 unknown368; // Inferred role: unknown, 4 set by the constructor; original member name unknown.
};

static_assert(offsetof(ScnDebugManipuScale2D, unknown360) == 0x360, "");
static_assert(offsetof(ScnDebugManipuScale2D, unknown364) == 0x364, "");
static_assert(offsetof(ScnDebugManipuScale2D, unknown368) == 0x368, "");

} // namespace ml

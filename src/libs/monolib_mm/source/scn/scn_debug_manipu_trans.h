#pragma once
#include <stddef.h>

#include "scn/scn_debug_manipu_obj.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class EventView;
class Scn;

class ScnDebugManipuTrans : public ScnDebugManipuObj {
public:
  ScnDebugManipuTrans(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale);
  ~ScnDebugManipuTrans() override;
  void setRadius(f32 radius) override;
  bool checkMouseButtonDown(EventView *event) override;
  bool checkMouseButtonUp(EventView *event) override;
  bool checkMouseMove(EventView *event) override;
  void update() override;
  void render(DebDraw *debDraw) override;
  int getSelectedAxisArrowPick(EventView *event, const mm::Vec3 &position);
  int getSelectedAxisPlanePick(EventView *event, const mm::Vec3 &position);

  u8 _360[0x380 - 0x360];
  u64 unknown380; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  s32 unknown388; // Inferred role: unknown, 7 set by the constructor; original member name unknown.
};

static_assert(offsetof(ScnDebugManipuTrans, unknown380) == 0x380, "");
static_assert(offsetof(ScnDebugManipuTrans, unknown388) == 0x388, "");

} // namespace ml

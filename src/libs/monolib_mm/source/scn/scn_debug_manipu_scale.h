#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "scn/scn_debug_manipu_obj.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace ml {

class EventView;
class Scn;

class ScnDebugManipuScale : public ScnDebugManipuObj {
public:
  ScnDebugManipuScale(Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale);
  ~ScnDebugManipuScale() override;
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
  u8 _38c[0x390 - 0x38c];
  mm::Vec3 unknown390; // Inferred role: unknown, zero vector set by the constructor; original member name unknown.
};

static_assert(offsetof(ScnDebugManipuScale, unknown380) == 0x380, "");
static_assert(offsetof(ScnDebugManipuScale, unknown388) == 0x388, "");
static_assert(offsetof(ScnDebugManipuScale, unknown390) == 0x390, "");

} // namespace ml

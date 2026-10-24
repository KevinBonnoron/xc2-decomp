#pragma once
#include <stddef.h>

#include "ml/attr_transform.h"
#include "ml/threadval.h"
#include "mm_math/mm_mat44.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {

class DebDraw;
class EventView;
class Scn;

enum SCNMANIPU {
  SCNMANIPU_NONE = -1,
  SCNMANIPU_TRANS,
  SCNMANIPU_ROT,
  SCNMANIPU_SCALE,
  SCNMANIPU_TRANS_2D,
  SCNMANIPU_SCALE_2D,
};

enum SCNAXIS {};

class ScnDebugManipuObj {
public:
  struct RENDER_INFO {
    AttrTransform unknown00; // Inferred role: transform; original member name unknown.
  };

  void getGblMat(mm::Mat44 &matrix, bool isBack);
  ScnDebugManipuObj(SCNMANIPU type, Scn *scn, const mm::Mat44 *matrix, const mm::Vec3 *scale);
  virtual ~ScnDebugManipuObj() {}
  virtual bool checkMouseButtonDown(EventView *event) = 0;
  virtual bool checkMouseButtonUp(EventView *event) = 0;
  virtual bool checkMouseMove(EventView *event) = 0;
  virtual void setRadius(f32 radius) = 0;
  virtual void update() = 0;
  virtual void render(DebDraw *debDraw) = 0;

  Scn *unknown08;      // Inferred role: scn; original member name unknown.
  SCNMANIPU unknown10; // Inferred role: type; original member name unknown.
  SCNAXIS unknown14;   // Inferred role: axis lock; original member name unknown.
  int unknown18;       // Inferred role: pick; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  bool unknown20;      // Inferred role: disp; original member name unknown.
  mm::Mat44 unknown30; // Inferred role: matrix; original member name unknown.
  u8 _70[0xb0 - 0x70];
  threadval<RENDER_INFO> unknownb0; // Inferred role: render info; original member name unknown.
};

static_assert(offsetof(ScnDebugManipuObj, unknown10) == 0x10, "");
static_assert(offsetof(ScnDebugManipuObj, unknown18) == 0x18, "");
static_assert(offsetof(ScnDebugManipuObj, unknown20) == 0x20, "");
static_assert(offsetof(ScnDebugManipuObj, unknown30) == 0x30, "");
static_assert(offsetof(ScnDebugManipuObj, unknownb0) == 0xb0, "");

} // namespace ml

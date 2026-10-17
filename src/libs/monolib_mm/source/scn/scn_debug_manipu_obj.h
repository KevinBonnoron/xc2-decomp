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
    AttrTransform transform;
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

  Scn *m_scn;
  SCNMANIPU m_type;
  SCNAXIS m_axisLock;
  int m_pick;
  u8 _1c[0x20 - 0x1c];
  bool m_isDisp;
  mm::Mat44 m_matrix;
  u8 _70[0xb0 - 0x70];
  threadval<RENDER_INFO> m_renderInfo;
};

static_assert(offsetof(ScnDebugManipuObj, m_type) == 0x10, "");
static_assert(offsetof(ScnDebugManipuObj, m_pick) == 0x18, "");
static_assert(offsetof(ScnDebugManipuObj, m_isDisp) == 0x20, "");
static_assert(offsetof(ScnDebugManipuObj, m_matrix) == 0x30, "");
static_assert(offsetof(ScnDebugManipuObj, m_renderInfo) == 0xb0, "");

} // namespace ml

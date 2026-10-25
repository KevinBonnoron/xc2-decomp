#pragma once
#include <stddef.h>

#include "ml/critical_section.h"
#include "ml/work_event.h"
#include "mtl/alloc_handle.h"
#include "scn/scn_debug_manipu_obj.h"
#include "scn/scn_render_callback.h"
#include "types.h"

namespace mm {
struct Mat44;
struct Vec3;
} // namespace mm

namespace ml {

class AttrTransform;
class DebDraw;
class Scn;
class EventView;

class ScnDebugManipu : public IWorkEvent {
public:
  bool isPick() const;
  void setCalcRotationZXY();
  void setAxisLock(SCNAXIS axis);
  SCNAXIS getAxisLock() const;
  SCNMANIPU getType() const;
  void createTrans(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void createTrans2D(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void createRot(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void createScale(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void createScale2D(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void setRadius(f32 radius);
  void setDisp(bool isDisp);
  void clear();
  const AttrTransform *getTrans(bool isBack) const;
  void setTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale);
  void setTrans(const AttrTransform &transform);
  void render(DebDraw *debDraw);
  ScnDebugManipu(Scn *scn);
  ~ScnDebugManipu() override;
  bool getGblMat(mm::Mat44 &matrix, bool isBack);
  bool OnMouseButtonDown(EventView *event);
  bool OnMouseButtonUp(EventView *event);
  bool OnMouseMove(EventView *event);
  void update();

  CriticalSection unknown08;    // Inferred role: cs; original member name unknown.
  Scn *unknown30;               // Inferred role: scn; original member name unknown.
  ScnDebugManipuObj *unknown38; // Inferred role: object; original member name unknown.
  bool unknown40;               // Inferred role: disp; original member name unknown.
};

static_assert(offsetof(ScnDebugManipu, unknown08) == 0x08, "");
static_assert(offsetof(ScnDebugManipu, unknown30) == 0x30, "");
static_assert(offsetof(ScnDebugManipu, unknown38) == 0x38, "");
static_assert(offsetof(ScnDebugManipu, unknown40) == 0x40, "");

class ScnDebug : public IWorkEvent, public IScnRender {
public:
  void render(DebDraw *debDraw);

  ScnDebug(Scn *scn, mtl::ALLOC_HANDLE mem);
  ~ScnDebug() override;
  mtl::ALLOC_HANDLE getMem() const;
  bool isPickManipu() const;
  const ScnDebugManipu *getManipulator() const;
  void setManipuCalcRotationZXY();
  ScnDebugManipu *getManipulator();
  void setManipuAxisLock(SCNAXIS axis);
  SCNAXIS getManipuAxisLock() const;
  SCNMANIPU getManipuType() const;
  void setManipulatorTrans(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void setManipulatorTrans2D(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void setManipulatorRot(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void setManipulatorScale(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void setManipulatorScale2D(const mm::Mat44 *matrix, const mm::Vec3 *scale);
  void setManipulatorRadius(f32 radius);
  void setManipulatorDisp(bool isDisp);
  void clrManipulator();
  const AttrTransform *getManipuTrans(bool isBack) const;
  void setManipuTrans(const mm::Vec3 *position, const mm::Vec3 *rotation, const mm::Vec3 *scale);
  void setManipuTrans(const AttrTransform &transform);
  void update();
  void cbRenderAfter(Scn *scn, SCNPRIO_CB priority) override;

  Scn *unknown10; // Inferred role: scn; original member name unknown.
  ScnDebugManipu *m_manipulator;
  int _20;
  void *_28;
  bool _30;
};

static_assert(offsetof(ScnDebug, unknown10) == 0x10, "");
static_assert(offsetof(ScnDebug, m_manipulator) == 0x18, "");
static_assert(offsetof(ScnDebug, _20) == 0x20, "");
static_assert(offsetof(ScnDebug, _30) == 0x30, "");

} // namespace ml

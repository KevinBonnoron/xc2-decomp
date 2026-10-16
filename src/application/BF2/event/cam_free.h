#pragma once
#include "event/cam_base.h"
#include "ml/work_event.h"
#include "types.h"

namespace ml {
class EventView;
} // namespace ml

namespace mm {
struct Mat44;
struct Vec3;

template <typename T> struct Pnt;
} // namespace mm

namespace event {

class CamFree : public CamBase, public ml::IWorkEvent {
public:
  enum CTRL_MODE {
    CTRL_MODE_NONE,
    CTRL_MODE_DOLLY,
    CTRL_MODE_TRACK,
    CTRL_MODE_TUMBLE,
  };

  CamFree(bool isFocal);
  virtual ~CamFree();
  virtual void update(const FrameInfo &info);
  void setActive(bool isActive);
  virtual bool OnMouseButtonDown(ml::EventView *view);
  virtual bool OnMouseMove(ml::EventView *view);
  void ctrlTumble(const mm::Pnt<int> &mouse);
  void ctrlDolly(const mm::Pnt<int> &mouse);
  void ctrlTrack(const mm::Pnt<int> &mouse);
  virtual bool OnMouseButtonUp(ml::EventView *view);
  virtual bool OnKeyUp(ml::EventView *view);
  virtual bool OnKeyDown(ml::EventView *view);
  void getScreenMove2TargetMove(mm::Vec3 &move, const mm::Pnt<int> &mouse) const;
  void getViewInvertMatrix(mm::Mat44 &matrix) const;
  void getViewMatrix(mm::Mat44 &matrix) const;
  void getFrustum(mm::Mat44 &matrix) const;

private:
  u32 flags;
  u32 mButtonFlags;
  CTRL_MODE mCtrlMode;
  f32 mMoveSpeed;
  u8 _58[0x60 - 0x58];
};

static_assert(sizeof(CamFree) == 0x60, "");

} // namespace event

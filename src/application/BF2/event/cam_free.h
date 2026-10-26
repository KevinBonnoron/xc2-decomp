#pragma once
#include "event/cam_base.h"
#include "ml/work_event.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace ml {
class EventView;
} // namespace ml

namespace mm {
struct Mat44;

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

  // Inferred role: copies the view parameters of a camera; original name unknown.
  void unknown002(const CamBase &cam) {
    unknown08 = cam.isFocal();
    unknown10.x = cam.getPos().x;
    unknown10.y = cam.getPos().y;
    unknown10.z = cam.getPos().z;
    unknown20.x = cam.getTarget().x;
    unknown20.y = cam.getTarget().y;
    unknown20.z = cam.getTarget().z;
    unknown30 = cam.getFov();
    unknown34 = cam.getRoll();
  }

private:
  // Inferred role: ctrl mode update shared by the mouse button handlers; original name unknown.
  bool unknown001() {
    unknown50 = CTRL_MODE_NONE;
    if ((unknown4c & 8) == 0) {
      return false;
    }
    if ((unknown4c & 1) != 0) {
      unknown50 = CTRL_MODE_DOLLY;
      return true;
    }
    if ((unknown4c & 2) != 0) {
      unknown50 = CTRL_MODE_TRACK;
      return true;
    }
    if ((unknown4c & 4) == 0) {
      return false;
    }
    unknown50 = CTRL_MODE_TUMBLE;
    return true;
  }

  u32 unknown48;       // Inferred role: flags; original member name unknown.
  u32 unknown4c;       // Inferred role: button flags; original member name unknown.
  CTRL_MODE unknown50; // Inferred role: ctrl mode; original member name unknown.
  f32 unknown54;       // Inferred role: move speed; original member name unknown.
  u8 _58[0x60 - 0x58];
};

static_assert(sizeof(CamFree) == 0x60, "");

} // namespace event

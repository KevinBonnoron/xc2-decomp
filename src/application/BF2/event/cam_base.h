#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
struct Col4;
}

namespace event {

struct FrameInfo;

class CamBase {
public:
  CamBase(bool isFocal);
  virtual ~CamBase() {}
  virtual void update(const FrameInfo &info) {}
  virtual void render(const mm::Col4 &color) {}
  virtual void tail() {}
  mm::Vec3 getRot() const;
  bool isFocal() const { return mIsFocal; }
  const mm::Vec3 &getPos() const { return mPos; }
  const mm::Vec3 &getTarget() const { return mTarget; }
  f32 getFov() const { return mFov; }
  f32 getRoll() const { return mRoll; }

protected:
  bool mIsFocal;
  mm::Vec3 mPos;
  mm::Vec3 mTarget;
  f32 mFov;
  f32 mRoll;
  f32 mNear;
  f32 mFar;
};

static_assert(sizeof(CamBase) == 0x40, "");

} // namespace event

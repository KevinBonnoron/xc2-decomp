#pragma once
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrEnvColiMan;

class ScnRenderDrEnvColi {
public:
  ScnRenderDrEnvColi(s32 index);
  ~ScnRenderDrEnvColi();
  bool testEnvColi(const mm::Vec3 &position, f32 radius);
  s32 getBgmId() const;
  s32 getLayerId() const;
  s32 getReverbId() const;
  s32 getCaveId() const;
  s32 getAreaId() const;
  s32 getWindId() const;
  bool isRoom() const;

private:
  DrEnvColiMan *m_envColiMan;
};

} // namespace ml

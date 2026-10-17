#pragma once
#include <stddef.h>

#include "ssd/ssd_sound.h"
#include "types.h"

namespace ssd {

struct Mat34 {
  f32 m[3][4];
};

void Mat34LookAt(Mat34 *matrix, const Vec3 *position, const Vec3 *look, const Vec3 *up);
void Vec3Transform(const Mat34 *matrix, const Vec3 *in, Vec3 *out);

class SoundListener : public Object {
public:
  struct Param {
    Vec3 position;
    Vec3 look;
    Vec3 up;
    Vec3 velocity;
  };

  void Connect();
  ~SoundListener() override;
  void Disconnect();
  void Init();
  void Quit();
  void SetParam(const Vec3 &position, const Vec3 &look, const Vec3 &up);
  void SetPosition(const Vec3 &position);
  void SetPosition(const f32 *position);
  void SetPosition(f32 x, f32 y, f32 z);
  void SetLook(const Vec3 &look);
  void SetLook(const f32 *look);
  void SetLook(f32 x, f32 y, f32 z);
  void SetUp(const Vec3 &up);
  void SetUp(const f32 *up);
  void SetUp(f32 x, f32 y, f32 z);
  void SetOrientation(const Vec3 &look, const Vec3 &up);
  void SetOrientation(f32 lookX, f32 lookY, f32 lookZ, f32 upX, f32 upY, f32 upZ);
  void LookAt(const Vec3 &position, const Vec3 &look, const Vec3 &up);
  void LookAt(const f32 *position, const f32 *look, const f32 *up);
  void SetVelocity(const Vec3 &velocity);
  void SetVelocity(f32 x, f32 y, f32 z);
  f32 GetInteriorSize() const;
  void SetInteriorSize(f32 size);
  f32 GetDopplerFactor() const;
  void SetDopplerFactor(f32 factor);
  bool IsEnableDoppler() const;
  void UpdateGameFrame(f32 deltaTime);
  void UpdateMatrix();
  void Vec3Transform(const Vec3 *in, Vec3 *out);

  Param param;
  Param applyParam;
  bool isConnect;
  bool isCalcVelocity;
  bool isUpdate;
  bool isUpdateVelocity;
  bool isValidMatrix;
  bool isEnableDoppler;
  f32 dopplerFactor;
  f32 interiorSize;
  Mat34 matrix;
};

static_assert(offsetof(SoundListener, param) == 0x18, "");
static_assert(offsetof(SoundListener, applyParam) == 0x48, "");
static_assert(offsetof(SoundListener, isConnect) == 0x78, "");
static_assert(offsetof(SoundListener, dopplerFactor) == 0x80, "");
static_assert(offsetof(SoundListener, matrix) == 0x88, "");

} // namespace ssd

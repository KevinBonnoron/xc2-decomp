#pragma once
#include <stddef.h>

#include "ssd/ssd_sound.h"
#include "types.h"

namespace ssd {

struct Mat34 {
  f32 unknown00[4][3]; // Inferred role: three axes and the translation; original member name unknown.
};

struct Vector3 {
  f32 unknown00; // Inferred role: x; original member name unknown.
  f32 unknown04; // Inferred role: y; original member name unknown.
  f32 unknown08; // Inferred role: z; original member name unknown.
};

void MakeIdentityf34(Mat34 *matrix);
void GetMatAxes(Vector3 *axisX, Vector3 *axisY, Vector3 *axisZ, Vector3 *translation, const Mat34 &matrix);

void Mat34LookAt(Mat34 *matrix, const Vec3 *position, const Vec3 *look, const Vec3 *up);
Vec3 *Vec3Transform(const Mat34 *matrix, const Vec3 *in, Vec3 *out);

class SoundListener : public Object {
public:
  struct Param {
    Vec3 unknown00; // Inferred role: position; original member name unknown.
    Vec3 unknown0c; // Inferred role: look; original member name unknown.
    Vec3 unknown18; // Inferred role: up; original member name unknown.
    Vec3 unknown24; // Inferred role: velocity; original member name unknown.
  };

  SoundListener();
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

  Param unknown18; // Inferred role: param; original member name unknown.
  Param unknown48; // Inferred role: apply param; original member name unknown.
  bool unknown78;  // Inferred role: connect; original member name unknown.
  bool unknown79;  // Inferred role: calc velocity; original member name unknown.
  bool unknown7a;  // Inferred role: update; original member name unknown.
  bool unknown7b;  // Inferred role: update velocity; original member name unknown.
  bool unknown7c;  // Inferred role: valid matrix; original member name unknown.
  bool m_enableDoppler;
  f32 m_dopplerFactor;
  f32 m_interiorSize;
  Mat34 unknown88; // Inferred role: matrix; original member name unknown.
};

static_assert(offsetof(SoundListener, unknown18) == 0x18, "");
static_assert(offsetof(SoundListener, unknown48) == 0x48, "");
static_assert(offsetof(SoundListener, unknown78) == 0x78, "");
static_assert(offsetof(SoundListener, m_dopplerFactor) == 0x80, "");
static_assert(offsetof(SoundListener, unknown88) == 0x88, "");

} // namespace ssd

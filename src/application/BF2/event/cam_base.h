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
  bool isFocal() const { return unknown08; }
  const mm::Vec3 &getPos() const { return unknown10; }
  const mm::Vec3 &getTarget() const { return unknown20; }
  f32 getFov() const { return unknown30; }
  f32 getRoll() const { return unknown34; }
  f32 getNear() const { return unknown38; }
  f32 getFar() const { return unknown3c; }
  void setNearFar(f32 nearClip, f32 farClip) {
    unknown38 = nearClip;
    unknown3c = farClip;
  }

protected:
  bool unknown08;     // Inferred role: is focal; original member name unknown.
  mm::Vec3 unknown10; // Inferred role: pos; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: target; original member name unknown.
  f32 unknown30;      // Inferred role: fov; original member name unknown.
  f32 unknown34;      // Inferred role: roll; original member name unknown.
  f32 unknown38;      // Inferred role: near; original member name unknown.
  f32 unknown3c;      // Inferred role: far; original member name unknown.
};

static_assert(sizeof(CamBase) == 0x40, "");

} // namespace event

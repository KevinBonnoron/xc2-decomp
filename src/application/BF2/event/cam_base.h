#pragma once
#include "ml/attr_transform.h"
#include "ml/scn.h"
#include "ml/threadval.h"
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

  // Inferred role: copies the position and the target of a scene camera; original name unknown.
  void unknown003(const ml::ScnObjCam *cam) {
    unknown10 = cam->unknown70.m_front->unknown00.unknown10;
    unknown20 = cam->unknown70.m_front->m_targetPos;
  }

  // Inferred role: sets the default fov and roll; original name unknown.
  void unknown004() {
    unknown30 = 40.0f;
    unknown34 = 0.0f;
  }

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // Role: stores the roll. Its user is CamEvaPlayer::update (1.0.0: 0x71000ad62c, 646 instructions). Form tried without the helper: `m_camBase->unknown34 = roll;` through a public member gives
  // 646 instructions with 3 differing lines: the assignment loads `roll` before the camera pointer, the game loads the camera pointer first (the call evaluates the object first).
  void setRoll(f32 roll) { unknown34 = roll; }

protected:
  bool unknown08; // Inferred role: is focal; original member name unknown.

public:
  // Public because CamEvaPlayer::update stores the position, the target and the fov through the camera pointer.
  mm::Vec3 unknown10; // Inferred role: pos; original member name unknown.
  mm::Vec3 unknown20; // Inferred role: target; original member name unknown.
  f32 unknown30;      // Inferred role: fov; original member name unknown.

protected:
  f32 unknown34; // Inferred role: roll; original member name unknown.
  f32 unknown38; // Inferred role: near; original member name unknown.
  f32 unknown3c; // Inferred role: far; original member name unknown.
};

static_assert(sizeof(CamBase) == 0x40, "");

} // namespace event

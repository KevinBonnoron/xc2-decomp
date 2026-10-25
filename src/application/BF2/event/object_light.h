#pragma once
#include <stddef.h>

#include "event/object.h"
#include "event/pos_axis.h"
#include "event/rot_axis.h"
#include "types.h"

namespace event {

class LightObj;

class ObjectLight : public Object {
public:
  ObjectLight(const char *name, u32 id);
  virtual ~ObjectLight();
  virtual void update();
  virtual void render(const mm::Col4 &color);
  void play(const char *name, f32 frame);
  void setPosAxis(const PosAxis &axis);
  void setRotAxis(const RotAxis &axis);

  LightObj *getLightObj() const { return unknown68; }

private:
  LightObj *unknown68; // Inferred role: light object; original member name unknown.
  PosAxis unknown70;   // Inferred role: position axis; original member name unknown.
  RotAxis unknown90;   // Inferred role: rotation axis; original member name unknown.

  friend struct ObjectLightLayout;
};

struct ObjectLightLayout {
  static_assert(offsetof(ObjectLight, unknown68) == 0x68, "");
  static_assert(offsetof(ObjectLight, unknown70) == 0x70, "");
  static_assert(offsetof(ObjectLight, unknown90) == 0x90, "");
  static_assert(sizeof(ObjectLight) == 0xb0, "");
};

} // namespace event

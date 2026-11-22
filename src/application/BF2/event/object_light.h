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

  LightObj *getLightObj() const { return m_lightObj; }

private:
  LightObj *m_lightObj; // Inferred role: light object; original member name unknown.
  PosAxis m_posAxis;    // Inferred role: position axis; original member name unknown.
  RotAxis m_rotAxis;    // Inferred role: rotation axis; original member name unknown.

  friend struct ObjectLightLayout;
};

struct ObjectLightLayout {
  static_assert(offsetof(ObjectLight, m_lightObj) == 0x68, "");
  static_assert(offsetof(ObjectLight, m_posAxis) == 0x70, "");
  static_assert(offsetof(ObjectLight, m_rotAxis) == 0x90, "");
  static_assert(sizeof(ObjectLight) == 0xb0, "");
};

} // namespace event

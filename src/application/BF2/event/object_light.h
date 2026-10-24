#pragma once
#include "event/object.h"
#include "types.h"

namespace event {

class LightObj;
class PosAxis;
class RotAxis;

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
  u8 _70[0xb0 - 0x70];
};

static_assert(sizeof(ObjectLight) == 0xb0, "");

} // namespace event

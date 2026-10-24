#pragma once
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class ScnObjLight;
} // namespace ml

namespace event {

struct FrameInfo;

class LightObj {
public:
  LightObj(int screenID);
  virtual ~LightObj();
  void clear();
  void update(const FrameInfo &info);
  void render(int x, int y);
  void play(const char *name, f32 life);
  bool isPlaying() const;
  void setPos(const mm::Vec3 &pos);
  const mm::Vec3 &getPos() const;
  void setRot(const mm::Vec3 &rot);

private:
  u32 unknown08;                  // Inferred role: flags; original member name unknown.
  ml::ScnObjLight *unknown10;     // Inferred role: light; original member name unknown.
  int unknown18;                  // Inferred role: screen id; original member name unknown.
  mm::mtl::FixStr<128> unknown1c; // Inferred role: path; original member name unknown.
  void *unknowna0;                // Inferred role: data; original member name unknown.
  f32 unknowna8;                  // Inferred role: life; original member name unknown.
  mm::Vec3 m_pos;
  mm::Vec3 unknownc0; // Inferred role: rot; original member name unknown.
};

static_assert(sizeof(LightObj) == 0xd0, "");

} // namespace event

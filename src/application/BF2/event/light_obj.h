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
  u32 flags;
  ml::ScnObjLight *mLight;
  int mScreenID;
  mm::mtl::FixStr<128> path;
  void *mData;
  f32 mLife;
  mm::Vec3 mPos;
  mm::Vec3 mRot;
};

static_assert(sizeof(LightObj) == 0xd0, "");

} // namespace event

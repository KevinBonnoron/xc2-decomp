#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class ScnObjLight;
} // namespace ml

namespace event {

class LightEvt {
public:
  LightEvt();
  virtual ~LightEvt();
  void clear();
  void render(int x, int y);
  void play(void *data, const char *path, u32 screenID);
  bool isPlaying() const;
  void setPos(const mm::Vec3 &pos);

private:
  ml::ScnObjLight *mLight;
  mm::mtl::FixStr<128> path;
  u32 mScreenID;
};

static_assert(sizeof(LightEvt) == 0x98, "");

} // namespace event

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
  ml::ScnObjLight *unknown08;     // Inferred role: light; original member name unknown.
  mm::mtl::FixStr<128> unknown10; // Inferred role: path; original member name unknown.
  u32 unknown94;                  // Inferred role: screen id; original member name unknown.
};

static_assert(sizeof(LightEvt) == 0x98, "");

} // namespace event

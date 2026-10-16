#pragma once
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

enum ALPHA_ATTR {
  ALPHA_ATTR_CHARA = 1,
  ALPHA_ATTR_MDLSTM = 2,
  ALPHA_ATTR_COUNT = 4,
};

class AlphaObj {
public:
  enum {
    FLAG_ACTIVE = 1 << 0,
  };

  AlphaObj(gf::GF_OBJ_HANDLE *handle);
  virtual ~AlphaObj() {}
  void update();
  void draw(int x, int y);
  void setAlpha(ALPHA_ATTR attr, f32 alpha, f32 belongingAlpha);
  static void setEventAlpha(gf::GF_OBJ_HANDLE *handle, f32 alpha, f32 belongingAlpha);

  bool isActive() const { return (flags & FLAG_ACTIVE) != 0; }
  gf::GF_OBJ_HANDLE *getHandle() const { return handle; }

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  f32 alphas[ALPHA_ATTR_COUNT];
  f32 belongingAlphas[ALPHA_ATTR_COUNT];
  f32 alpha;
  f32 belongingAlpha;
  s32 opaqueFrames;
};

static_assert(sizeof(AlphaObj) == 0x48, "");

} // namespace event

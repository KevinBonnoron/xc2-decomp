#pragma once
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf
namespace mm {
struct Vec3;
} // namespace mm

namespace event {

class CharaWeightPlayer;

class CharaPlayFacial : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_DISABLE_TALK_LIP = 1 << 2,
    FLAG_DISABLE_WINK = 1 << 3,
  };

  void render(const mm::Vec3 &position, f32 height);
  void play(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn, f32 blendOut);
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  CharaWeightPlayer *weight;
  int type;
  f32 life;
  const char *bdatName;
  const char *name;
  const char *browStat;
  f32 browWeight;
  const char *eyeStat;
  f32 eyeWeight;
  const char *lipStat;
  f32 lipWeight;
  f32 blendIn;
  f32 blendOut;
};

static_assert(sizeof(CharaPlayFacial) == 0x70, "");

} // namespace event

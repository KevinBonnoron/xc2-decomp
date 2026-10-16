#pragma once
#include "bdat.h"
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

class CharaPlayHead : public ICmd {
public:
  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
    FLAG_BLEND_OUT = 1 << 2,
  };

  void render(const mm::Vec3 &position, f32 height);
  void play(int type, f32 life, bool isBlendIn, bool isBlendOut);
  void idle();
  virtual void init();
  virtual RESULT update(const Param &param);
  virtual void term();

private:
  static const char *type2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "stat", type, 7)); }
  static f32 type2blend(int type) { return static_cast<s16>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "blend", type, 5)); }

  u32 flags;
  gf::GF_OBJ_HANDLE *handle;
  CharaWeightPlayer *weight;
  int type;
  f32 life;
  const char *name;
  f32 blendIn;
  f32 blendOut;
};

static_assert(sizeof(CharaPlayHead) == 0x38, "");

} // namespace event
